#include "TEXT_data.hpp"

hwlib::string<1000> TEXT_data::print
{
	unsigned int cur_pos = 0; // iterator
	char last_char = DTMF_message[0]; // last char that was seen
	hwlib::string<1000> substring = "";
	
	while (DTMF_message[cur_pos] != '\0' && cur_pos < 1000){
		
		while(DTMF_message[cur_pos] == last_char){
			last_char = DTMF_message[cur_pos];
			substring += DTMF_message[cur_pos];
			cur_pos++;
		}
		TEXT_message += TEXT_data.decode(substring);
	}
}

char TEXT_data::decode(const hwlib::string & substring)
{
	for ()
}

