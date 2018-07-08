#ifndef DTMF_DATA_HPP
#define DTMF_DATA_HPP
#include "hwlib.hpp"

/// @file

/// \brief
/// Minimalist interface to the MT8870 DTMF decoder chip.
/// \details
/// This class implements a 5-wire interface to the MT8870 DTMF module
/// which can be used to detect and decode Dual Tone Multi Frequency signals.
/// The StQ pin is used to detect a signal (it will be logic 1 when a signal
/// is present). The four data pins will represent a DTMF code as a four-bit
/// value (nibble, from 0x00 to 0x0F).

class MT8870 {
protected:
	hwlib::target::pin_in bit_0;
	hwlib::target::pin_in bit_1;
	hwlib::target::pin_in bit_2;
	hwlib::target::pin_in bit_3;
	hwlib::target::pin_in stq;
public:

	/// \brief
	/// Constructor for MT8870 class.
	/// \details
	/// This constructor will initialize a MT8870 object,
	/// it should be given 5 hwlib::target::pin_in variables.
	/// the first four are the data pins (Q1 to Q4 on the module),
	/// and an StQ pin as the fifth.
	MT8870(const hwlib::target::pin_in & bit_0,
			  const hwlib::target::pin_in & bit_1,
			  const hwlib::target::pin_in & bit_2,
			  const hwlib::target::pin_in & bit_3,
			  const hwlib::target::pin_in & stq):
		bit_0(bit_0),
		bit_1(bit_1),
		bit_2(bit_2),
		bit_3(bit_3),
		stq(stq)
		{}

	/// \brief
	/// Check if a signal is available.
	/// \details
	/// This function returns true if a signal is
	/// present, false if no signal is present.
	bool available();

	/// \brief
	/// Gets a signal.
	/// \details
	/// This function returns a byte representing a
	/// DTMF signal if it is present, returns 0 when not.
	/// Because of this it is recommended to call this function
	/// right after available() returns true.
	uint8_t get();
};

#endif // DTMF_DATA_HPP