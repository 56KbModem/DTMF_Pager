#include "dtmf.hpp"

// add a character to the DTMF message
void DTMF_data::add(const char & DTMF_character)
{
	unsigned int i = 0; // iterator for char array
	while (DTMF_message[i] != '\0' && i < 1000){
		++i;
		if (DTMF_message[i] == '\0' && i < 1000){
			DTMF_message += DTMF_character;
		}
	}
}

// clear the DTMF message
void DTMF_data::reset()
{
	DTMF_message = ""; // empty string
}

// return the DTMF message to the caller
hwlib::string<1000> DTMF_data::print()
{
	return DTMF_message;
}