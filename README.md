# KnobBox
K7TDI's hardware interface for SDR software

This is a hardware controller for SDR software such as SDR-Console and HDSDR.  It currently utilizes keyboard emulation for input into the software, but the goal of the project is to be entirely compatible with Kenwood CAT serial communication.  This is well implemented in SDR-Console, which is quickly becoming my favorite software to use.  However, by using an Adruino Pro Micro (Atmel 328p, compatible with the Leonardo), keyboard and mouse wheel emulation is easy, and this allows the KnobBox to be used with any software that supports those.

This project, aside from the PCB, uses all off the shelf hardware, most of it available from China on eBay.  The total cost if you go that route is around $30, depending on how many extra parts you order.

It consists of:

An Arduino Pro Micro

2 5 pin rotary encoders with push buttons

a 16x2 LCD display with HD44780 controller

An enclosure

A custom PCB

Some videos:
https://vimeo.com/150329712
https://vimeo.com/150324509
https://vimeo.com/150324508
https://vimeo.com/150324507

**Notice/Current issues**

This is NOT complete, and is a pain to assemble.  I've included issues and proposed fixes in the hardware folder.

The software is also completely incomplete.  This is addressed in the software folder.

I really hope to get feedback and help with this project.  I've been plugging away at it for months now, and learning a lot along the way.  I'm a masters student in health sciences with an undergrad in biology, I hope some of you that are more experienced with hardware design and especially coding will make contributions.

I hope you find what I've released here helpful, and at least a starting point for your own ideas.

If you like this and use it for your own project that you distribute, I'd appreciate it if you included a mention of my callsign (K7TDI) and a link to this repo.



**If you'd like to contact me:**
**k7tdi@technotechnician.com**
