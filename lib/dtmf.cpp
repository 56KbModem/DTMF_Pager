#include "dtmf.hpp"

// check if a dtmf signal is available
bool MT8870::available()
{
	if (stq.get()){
		return 1;
	}
	else{
		return 0;
	}
}

// get 4-bit (nibble) signal from the module
uint8_t MT8870::get()
{
	return bit_3.get() << 3 | bit_2.get() << 2 | bit_1.get() << 1 | bit_0.get(); 
}
