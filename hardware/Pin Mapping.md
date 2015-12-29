I know my schematic sucks, so if you get lost, here are the important pins:

 Rotary Encoders:
 
	Left Encoder:
	B -> TX (Arduino pin 0) (CCW)
	C -> GND
	A -> RX (Arduino pin 1) (CW)
	
	Right Encoder:
	B -> 2 (CW)
	C -> GND
	A -> 3 (CCW)
	
	LCD Backlight:
	Pin 10 is connected to the base on an NPN transistor with a current limiting resistor (not sure if this is needed or not) of 100 ohms.
	You can analogWrite to it and change the backlight brightness.
	
	Everything Else:
	On my KnobBox I broke out all the other pins to pin headers on the board.  You don't need to, but the pads are there in the eagle files.
	I wound up leaving RAW and RST unconnected because I already had too much crap stuffed between the board and the back of the LCD at that spot.
