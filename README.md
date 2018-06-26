# DTMF Pager program

## Synopsis
This library will be used to implement a pager over DTMF

## DTMF Library
The library in dtmf.hpp and its implementation in dtmf.cpp
give a very basic interface to the MT8870 DTMF decoder chip.

It only uses it's four output pins which translate to a specific
tone pair and the StQ pin to check whether a tone is available.
The chip and this accompanying library can be used to make use of
DTMF tones from whatever source possible, be it a radio or a landline,
and can thus be fed into another device like an answer machine or 
phone menu system.

## Text library
The library in TEXT\_data.hpp and its implementation in
TEXT\_data.cpp can make use of the MT8870 class defined in
dtmf.hpp to give a translation of the incoming tone(s) to
a character following the ITU-T E.161 standard.

Some less used characters on a phone keypad will be
used by this library to signal an action to occur,
like output this text to a screen or delete the buffer.

A user of this library may use the ```add()``` function to read in
a signal from the DTMF module (through the MT8870 object),
The ```reset()``` function to clear the buffers and a print function
to get the text buffer returned to him. Internally the class
will use two functions to decode the dtmf message to text,
namely ```decode()``` function to lookup which group of characters
to decode and ```get_phone_char()``` to see which character of the
group was meant.
