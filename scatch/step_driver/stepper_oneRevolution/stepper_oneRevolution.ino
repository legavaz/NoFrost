
#include <Stepper.h>

// initialize the stepper library on pins (74 63) - попарно катушкам (прозвониваются)
//210 - скорость ш.двиг. (подбирается индивидуально, по умолчанию 200)
Stepper myStepper(210, 9, 10, 11, 12);
boolean flap_close = 1; //флаг открытия заслонки

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  Serial.print("посылаем сигнал закрытия");
  flap(1);
  delay (5000);

  Serial.print("посылаем сигнал открытия");
  flap(-1);
}


void flap(int dir)
{

  Serial.print("dir: ");
  Serial.println(dir);
  Serial.print("flap_close: ");
  Serial.println(flap_close);

  int steps = 1700;

  if (dir == 1 and flap_close == 0)
  {
    Serial.println("Закрываем");
    myStepper.step(steps * dir);
    flap_close = !flap_close;
  }
  else if (dir == -1 and flap_close == 1)
  {
    Serial.println("открываем");
    myStepper.step(steps * dir);
    flap_close = !flap_close;
  }

  delay(100);
}
