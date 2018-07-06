#include "TEXT_data.hpp"

hwlib::string<1000> TEXT_data::print()
{
	hwlib::cout << "STRING: " << DTMF_message << '\n';
	unsigned int cur_pos = 0; // iterator
	char last_char = DTMF_message[0]; // last char that was seen
	hwlib::string<20> substring = ""; // substring to decode into character
	
	while (cur_pos <= DTMF_message.length()){
		
		if (DTMF_message[cur_pos] == last_char){
			last_char = DTMF_message[cur_pos];
			substring += DTMF_message[cur_pos];
			cur_pos++;
		}else{
			TEXT_message += decode(substring); // decode to value
			hwlib::cout << "substring: " << substring << '\n';
			last_char = DTMF_message[cur_pos];
			substring = DTMF_message[cur_pos];
			cur_pos++;
		}
	}
	return TEXT_message;
}


char TEXT_data::decode(const hwlib::string<20> & substring)
{
	/* this array represents the ITU-T E.161 layout */
	std::array<hwlib::string<4>, 8> E_161 = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
	
	char button = substring[0]; // check which button it is about
	
	/* choose which button to decode */
	switch (button){
		case '1':
			return ' ';
			break;
		case '2':
			return get_phone_char(substring.length(), E_161[0]);
			break;
		case '3':
			return get_phone_char(substring.length(), E_161[1]);
			break;
		case '4':
			return get_phone_char(substring.length(), E_161[2]);
			break;
		case '5':
			return get_phone_char(substring.length(), E_161[3]);
			break;
		case '6':
			return get_phone_char(substring.length(), E_161[4]);
			break;
		case '7':
			return get_phone_char(substring.length(), E_161[5]);
			break;
		case '8':
			return get_phone_char(substring.length(), E_161[6]);
			break;
		case '9':
			return get_phone_char(substring.length(), E_161[7]);
			break;
	}
	return '.';
}

char TEXT_data::get_phone_char(const signed int & size, const hwlib::string<20> & button)
{
	int index = (size % button.length()) - 1;
	if (index < 0){
		index = button.length() -1;
	}
	hwlib::cout << size << " mod " << button.length() << " = " << index << '\n';
	return button[index];
}

void TEXT_data::reset()
{
	DTMF_message = ""; 
	TEXT_message = "";
}

void TEXT_data::add(const uint8_t & MT8870_signal)
{
	DTMF_message += keys[MT8870_signal];
}
