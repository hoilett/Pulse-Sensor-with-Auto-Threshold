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


unsigned long strtTime = 0;
unsigned long lastTime = 0;
unsigned long 6Secs = 6000; //6 seconds in milliseconds
unsigned long 60Secs = 60000; //60 seconds in milliseconds
unsigned long refracPeriod = 300;

int pulsePin = A0;
int compPin = A1;
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

  //initialize timekeeping variables
  strtTime = millis();
  lastTime = strtTime;
}

void loop()
{
  //measuring the amplifier outputs using the ADC
  pulse = analogRead(pulsePin);
  comp = analogRead(compPin);
  peak = analogRead(peakPin);
  
  Serial.print(pulse);

  //Counting heartbeats and calculating heart rate
  //this if-statements ensures that we don't count the same
  //heartbeat twice
  if(millis()-lastTime > refracPeriod)
  {
    //increments heartBeats variable is comparator voltage output is HIGH
    heartBeats += (int)digitalRead(compPin); //should be able to do this without doing pinMode()

    //after 6 seconds of data collection, calculate heart rate
    if((millis() - strtTime) > 6Secs)
    {
      //number of beats in 6 seconds scaled to number of beats
      //in 60 seconds
      heartRate = (double)heartBeats*((double)60Secs/(millis()-strtTime));
      Serial.print("heart rate: ");
      Serial.println(heartRate);
      heartBeat = 0; //restart heartBeat variable
      strtTime = millis(); //restart timer variable
    }
    
    lastTime = millis();
  }

  delay(20);
}
