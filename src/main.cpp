#include "hwlib.hpp"
#include "dtmf.hpp"
#include "TextData.hpp"

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
	MT8870 DTMF(pin0,pin1,pin2,pin3,STQ_pin);
	
	// instance of TextData object
	TextData user_message(DTMF);

	hwlib::wait_ms(1000); // wait a second for serial comm

	/* Main control loop, must never exit (embedded application). *
	 * in this loop we will continously wait for a DTMF signal,   *
	 * if a signal is present we will add it to the user message  *
	 * or we will print the message when a DTMF 'D' is detected   */
	while(1){
		if (DTMF.available()){
			uint8_t c = DTMF.get();
			
			if (c == 0){	// DTMF D
				hwlib::cout << "raw data: " << user_message.print_raw() << '\n';
				hwlib::cout << "message: " << user_message.print() << '\n';
				user_message.reset();
			}
			
			else if (c == 15){ // DTMF C
				user_message.add('%');
			}
			
			else{
				user_message.add(c);
			}
			
			hwlib::wait_ms(120);
		}
   }
}
  