/*
 * This is a development sketch for K7TDI's KnobBox
 * Check out https://github.com/K7TDI/KnobBox for more info
 * Copyright at end of file.
 * 
 * This sketch is super buggy, but an intro to how one can interface the Kenwood CAT interface with SDR-Console (http://sdr-radio.com/)
 * It has no tuning functionality, but I have tested sending frequencies using (for example) Serial.print("FA000155000000;") to tune
 * SDR-Console to 155mhz.
 * 
 * This sketch will display current frequency and mode of SDR-Console.  There's a function included (sendmode()) that would allow you
 * to change the mode as well, but it's been touch and go getting it to work so I've omitted using it here.
 * 
 * Issues:
 * Aside from the bugginess overall, there's nothing here to handle the number of digits of the frequency changing on the LCD.
 * If you change from 1mhz to 999khz, you will have extra characters still on the screen.
 * 
 * If you get a bunch of garbled stuff on the screen, toggle serial on and off in SDR-Console.
*/

#include <LiquidCrystal.h> //for display
#include <Encoder.h>// include the PRJC encoder library http://www.pjrc.com/teensy/td_libs_Encoder.html

Encoder lEnc(1,0); //setup left encoder
Encoder rEnc(2,3); //setup right encoder

//setup lcd
LiquidCrystal lcd(16,14,5,6,7,8); //set up lcd

//pins
int blpin = 10; //backlight pwm pin
int leftbutton = 4; //left button pin
int rightbutton = 21; //right button pin

//global variables
unsigned long cfreq = 0; //current frequency
int mode; //current mode
unsigned long elapsed; //elapsed time, basically 'old' time


void setup() {
  pinMode(4, INPUT_PULLUP); //set up the left button
  pinMode(17, INPUT_PULLUP); //set up the right button
  analogWrite(10, 150); //turn on the backlight to a fixed setting
  lcd.begin(16, 2); //start LCD

  Serial.begin(57600); //blazin' fast!
  
  splash(); //show splash screen

  
  while (!Serial) //wait for serial connection
  {
    lcd.setCursor(0, 0);
    lcd.print("  Waiting For   ");
    lcd.setCursor(0, 1);
    lcd.print("    Serial..    ");
  }
  lcd.clear();

cfreq = getfreq(); //set cfreq to the frequency of SDR-Console
mode = getmode(); //set mode to current mode

lcd.setCursor(0,0);
lcd.print(cfreq); //display the current frequency

lcd.setCursor(13,1); //move to the bottom right
lcd.print(modetxt(mode)); //display the current mode in a 3 character string

}


void loop()
{
  
unsigned long newmillis = millis(); //a variable to use for every cycle

  if ((newmillis - elapsed) >= 500) //every 500 milliseconds, this can be sped up by a lot, but I left it slow here.  SDR-Console doesn't seem to mind being hammered by 'FA;', but other things seem to not work as well.
  {
    long newfreq = getfreq(); //get the current frequency over serial
    int newmode = getmode(); //get the current mode over serial
    
    if (newfreq != cfreq); //if the frequency has changed
      {
        cfreq = newfreq; //update the global freqency variable
        lcd.setCursor(0,0); //move the cursor...
        lcd.print(cfreq); //show the new freqency
      }
    if (newmode != mode) //if the mode has changed... same as above
      {
        mode = newmode;
        lcd.setCursor(13,1);
        lcd.print(modetxt(mode));
      }
    elapsed = newmillis; //reset the timer
  }
  
}

/***************************************************************************** Functions *****************************************************************************/
long getfreq() //returns VFO A frequency as a long(Serial.parseInt() actually returns a long).  This could be avoided with better handling of the leading zeroes for most frequencies.
{

  Serial.print("FA;"); //send request

  if (Serial.available() > 13) //if we have a return
  {
    unsigned long gotfreq = Serial.parseInt(); //parse it
    if (Serial.read() == ';') //once we hit the ';', exit
    {
      return gotfreq;
    }
  }
  else
  {
    return 0;
  }
} //end getfreq()

int getmode() //get current mode from SDR-Console
{

  Serial.print("MD;"); //send request
  delay(10);
  if (Serial.available() > 2) //if we have a return
  {
    int gotmode = Serial.parseInt(); //parse that shit
    if (Serial.read() == ';') //once we hit the ';', exit
    {
      if (gotmode < 1 || gotmode > 10) //if we get weird shit for the mode
      {
        gotmode = 1; //stick it on LSB
      }
      return gotmode;
    }
  }
} //end getmode()

String modetxt(int mode) //return a 3 character string for a mode number according to the spec
{
  switch (mode)
  {
  case 1:
    return "LSB";
    break;
  case 2:
    return "USB";
    break;
  case 3:
    return " CW";
    break;
  case 4:
    return " FM";
    break;
  case 5:
    return " AM";
    break;
  case 6:
    return "FSK";
    break;
  case 7:
    return "CWR";
    break;
  case 8:
    return "TNE";
    break;
  case 9:
    return "FSR";
    break;
  case 10:
    return "SAM";
    break;
  default:
    return "MOD";
    break;

  }
} //endmodetxt

void incrementmode() //increments the mode up 1 when called. (requires global variable 'mode')
{

  int newmode = mode + 1; //add 1 to mode variable

  switch (newmode) //sets mode to something common if it's been set to kenwood 6-9 or 10 (synchronous AM)
  {
  case 6: //if the mode is FSK
    newmode = 1; //pretend it's AM so we roll over to LSB on toggle
    break;
  case 7: //if mode is reverse CW
    newmode = 3; //pretend it's CW
    break;
  case 8: //if mode is 'tune' (I don't know if this would actually happen)
    newmode = 5; //pretend it's AM
    break;
  case 9: // if it's reverse FSK
    newmode = 1; //same as above, pretend it's AM
    break;
  case 10: //if it's synchronous AM, which sdrconsole sends
    newmode = 5; //pretend it's AM, this one makes sense right?
    break;
  case 11: //we hit the button after being on SAM
    newmode = 1; //if we pretended SAM is the same as regular AM, we'd land on LSB (#1) after clicking
    break;
  default:
    newmode = newmode; //don't change it
    break;

  }
}
void sendmode(int mode) //send the mode variable
{
  Serial.print("MD");
  Serial.print(mode);
  Serial.print(";");

} //end sendmode()

void splash() //splash screen
{
  unsigned long startmillis = millis();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("#DFP");
  while (millis() - startmillis < 2000)
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
