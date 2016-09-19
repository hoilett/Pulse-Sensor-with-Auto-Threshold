/*  FILENAME: PulseFit-Plotter
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


int pulsePin = A0;
int compPin = A1;
int peakPin = A2;

int pulse = 0;
int comp = 0;
int peak = 0;

void setup()
{
  Serial.begin(9600);

  //uncomment this line if you want to reference the analogRead
  //to V+ of PulseFit if not being powered from Arduino
  //analogReference(EXTERNAL);

}

void loop()
{
  //measuring the amplifier outputs using the ADC
  pulse = analogRead(pulsePin);
  comp = analogRead(compPin);
  peak = analogRead(peakPin);

  //The Arduino Serial Plotter can only plot one variable
  //at a time. Uncomment and comment each line for whatever value
  //you would like to print.
  Serial.println(pulse);
  //Serial.print(comp);
  //Serial.print(peak);

  delay(20);
}
