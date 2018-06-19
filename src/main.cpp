//#include <iostream>
#include "hwlib.hpp"
#include "dtmf.hpp"

namespace target = hwlib::target;

int main(int argc, char **argv)
{

	// kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
	DTMF_data DTMF;
   
	// StQ pin (high when a DTMF tone is available)
	auto STQ_in = target::pin_in(target::pins::d50);
   
	// input pins from MT8870
	auto pin0 = target::pin_in(target::pins::d30);
	auto pin1 = target::pin_in(target::pins::d31);
	auto pin2 = target::pin_in(target::pins::d32);
	auto pin3 = target::pin_in(target::pins::d33);

	// collect pins in port_in_from_pins structure
	auto data_in = hwlib::port_in_from_pins(pin0,
											pin1,
											pin2,
											pin3);

	hwlib::wait_ms(1000); // wait a second for serial comm
	
   while(1){
		if (STQ_in.get()){
			switch(data_in.get()){
				case 1:				// DTMF 1
					DTMF.add('1');
					hwlib::wait_ms(140);
					break;
				case 2:				// DTMF 2
					DTMF.add('2');
					hwlib::wait_ms(140);
					break;
				case 3:				// DTMF 3
					DTMF.add('3');
					hwlib::wait_ms(140);
					break;
				case 4:				// DTMF 4
					DTMF.add('4');
					hwlib::wait_ms(140);
					break;
				case 5:				// DTMF 5
					DTMF.add('5');
					hwlib::wait_ms(140);
					break;
				case 6:				// DTMF 6
					DTMF.add('6');
					hwlib::wait_ms(140);
					break;
				case 7:				// DTMF 7
					DTMF.add('7');
					hwlib::wait_ms(140);
					break;
				case 8:				// DTMF 8
					DTMF.add('8');
					hwlib::wait_ms(140);
					break;
				case 9:				// DTMF 9
					DTMF.add('9');
					hwlib::wait_ms(140);
					break;
				case 10:			// DTMF 0
					DTMF.add('0');
					hwlib::wait_ms(140);
					break;
				case 0:		// DTMF D
					hwlib::cout << "message: " << DTMF.print() << '\n';
					DTMF.reset(); // clear DTMF_message string
					hwlib::wait_ms(50);
					break;
			}
		}
   }
}