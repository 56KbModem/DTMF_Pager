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

class TEXT_data{
private:
	/* reference to a MT8870 module */
	MT8870 DTMF_Module;

	/* DTMF keypad */
	char keys[16] = {'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C'};
	hwlib::string<1000> DTMF_message;
	hwlib::string<1000> TEXT_message;
	
	char decode(const hwlib::string<20> & substring);
	char get_phone_char(const signed int & size, const hwlib::string<20> & button);
public:

	/// \brief
	/// Constructor for the TEXT_data class.
	/// \details
	/// This constructor takes a reference to an MT8870 module
	TEXT_data(const MT8870 & DTMF_Module):
		DTMF_Module(DTMF_Module),
		DTMF_message(""),
		TEXT_message("")
		{}
	
	/// \brief
	/// Decode DTMF_message string and return TEXT_message string.
	/// \details
	/// This function uses the decode() and get_phone_char()
	/// functions internally to decode the numeric DTMF message string
	/// and adds every decoded character to TEXT_message.
	/// Finally it returns TEXT_message.
	hwlib::string<1000> print();
	
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
	/// variables in this object.
	void reset();
};

#endif // TEXT_DATA_HPP
