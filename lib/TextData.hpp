#ifndef TEXT_DATA_HPP
#define TEXT_DATA_HPP
#include "dtmf.hpp"

/// @file

/// \brief
/// Class implementing text schema decoding from DTMF numeric string.
/// \details
/// This class can be used to create a text string from DTMF signals.
/// It can latch in keypresses from the MT8870 module and later decode
/// them into a string following the ITU-T E.161 standard.

class TextData{
private:
	/* reference to a MT8870 module */
	MT8870 DTMF_Module;

	/* DTMF keypad */
	char keys[16] = {'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C'};
	hwlib::string<1000> DTMF_message;
	hwlib::string<1000> TEXT_message;
	
	/// \brief
	/// Decode a substring.
	/// \details
	/// This function detects what button was pressed
	/// and determines which sequence of characters should be looked
	/// in to find the meant character. The user of this library should
	/// not have to tamper with this function as it is only called by
	/// the print function.
	char decode_key_num(const hwlib::string<20> & substring);
	
	/// \brief
	/// Return a phone character following E.161.
	/// \details
	/// This function takes the size of a DTMF substring and
	/// a button substring defined in decode_key_num() and uses
	/// modulo arithmetic to determine the right character to return.
	/// The user of this library should not have to tamper with this
	/// function as it is only to be used by the decode_key_num()
	/// function.
	char get_phone_char(const signed int & size, const hwlib::string<20> & button);
public:

	/// \brief
	/// Constructor for the TextData class.
	/// \details
	/// This constructor takes a reference to an MT8870 module
	/// and constructs an empty object (message strings are empty strings).
	TextData(const MT8870 & DTMF_Module):
		DTMF_Module(DTMF_Module),
		DTMF_message(""),
		TEXT_message("")
		{}
	
	/// \brief
	/// Decode DTMF_message string and return TEXT_message string.
	/// \details
	/// This function uses the decode_key_num() and get_phone_char()
	/// functions internally to decode the numeric DTMF message string
	/// and adds every decoded character to TEXT_message.
	/// Finally it returns TEXT_message.
	hwlib::string<1000> print();
	
	/// \brief
	/// Return raw DTMF string.
	/// \details
	/// This function returns the objects DTMF string data.
	hwlib::string<1000> print_raw();
	
	/// \brief
	/// Add a number to DTMF_message.
	/// \details
	/// This function takes a byte, preferably a MT8870 signal,
	/// and adds it to the DTMF_message variable.
	void add(const uint8_t & MT8870_signal);
	
	/// \brief
	/// Reset message variables
	/// \details
	/// This function resets both DTMF_message and TEXT_message
	/// variables in this object to an empty hwlib::string.
	void reset();
};

#endif // TEXT_DATA_HPP
