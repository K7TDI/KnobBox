/*
 * This is a basic functionality sketch of K7TDI's KnobBox
 * Check out https://github.com/K7TDI/KnobBox for more info
 * Copyright at end of file.
 * 
 * This sketch shows the values of the rotary encoders on the LCD basically
 * 
*/

#include <Keyboard.h> //for keyboard emulation
#include <Mouse.h> //for mouse emulation
#include <LiquidCrystal.h> //for display
#include <Encoder.h>// include the PRJC encoder library http://www.pjrc.com/teensy/td_libs_Encoder.html

Encoder lEnc(1,0); //setup left encoder
Encoder rEnc(2,3); //setup right encoder

//setup lcd
LiquidCrystal lcd(16,14,5,6,7,8); //set up lcd

//pins
int blpin = 10; //backlight pwm pin
int leftbutton = 4; //left button pin
int rightbutton = 17; //right button pin

//variables
long leftposition = 5000; //arbitrary, I found you can stuff at least 9x10^10 into the encoder object and everything works fine
long rightposition = 5000;


unsigned long timer1; //updated to the output of millis() every cycle
unsigned long elapsed; //elapsed time, basically 'old' time
unsigned long elapsed1; //another 'old' time variable
int difference; //this keeps track of the difference between the left position variable and the register of the encoder

void setup() {
  pinMode(4, INPUT_PULLUP); //set up the left button
  pinMode(17, INPUT_PULLUP); //set up the right button
  analogWrite(10, 150); //turn on the backlight to a fixed setting
  lcd.begin(16, 2); //start LCD

  Mouse.begin();
  Keyboard.begin();
  
  lEnc.write(leftposition); //start the register at the above defined position
  rEnc.write(rightposition); //same as above
  
  splash(); //show splash screen
}

void loop() {

  unsigned long newmillis = millis(); //a variable to use for every cycle
  timer1 = newmillis; //set the timer var to current time
  long newLpos = lEnc.read(); //put the current encoder position into a variable
  
  lcd.setCursor(0,0); //1st line
  lcd.print(leftposition); //print the current value of leftposition variable

  if (newLpos != leftposition) //if the encoder has moved
  {
  difference = newLpos - leftposition; //self explanitory
  lcd.setCursor(0,1); //2nd line
  lcd.print(newLpos); //print the left encoder position
  lcd.setCursor(10,0); //move over to the right on the 1st line
  lcd.print(difference); //show the difference
  }
  
  if ((newmillis - elapsed) >= 100) //every 100 milliseconds
  {
    elapsed = millis();
    lcd.setCursor(10,1); //move over to the right on the 2nd line
    lcd.print(elapsed/1000); //show the elapsed time in seconds
    leftposition = newLpos; //set the left position value
    Mouse.move(0,0,-difference); //scroll the opposite of 'difference'
    difference = 0; //clear the difference variable
    lcd.setCursor(10,0); //move over to where we're printing difference
    lcd.print("    "); //print some blank spaces over where the difference was
    elapsed = newmillis; //reset the timer
  }
  if ((newmillis - elapsed1) >= 5000) //every 5 seconds, reset positions to 500.  We're interested in the difference between updates, this makes it less likely to overflow the variables
  {
    elapsed1 = millis();
    leftposition = 5000; //set the left position back to 500
    lEnc.write(leftposition); //set the encoder register back to 500
    lcd.setCursor(0,1); //move to the right of the 2nd line
    lcd.print(lEnc.read()); //show that new value
    elapsed1 = newmillis; //reset the timer
  }
}

void splash() //splash screen
{
  unsigned long startmillis = millis();
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("#DFP");
  while(millis() - startmillis < 2000)
  {
  }
  lcd.clear();
}

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
