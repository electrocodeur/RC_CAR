/*#include <RCSwitch.h>
  RCSwitch mySwitch = RCSwitch();
  int JoyStick_X = A0; //x
  int JoyStick_Y = A1; //y
  void setup() {
  mySwitch.enableTransmit(10);
  Serial.begin(9600);
  }

  void loop() {
  int x, y;
  x = analogRead(JoyStick_X);
  y = analogRead(JoyStick_Y);
  Serial.println(x);
  Serial.println(y);
  if (x < 350) {
    mySwitch.send((999000), 23);
  }
  if (x > 650) {
    mySwitch.send((888000), 24);
  }
  if (y < 350) {
    mySwitch.send((777000), 24);
  }
  if (y > 640) {
    mySwitch.send((666000), 24);
  }
  if (x > 351 && x < 649 || y > 351 && y < 639) {
    mySwitch.send((555000), 24);
  }
  }
*/
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int JoyStick_X = PA0; //x
int JoyStick_Y = PA1; //y
void setup() {
  mySwitch.enableTransmit(PA10);
  Serial.begin(9600);
}

void loop() {
  int x, y;
  x = analogRead(JoyStick_X) / 8;
  y = analogRead(JoyStick_Y) / 8;
  mySwitch.send((999000 + x), 24);
  mySwitch.send((888000 + y), 24);
  //Serial.print(x);
  Serial.println(y);
}
/*#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
int JoyStick_X = A0; //x
int JoyStick_Y = A1; //y
void setup() {
  mySwitch.enableTransmit(10);
  Serial.begin(9600);
}

void loop() {
  int x, y;
  x = analogRead(JoyStick_X) / 2;
  y = analogRead(JoyStick_Y) / 2;
  mySwitch.send((999000 + x), 24);
  mySwitch.send((888000 + y), 24);
  //Serial.print(x);
  Serial.println(y);
}*/
