#include <simplyEncoder.h>
/*
Ultrasimple library for encoders, works with no hassle with most encoders and micros,
doesn't use any strange feature so it will always work, no interrupts, no timers.
Good for interface rotary encoders where high precision it's not a priority!
*/
simplyEncoder enc;

void setup()
{
  Serial.begin(38400);
  //pin A, pin B, pullup, decoding mode (0,1)
  //pullup must be false if you already have pullup resistors on
  //pin A and B!!!!!
  enc.setup(18,19,true,0);
}

void loop()
{
  int dir = enc.read();
  if (dir) {
    if (dir > 0) {
      Serial.println("right");
    }
    else {
      Serial.println("left");
    }
  }

}