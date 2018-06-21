#ifndef TEXT_DATA_HPP
#define TEXT_DATA_HPP
#include "dtmf.hpp"

class TEXT_data : public MT8870{
private:
	/* DTMF keypad */
	char keys[16] = {'D', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C'};
	hwlib::string<1000> DTMF_message;
	hwlib::string<1000> TEXT_message;
	
	char decode(const hwlib::string<20> & substring);
	char get_phone_char(const int & size, const hwlib::string<20> & button);
public:
	TEXT_data(const hwlib::target::pin_in & bit_0,
			  const hwlib::target::pin_in & bit_1,
			  const hwlib::target::pin_in & bit_2,
			  const hwlib::target::pin_in & bit_3,
			  const hwlib::target::pin_in & stq):
		MT8870(bit_0, bit_1, bit_2, bit_3, stq),
		DTMF_message(""),
		TEXT_message("")
		{}
		
	hwlib::string<1000> print();
	void add(const uint8_t & MT8870_signal);
	void reset();
};

#endif // TEXT_DATA_HPP
