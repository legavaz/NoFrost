/*
   базовый скетч отработки нажатия кнопки с фильтром дребезга контактов
   и включением выключением реле / светодиода по нажатию на кнопку
   к уроку #6
*/

#define D_pin 2             // пин двери
#define door_light_pin 10   // пин мосфета / реле

boolean door = 0;           // флажок режима
uint32_t doorTimer = 0;
void setup() {
  pinMode(D_pin, INPUT_PULLUP);       // кнопка подтянута внутренним резистором (урок 5)
  pinMode(door_light_pin, OUTPUT);    // пин реле как выход

  Serial.begin(9600);

}

void loop() {
  delay(1000);

  door_status();

}


void door_status()
{
  boolean door_open = digitalRead(D_pin);  // считать текущее положение конечного выключателя (0-закрыт;1-открыт)

  if (door_open && !door && millis() - doorTimer > 100) {
    door = true;
    doorTimer = millis();
    Serial.println("press");
  }
  if (!door_open && door && millis() - doorTimer > 100) {
    door = false;
    doorTimer = millis();
    //Serial.println("release");
  }


  Door_light_rele(door);
  
  Serial.print("door: ");
  Serial.println(door);

}


//upr_signal - 1 вкл., 0 - выкл
//реле обратное включение от 0
void Door_light_rele(boolean upr_signal)
{
  boolean invert = 0;
  
  if (invert)
  {
    digitalWrite(door_light_pin, !upr_signal);
  }
  else
  {
    digitalWrite(door_light_pin, upr_signal);
  }
}
