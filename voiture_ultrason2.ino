#include <IRremote.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

#define echoPin A0 // Echo Pin
#define trigPin A1 // Trigger Pin

String temporaryValue ;
int RECV_PIN = 3;
int In1 = 5;
int In2 = 6;
int In3 = 7;
int In4 = 9;
int m1 = 11;
int m2 = 12;
int m3 = 13;
int mode = 1;
int pos = 0;
int obstacle = 35;
long duration, distance;
long tdevant = 0x00FF629D;
long tderriere = 0x00FFA857;
long tdroite = 0x00FFC23D;
long tgauche = 0x00FF22DD;
long mode1 = 0x00FFB04F;
long mode2 = 0x00FF7A85;
long mode3 = 0x00FF5AA5;
long mode4 = 0x00FF52AD;
long on = 0x00FF02FD;
long off = 0x00FF4AB5;
long STOP = 0x00FF00AA;
int x, y = 0;
byte value = false;
char command;
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  irrecv.enableIRIn();
  mySwitch.enableReceive(0);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  if (results.value == mode1) {
    mode = 1;
  }
  if (results.value == mode2) {
    mode = 2;
  }
  if (results.value == mode3) {
    mode = 3;
  }
  if (results.value == mode4) {
    mode = 4;
  }
  if (results.value == on) {
    value = true;
  }
  if (results.value == off) {
    value = false;
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    digitalWrite(m3, LOW);
    Stop();
  }
  if (value == true) {
    if (mode == 1) {
      Stop();
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      while (results.value == tdevant) {
        avance();
        delay(175);
        results.value = STOP;
      }
      while (results.value == tdroite) {
        droite();
        delay(175);
        results.value = STOP;
      }
      while (results.value == tgauche) {
        gauche();
        delay(175);
        results.value = STOP;
      }
      while (results.value == tderriere) {
        recule();
        delay(175);
        results.value = STOP;
      }
      if (results.value == STOP) {
        digitalWrite(In1, false);
        digitalWrite(In2, false);
        digitalWrite(In3, false);
        digitalWrite(In4, false);
      }
    }
    if (mode == 2) {
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      regarder();
      if (distance > obstacle) {
        avance();
        regarder();
      }
      if (distance <= obstacle) {
        recule();
        delay(150);
        droite();
        delay(650);
        Stop();
        delay(50);
        regarder();
        if (distance > obstacle) {
          avance();
          regarder();
        }
        if (distance <= obstacle) {
          recule();
          delay(150);
          gauche();
          delay(1300);
          Stop();
          delay(50);
          regarder();
        }
        if (distance > obstacle) {
          avance();
          regarder();
        }
        if (distance <= obstacle) {
          recule();
          delay(150);
          gauche();
          delay(650);
          Stop();
          delay(50);
          regarder();
        }
        if (distance > obstacle) {
          avance();
          regarder();
        }
      }
    }
    if (mode == 3) {
      Stop();
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      if (Serial.available() > 0) {
        command = Serial.read();
        Stop();
        switch (command) {
          case 'F':
            avance();
            delay(18);
            break;
          case 'B':
            recule();
            delay(18);
            break;
          case 'R':
            droite();
            delay(18);
            break;
          case 'L':
            gauche();
            delay(18);
            break;
        }
      }
    }
    if (mode == 4) {
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, HIGH);
      Stop();
      if (mySwitch.available()) {
        temporaryValue = String(mySwitch.getReceivedValue());
        if (temporaryValue.substring(0, 3) == "999") {
          x = temporaryValue.substring(3).toInt() ;
        }
        if (temporaryValue.substring(0, 3) == "888") {
          y = temporaryValue.substring(3).toInt() ;
        }
        //Serial.print(x);
        //Serial.println(y);
        //delay(100);
        if (x < 100) {
          gauche();
          delay(5);
        }
        if (x > 400) {
          droite();
          delay(5);
        }
        if (y < 100) {
          avance();
          delay(5);
        }
        if (y > 400) {
          recule();
          delay(5);
        }
        if (x > 101 && x < 399 || y > 101 && y < 399) {
          Stop();
        }
      }
    }
  }
}
void regarder() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
}
void avance() {
  digitalWrite(In1, true);
  digitalWrite(In2, false);
  digitalWrite(In3, true);
  digitalWrite(In4, false);
}

void recule() {
  digitalWrite(In1, false);
  digitalWrite(In2, true);
  digitalWrite(In3, false);
  digitalWrite(In4, true);
}

void droite() {
  digitalWrite(In1, true);
  digitalWrite(In2, false);
  digitalWrite(In3, false);
  digitalWrite(In4, false);
}

void gauche() {
  digitalWrite(In1, false);
  digitalWrite(In2, false);
  digitalWrite(In3, true);
  digitalWrite(In4, false);
}
void Stop() {
  digitalWrite(In1, false);
  digitalWrite(In2, false);
  digitalWrite(In3, false);
  digitalWrite(In4, false);
}
