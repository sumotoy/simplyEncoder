#include "simplyEncoder.h"

const uint8_t simplyEncoder::cwB[4] = {2,0,3,1};
const uint8_t simplyEncoder::ccwB[4] = {1,3,0,2};
const uint8_t simplyEncoder::cwA[4] = {3,0,2,1};
const uint8_t simplyEncoder::ccwA[4] = {1,2,0,3};
			
			
void simplyEncoder::setup(const uint8_t a, const uint8_t b,bool pullup, uint8_t decoderType) {
	_pinA = a;
	_pinB = b;
	if (decoderType > 1) decoderType = 1;
	_decoding = decoderType;
	pinMode(_pinA, INPUT);
	pinMode(_pinB, INPUT);
	if (pullup){
		digitalWrite(_pinA, HIGH);
		digitalWrite(_pinB, HIGH);
	}
	_state = 0;
	_prevState = 0;
	_count = 0;
	_cycleCount = 0;
}



int simplyEncoder::read() {
	int dir = 0;
#if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MKL26Z64__)
	const byte a = digitalReadFast(_pinA);
	const byte b = digitalReadFast(_pinB);
#else
	const byte a = digitalRead(_pinA);
	const byte b = digitalRead(_pinB);
#endif
	_state = (a << 1 | b);
	if (_state != _prevState) {
		if (_decoding == 0){
			if (_state == cwA[_prevState]) {
				_cycleCount++;//  forward
			} else if (_state == ccwA[_prevState]) {
				_cycleCount--;//  backward
			}
		} else {
			if (_state == cwB[_prevState]) {
				_cycleCount++;//  forward
			} else if (_state == ccwB[_prevState]) {
				_cycleCount--;//  backward
			}
		}
		if (_state == 3) {
			if (_cycleCount > 0) {
				_count++;
				dir = 1;
			} else if(_cycleCount < 0) {
				_count--;
				dir = -1;
			}
			_cycleCount = 0;
		}
		_prevState = _state;
	}
	return dir;
}

