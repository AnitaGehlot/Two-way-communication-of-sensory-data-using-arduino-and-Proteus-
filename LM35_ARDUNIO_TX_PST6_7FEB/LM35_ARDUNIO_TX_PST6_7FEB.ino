// the setup routine runs once when you press reset:
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  // initialize serial communication at 9600 bits per second:
  lcd.begin(16,2);
  Serial.begin(9600);
  inputString.reserve(200);
}

// the loop routine runs over and over again forever:
void loop() 
{  
  serialEvent();
  delay(100);
  int VAL1 = analogRead(A0);
  int FSR1=VAL1/2;
  lcd.setCursor(0,0);
  lcd.print("Temp0C:");
  lcd.setCursor(8,0);
  lcd.print(FSR1);
  Serial.println(FSR1);
             // delay in between reads for stability
}

void serialEvent()
{
  while (Serial.available()>0)
  {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == 0x0D) 
    {
      stringComplete = true;
    }
  
  }
  if (stringComplete)
  {
    lcd.setCursor(0,1);
    lcd.print(inputString[0]);
    lcd.print(inputString[1]);
        
    if(inputString[0]==0x0A)
    {
    lcd.setCursor(0,1);
    lcd.print(inputString[1]);
    lcd.print(inputString[2]);
    }
   // Serial.println(inputString); 
    // clear the string:
    inputString = "";
    stringComplete = false;
  } 
  
}
