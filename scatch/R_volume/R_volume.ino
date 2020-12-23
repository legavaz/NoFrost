
/*
  Lega_dvi:23-12-2020
  скетч создан для работы холодилника по принципам NOFROST
  Репозиторий: https://github.com/legavaz/NoFrost.git
  питание:
  gnd - земля
  vcc - 5V
  порты i2c:
  SCL - пин A5
  SDA - пин A4
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки
LiquidCrystal_I2C lcd(0x27,16,2); // Указываем I2C адрес (наиболее распространенное значение), а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой 

int analogPin = 0;
int raw = 0;
int Vin = 5;
float Vout = 0;
float R1 = 50000;
float R2 = 0;
float buffer = 0;

void setup()
{
  lcd.init();                      // Инициализация дисплея
  lcd.backlight();                 // Подключение подсветки
  lcd.setCursor(0, 0);             // Установка курсора в начало первой строки
  lcd.print("scatch:");       // Набор текста на первой строке
  lcd.setCursor(0, 1);             // Установка курсора в начало второй строки
  lcd.print("No Frost");       // Набор текста на второй строке

  Serial.begin(9600);
}

void loop()
{
  raw = analogRead(analogPin);
  if (raw)
  {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
    Serial.print("Vout: ");
    Serial.println(Vout);
    Serial.print("R2: ");
    Serial.println(R2);

    lcd.setCursor(0, 10);             // Установка курсора в начало второй строки
    lcd.print(R2);

    delay(1000);
  }
}
