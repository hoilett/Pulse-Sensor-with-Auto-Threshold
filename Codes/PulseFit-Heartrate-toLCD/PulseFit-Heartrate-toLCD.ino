/*  FILENAME: PulseFit-Heartrate
 *  AUTHORS:  Orlando S. Hoilett
 *  VERSION:  V.0.1.0
 *  EMAIL:    orlandohoilett@gmail.com
 *  WEBSITE:  https://github.com/hoilett/Pulse-Sensor-with-Auto-Threshold.git
 *  
 *  AFFILIATION
 *  Calvary Engineering (@CalvEngIO)
 *  
 *  Description
 *  
 *  
 *  LICENSE
 *  CC-BY-SA-4.0
 *  
 *  If you find any bugs or have any questions, please feel free to contact
 *  orlandohoilett@gmail.com
 *  
 */

//LCD
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR  0x3F  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN   3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C     lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

unsigned long strtTime = 0;
unsigned long lastTime = 0;
unsigned long SamplePeriod = 7500; //6 seconds in milliseconds
unsigned long SixtySecs = 60000; //60 seconds in milliseconds
unsigned long refracPeriod = 300;

int pulsePin = A0;
int compPin = 2;
int peakPin = A2;

int pulse = 0;
int comp = 0;
int peak = 0;

int heartBeats = 0;
int heartRate = 0;

void setup()
{
  Serial.begin(9600);

  //uncomment this line if you want to reference the analogRead
  //to V+ of PulseFit if not being powered from Arduino
  //analogReference(EXTERNAL);

  lcd.begin (20,4);  //Size of LCD
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();

  attachInterrupt(digitalPinToInterrupt(2), detectPeaks, RISING);
  
  delay(2000);
  
  //initialize timekeeping variables
  strtTime = millis();
  lastTime = strtTime;
}

void loop()
{
  //measuring the amplifier outputs using the ADC
  pulse = analogRead(pulsePin);
  peak = analogRead(peakPin);
  
  //Serial.println(pulse);

  if((millis() - strtTime) > SamplePeriod)
  {
    //number of beats in 6 seconds scaled to number of beats
    //in 60 seconds
    heartRate = (double)heartBeats*((double)SixtySecs/(millis()-strtTime));
    Serial.print("heart rate: ");
    Serial.println(heartRate);
    writeToLCD();
    heartBeats = 0; //restart heartBeat variable
    strtTime = millis(); //restart timer variable
  }
  delay(20);
}


void detectPeaks()
{
  if((millis()-lastTime) > refracPeriod)
  {
    heartBeats++;
    Serial.println(heartBeats);
    lastTime = millis();
  }
}


void writeToLCD()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Heart Rate: ");
  lcd.setCursor(0,1);
  lcd.print(heartRate);
  lcd.setCursor(3,1);
  lcd.print("BPM");
}
