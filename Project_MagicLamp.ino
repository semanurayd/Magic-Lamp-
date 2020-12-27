/*
 Project Name  : MAGIC LAMP
 Revision Date : 20.12.2020
 Author        : SEMANUR AYDINALP
//------------------------------------------------------------------------------------------
 Purpose       : Implementing a temperature and light balance system that will contribute
                 to the development of plants and increase their efficiency. 
//------------------------------------------------------------------------------------------
 System Input  :
                 1. NTC  : To determine the ambient temperature  
                 2. LDR  : To determine the amount of light coming into environment  
 System Output :
                 1. LED  : To change color according to temperature 
                 2. LCD  : To print the ambient temperature 
//-------------------------------------------------------------------------------------------
 System Work   : Light is detected with LDR, if the amount of light in the environment is 
                 less than a certain value, the temperature in the environment is checked. 
                 The leds change color according to the temperature values. If the amount
                 of light is greater than the specified value, the LEDs will not light. 
//-------------------------------------------------------------------------------------------                                         
 */

#include<math.h>
#include<LiquidCrystal.h>
 

// DEFINITIONS
LiquidCrystal lcd (8, 7, 6, 5, 4, 3);
  
 /* CIRCUIT:
 * LCD RS pin digital pin 8
 * LCD Enable pin digital pin 7
 * LCD D4 pin digital pin 6
 * LCD D5 pin digital pin 5
 * LCD D6 pin digital pin 4
 * LCD D7 pin digital pin 3
 * LCD R/W pin GND
 * LCD VSS pin GND
 * LCD VCC pin +5V  */

int red=9;
int blue=10;

// SETUP CODE AREA
void setup() {
  
   Serial.begin(9600);                 // Sets the baud rate for serial data transmission.          
   lcd.begin(16,2);                    // Indicates the number of columns and rows of the LCD. 
   pinMode(red,OUTPUT);                // Red led defined as OUTPUT.
   pinMode(blue,OUTPUT);               // Blue led defined as OUTPUT.
   Serial.println("Setup is done!");
}

 // The Function Prat that converts the temperature value to degrees 
 double Thermistor(int analogRead){

  double temperature;
  temperature = log(((10240000 / analogRead) - 10000));
  temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
  temperature = temperature - 273.15;
  return temperature;
 }
 
 // MAIN CODE AREA
void loop() {
 
  int ntc_value = analogRead(A0);                // Read the analog NTC value.
  double temperature = Thermistor(ntc_value);  // Call the temperaure function.
  Serial.println(temperature);                   // Display temperature values to serial port screen.
  int light = analogRead(A2);                    // Read the analog light value.
  Serial.println(light);
  
  lcd.clear();                          // Erase the screen.  
  lcd.home();
  lcd.print("  TEMPERATURE  ");       // Print the TEMPERATURE on the screen.
  lcd.setCursor(0, 1);                  // Print text on the bottom line of the screen.
  lcd.print(temperature);               // Print the temperature value on the screen.
  lcd.print(" degrees ");               // Print the degrees on the screen.
  delay(1000);

 // if light is smaller than 45 look at temperature 
 if (light < 45){

    // if temperature bigger than 25 turn on the red light and turn of the blue light. 
    if(temperature >= 25){     
      digitalWrite(red,LOW);
      digitalWrite(blue,HIGH);
      delay(10000);
    }
    // if temperature smaller than 25 turn on the blue light and turn of the red light.
    else{
      digitalWrite(red,HIGH);
      digitalWrite(blue,LOW);
      delay(10000);
    }
 }
 // if light is bigger than 50 turn of the both leds. 
 if (light > 50){
   digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
 } 
}
