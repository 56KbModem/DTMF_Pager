#ifndef DTMF_DATA_HPP
#define DTMF_DATA_HPP
#include "hwlib.hpp"

/* This class implements a 5-wire interface to the MT8870 DTMF module*/
class MT8870 {
protected:
	hwlib::target::pin_in bit_0;
	hwlib::target::pin_in bit_1;
	hwlib::target::pin_in bit_2;
	hwlib::target::pin_in bit_3;
	hwlib::target::pin_in stq;
public:
	MT8870(const hwlib::target::pin_in & bit_0,
			  const hwlib::target::pin_in & bit_1,
			  const hwlib::target::pin_in & bit_2,
			  const hwlib::target::pin_in & bit_3,
			  const hwlib::target::pin_in & stq):
		bit_0(bit_0),
		bit_1(bit_1),
		bit_2(bit_2),
		bit_3(bit_3),
		stq(stq)
		{}
	
	bool available();
	uint8_t get();
};

#endif // DTMF_DATA_HPP