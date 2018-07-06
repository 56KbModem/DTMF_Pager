#ifndef TEXT_DATA_HPP
#define TEXT_DATA_HPP
#include "dtmf.hpp"

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
	TEXT_data(const MT8870 & DTMF_Module):
		DTMF_Module(DTMF_Module),
		DTMF_message(""),
		TEXT_message("")
		{}
		
	hwlib::string<1000> print();
	void add(const uint8_t & MT8870_signal);
	void reset();
};

#endif // TEXT_DATA_HPP
