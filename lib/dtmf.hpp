#ifndef DTMF_DATA_HPP
#define DTMF_DATA_HPP
#include "hwlib.hpp"

/* This class holds the characters decoded from the MT8870 DTMF module*/
class DTMF_data {
protected:
	hwlib::string<1000> DTMF_message;
public:
	DTMF_data():
		DTMF_message("")
		{}
	
	void add(const char & DTMF_character);
	void reset();
	hwlib::string<1000> print();
	
};

#endif // DTMF_DATA_HPP