#ifndef TEXT_DATA_HPP
#define TEXT_DATA_HPP

class TEXT_data
{
private:
	hwlib::string<1000> TEXT_message;
public:
	TEXT_data():
		TEXT_message("");
		{}
		
	hwlib::string<1000> print() override;
	char decode();
};

#endif // TEXT_DATA_HPP
