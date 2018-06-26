//#include <iostream>
 #include "hwlib.hpp"
#include "dtmf.hpp"
#include "TEXT_data.hpp"

namespace target = hwlib::target;

int main(int argc, char **argv)
{

	// kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
      
	// StQ pin (high when a DTMF tone is available)
	auto STQ_pin = target::pin_in(target::pins::d50);
   
	// input pins from MT8870
	auto pin0 = target::pin_in(target::pins::d30);
	auto pin1 = target::pin_in(target::pins::d31);
	auto pin2 = target::pin_in(target::pins::d32);
	auto pin3 = target::pin_in(target::pins::d33);

	// instance of MT8870 chip class
	TEXT_data DTMF(pin0,pin1,pin2,pin3,STQ_pin);

	hwlib::wait_ms(1000); // wait a second for serial comm
	
	hwlib::string<100> test_string = "";
	
	
   while(1){
		if (DTMF.available()){
			uint8_t c = DTMF.get();
			
			if (c == 0){
				hwlib::cout << "message: " << DTMF.print() << '\n';
				DTMF.reset();
			}
			else {
				DTMF.add(c);
			}
			hwlib::wait_ms(130);
		}
   }
}