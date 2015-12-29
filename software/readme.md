Here are some example files that show what the hardware can do.  I've commented as much as possible in the code, although I make no promises that my thought process makes sense.

These make use of the LiquidCrystal library included with the Arduino IDE, and the Encoder library from PJRC, which is by far the best I've found.  That's available here:

http://www.pjrc.com/teensy/td_libs_Encoder.html


basic_function is an example of interfacing with the hardware and turning knobs.

basic_scrolling is a simple mouse wheel scroll emulator using the left encoder knob.

basic_HDSDR includes both mouse wheel scrolling and keyboard commands.

basic_CAT is a starting point for serial communications using Kenwood CAT commands, which are compatible with SDR-Console.
