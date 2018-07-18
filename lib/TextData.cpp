#include "TextData.hpp"

hwlib::string<1000> TextData::print()
{
	unsigned int cur_pos = 0; // iterator
	char last_char = DTMF_message[0]; // last char that was seen
	hwlib::string<20> substring = ""; // substring to decode into character

	/* Loop as long as there are characters in the DTMF message */
	while (cur_pos <= DTMF_message.length()){
		
		if (DTMF_message[cur_pos] == 'C'){ // splitted substring
			TEXT_message += decode_key_num(substring);
			cur_pos++;
			last_char = DTMF_message[cur_pos];
			substring = "";
		}
		
		/* Create a substring to decode */
		else if (DTMF_message[cur_pos] == last_char){
			last_char = DTMF_message[cur_pos];
			substring += DTMF_message[cur_pos];
			cur_pos++;
		}
		
		else{
			TEXT_message += decode_key_num(substring); // decode to value
			last_char = DTMF_message[cur_pos];
			substring = DTMF_message[cur_pos];
			cur_pos++;
		}
	}
	return TEXT_message;
}

/* return dtmf string directly */
hwlib::string<1000> TextData::print_raw()
{
	return DTMF_message;
}


char TextData::decode_key_num(const hwlib::string<20> & substring)
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

char TextData::get_phone_char(const signed int & size, const hwlib::string<20> & button)
{
	int index = (size % button.length()) - 1;
	if (index < 0){
		index = button.length() - 1;
	}
	return button[index];
}

void TextData::reset()
{
	DTMF_message = ""; 
	TEXT_message = "";
}

void TextData::add(const uint8_t & MT8870_signal)
{
	DTMF_message += keys[MT8870_signal];
}