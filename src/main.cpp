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

	// setup for OLED display (i2c)
	auto scl     = target::pin_oc( target::pins::scl ); // Serial clock
	auto sda     = target::pin_oc( target::pins::sda ); // Serial data
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda ); // i2c bus
	auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 	// OLED display
	auto font    = hwlib::font_default_8x8();			// OLED font size
	auto display = hwlib::window_ostream( oled, font );	// output stream to window


	hwlib::wait_ms(1000); // wait a second for serial comm
	oled.clear();         // refresh oled 

	/* Main control loop, must never exit (embedded application). *
	 * in this loop we will continously wait for a DTMF signal,   *
	 * if a signal is present we will add it to the user message  *
	 * or we will print the message when a DTMF 'D' is detected   */
	while(1){
		if (DTMF.available()){
			uint8_t c = DTMF.get();
			
			if (c == 0){	// DTMF D
				oled.clear();
				display << '\f' << user_message.print() << '\n' << hwlib::flush;
				user_message.reset();
			}
			else{
				user_message.add(c); 
			}
			
			hwlib::wait_ms(120);
		}
   }
}
  