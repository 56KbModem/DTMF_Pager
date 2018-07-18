#include "hwlib.hpp"
#include "dtmf.hpp"
#include "TextData.hpp"

namespace target = hwlib::target;

// function prototype
hwlib::string<1000> test_lib(const bool & human_readable);


int main(int argc, char **argv)
{

	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;
      

	// setup for OLED display (i2c)
	auto scl     = target::pin_oc( target::pins::scl ); // Serial clock
	auto sda     = target::pin_oc( target::pins::sda ); // Serial data
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ); // i2c bus
	auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 	// OLED display
	auto font    = hwlib::font_default_8x8();			// OLED font size
	auto display = hwlib::window_ostream( oled, font );	// output stream to window

	oled.clear();         // refresh oled 

	/* START OF TEST */
	hwlib::wait_ms(1000); // wait for serial conn
	hwlib::string<1000> token;
	int test_count = 0;
	
	hwlib::cout << "Please run help_me.wav through the radio's:\n";
	token = test_lib(1);
	
	if (token == "help me"){
		hwlib::cout << "Test 1: OK\n";
		test_count++;
	}
	else{
		hwlib::cout << "Test 1: NOK\n";
		hwlib::cout << "ERROR: DTMF string decoded incorrectly: " << "." << token << "." << '\n';
	}
	
	hwlib::cout << "Please run test_1.wav through the radio's:\n";
	token = test_lib(1);
	
	if (token == "abc"){
		hwlib::cout << "Test 2: OK\n";
		test_count++;
	}
	else{
		hwlib::cout << "Test 2: NOK\n";
		hwlib::cout << "ERROR: error seperating same button string: " << token << '\n';
	}
	
	hwlib::cout << "Please run test_2.wav through the radio's:\n";
	token = test_lib(0);
	
	if (token == "123456789"){
		hwlib::cout << "Test 3: OK\n";
		test_count++;
	}
	else{
		hwlib::cout << "Test 3: NOK\n";
		hwlib::cout << "Not all keys were detected: " << token << '\n';
	}
	
	if (test_count == 3){
		oled.clear();
		hwlib::cout << "Library stable!\n";
		display << '\f' << "TEST OK!" << '\n' << hwlib::flush;
	}
	else{
		oled.clear();
		hwlib::cout << "Library unstable: please check source for errors!\n";
		display << '\f' << "TEST FAILED!" << '\n' << hwlib::flush;
	}
}

hwlib::string<1000> test_lib(const bool & human_readable)
{
	//StQ pin (high when a DTMF tone is available)
	auto STQ_pin = target::pin_in(target::pins::d50);
   
	// input pins from MT8870
	auto pin0 = target::pin_in(target::pins::d30);
	auto pin1 = target::pin_in(target::pins::d31);
	auto pin2 = target::pin_in(target::pins::d32);
	auto pin3 = target::pin_in(target::pins::d33);

	// instance of MT8870 chip class
	MT8870 DTMF(pin0,pin1,pin2,pin3,STQ_pin);
	
	// instance of TextData object
	TextData user_message(DTMF);
	
	hwlib::wait_ms(800);
	
	uint8_t c; // character variable
	
	while(1){ // wait for the DTMF D
		if (DTMF.available()){
			c = DTMF.get();

			if (c == 0){	// DTMF D
				if (human_readable){
					return user_message.print();
				}
				else{
					return user_message.print_raw();
				}
			}
			else{
				user_message.add(c); 
			}
		
			hwlib::wait_ms(120);
		}
	}
	c = 1;
	return "NOP";
}
