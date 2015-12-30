/*
 * This is a basic functionality sketch of K7TDI's KnobBox
 * Check out https://github.com/K7TDI/KnobBox 
 * Copyright info at the bottom
 * 
 *This sketch adjusts the backlight brightness.
 * 
 * It uses the left encoder.
*/

//include libraries
#include <Encoder.h>// include the PRJC encoder library http://www.pjrc.com/teensy/td_libs_Encoder.html
#include <LiquidCrystal.h>

//setup encoders
Encoder myEncLeft(1,0);
Encoder myEncRight(2,3);

//setup lcd
LiquidCrystal lcd(16,14,5,6,7,8);

int blpin = 10; //backlight pwm pin
int leftbutton = 4; //pushbutton on left encoder

int backlight = 80; //backlight level, percentage multiplied by 255 later

bool bltoggle = 0; //whether we're in the backlight setup or not

void setup() {
  Serial.begin(9600); //for debugging
  lcd.begin(16, 2); //more lcd setup
  
  pinMode(10, OUTPUT); //pwm backlight pin
  analogWrite(blpin, backlight); //crank it up for starters

  pinMode(leftbutton, INPUT_PULLUP); //set up the left button

}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("main loop");
  flipleft();
  while (bltoggle == 1)
  {
  backlightcontrol();
  }
}

void backlightcontrol() //software backlight dimming control
{
  lcd.setCursor(0,0);
  lcd.print("Brightness");
  lcd.setCursor(0,1);
  lcd.print(backlight); //print the variable...
  lcd.setCursor(2,1); //move to the 3rd position
  lcd.print("%"); //print a percent symbol
  int newbacklight = backlight + encoderchange();
  if (newbacklight != backlight && newbacklight >=1 && newbacklight <= 99) //if the encoder moves and the new value is within limits
  {
    
  backlight = newbacklight; //set the backlight variable
  analogWrite(blpin, backlight*2.5); //change the voltage on blpin
 }
 
  flipleft(); //check if the button has been pushed
  if(bltoggle == 0) //if we're going back to the main loop, clear the lcd
  {lcd.clear();}
 return;
}

void flipleft() //flip the backlight boolean
{
  if(digitalRead(leftbutton) == LOW)
  {
    
    bltoggle = !bltoggle;
    
    delay(200);
  }
}

int encoderchange () //should return -1 or 1 as integer
{
  int change = myEncLeft.read();
  if (change != 0 && (change % 2 == 0))
  {
    myEncLeft.write(0);
  }
  int output = change/2;
  return output;
}
