#include "simplyEncoder.h"

#if defined(__FASTSPI)
#include <../digitalWriteFast/digitalWriteFast.h>
#endif

const uint8_t simplyEncoder::cwB[4] = {2,0,3,1};
const uint8_t simplyEncoder::ccwB[4] = {1,3,0,2};
const uint8_t simplyEncoder::cwA[4] = {3,0,2,1};
const uint8_t simplyEncoder::ccwA[4] = {1,2,0,3};
			
			
void simplyEncoder::setup(const uint8_t pinA, const uint8_t pinB,bool pullup, uint8_t decoderType) {
	this->pinA = pinA;
	this->pinB = pinB;
	if (decoderType > 1) decoderType = 1;
	this->_decoding = decoderType;
	pinMode(this->pinA, INPUT);
	pinMode(this->pinB, INPUT);
	if (pullup){
		digitalWrite(this->pinA, HIGH);
		digitalWrite(this->pinB, HIGH);
	}
	this->state = 0;
	this->prevState = 0;
	this->count = 0;
	this->cycleCount = 0;
}



int simplyEncoder::read() {
	int dir = 0;
#if defined(__FASTSPI)
	const byte a = digitalReadFast(this->pinA);
	const byte b = digitalReadFast(this->pinB);
#else
	const byte a = digitalRead(this->pinA);
	const byte b = digitalRead(this->pinB);
#endif
	this->state = (a << 1 | b);
	if (state != prevState) {
		if (this->_decoding == 0){
			if (state == cwA[prevState]) {
				cycleCount++;//  forward
			} else if (state == ccwA[prevState]) {
				cycleCount--;//  backward
			}
		} else {
			if (state == cwB[prevState]) {
				cycleCount++;//  forward
			} else if (state == ccwB[prevState]) {
				cycleCount--;//  backward
			}
		}
		if (state == 3) {
			if (cycleCount > 0) {
				count++;
				dir = 1;
			} else if(cycleCount < 0) {
				count--;
				dir = -1;
			}
			cycleCount = 0;
		}
		prevState = state;
	}
	return dir;
}

