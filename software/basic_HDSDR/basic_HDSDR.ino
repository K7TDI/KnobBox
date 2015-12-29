/*
 * This is a basic functionality sketch of K7TDI's KnobBox
 * Check out https://github.com/K7TDI/KnobBox 
 * Copyright info is at the bottom
 * 
 * This sketch sends a mouse scroll when the left encoder is turned, and command + up or down arrow when the right encoder is turned
 * These commands are designed to work with HDSDR http://www.hdsdr.de/
 * 
 * If you haven't already, look at the 'basic_scrolling.ino' sketch to get a better idea of what is going on.
 * This sketch does not use the LCD, but I left everything in to be uncommented if you want to use it for something.
 * 
 * Issues:
 * The encoders I'm using register a change halfway between notches.  Therefore this sketch gives me twice as many steps as I would expect.
*/

#include <Keyboard.h> //for keyboard emulation
#include <Mouse.h> //for mouse emulation
#include <LiquidCrystal.h> //for display
#include <Encoder.h>// include the PRJC encoder library http://www.pjrc.com/teensy/td_libs_Encoder.html

Encoder lEnc(1,0); //setup left encoder
Encoder rEnc(2,3); //setup right encoder

//LiquidCrystal lcd(16,14,5,6,7,8); //set up lcd

//pins
//int blpin = 10; //backlight pwm pin
int leftbutton = 4; //left button pin
int rightbutton = 17; //right button pin

//variables
long leftposition = 5000; //arbitrary, I found you can stuff at least 9x10^10 into the encoder object and everything works fine
long rightposition = 5000;


unsigned long timer1; //updated to the output of millis() every cycle
unsigned long elapsed; //elapsed time, basically 'old' time
unsigned long elapsed1; //another 'old' time variable
int ldifference; //this keeps track of the difference between the left position variable and the register of the encoder
int rdifference; //same as above

void setup() {
  pinMode(4, INPUT_PULLUP); //set up the left button
  pinMode(17, INPUT_PULLUP); //set up the right button
  //analogWrite(10, 150); //turn on the backlight to a fixed setting
  //lcd.begin(16, 2); //start LCD

  Mouse.begin();
  Keyboard.begin();
  
  lEnc.write(leftposition); //start the register at the above defined position
  rEnc.write(rightposition); //same as above
  
  //splash(); //show splash screen
}

void loop() {

  unsigned long newmillis = millis(); //a variable to use for every cycle
  timer1 = newmillis; //set the timer var to current time
  long newLpos = lEnc.read(); //put the current encoder position into a variable
  long newRpos = rEnc.read();
  
  
  if ((newmillis - elapsed) >= 50) //every 50 milliseconds
    {
      ldifference = newLpos - leftposition; //see if there's a difference
      rdifference = newRpos - rightposition;
    
      if(ldifference != 0) //if the left position has changed
        {
          sendLeft(ldifference); //send that difference through the function.
          leftposition = newLpos; //reset the left position
          ldifference = 0; //clear out the difference
        }
       if(rdifference != 0) //if the right position has changed... same as above
        {
          sendRight(rdifference);
          rightposition = newRpos;
          rdifference = 0;
        }
      elapsed = newmillis; //reset the timer
  }

  
  if ((newmillis - elapsed1) >= 5000) //every 5 seconds, reset positions to 500.  We're interested in the difference between updates, this makes it less likely to overflow the variables
  {
    elapsed1 = millis();
    leftposition = 5000; //set the left position back to 5000
    rightposition = 5000; //set the right position back to 5000
    lEnc.write(leftposition); //set the encoder register back to 5000
    rEnc.write(rightposition); //same as above
    elapsed1 = newmillis; //reset the timer
  }
}


void sendLeft(int ldiff) //This doesn't need to be a function at this point, but I like having it here for further changes
{
  Mouse.move(0,0,ldiff); //send it
}

void sendRight(int rdiff)
{
  Keyboard.press(128); //push the control button
  
  if (rdiff > 0) //if rdiff is a positive number
  {
    for (int i = 0; i < rdiff; i++) //run this command 'rdiff' times
    {
    Keyboard.write(218); //press up arrow
    }
  }
  if (rdiff < 0) //if rdiff is a negative number
  {
    for (int i = 0; i < -rdiff; i++) //run this command 'rdiff' times
    {
    Keyboard.write(217); //press down arrow
    }
  }
  Keyboard.release(128); //release the control button
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
