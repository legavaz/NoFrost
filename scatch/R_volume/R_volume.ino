
/*
  Lega_dvi:23-12-2020
  скетч создан для работы холодилника по принципам NOFROST
  Репозиторий: https://github.com/legavaz/NoFrost.git

*/

// ------- БИБЛИОТЕКИ -------
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Подключение библиотеки


// ------- ПЕРЕМЕННЫЕ -------
LiquidCrystal_I2C lcd(0x27, 16, 2); // Указываем I2C адрес (наиболее распространенное значение),
//а также параметры экрана (в случае LCD 1602 - 2 строки по 16 символов в каждой
String author = "legavaz@gmail.com";
String Version = "NF_23-12-20";
//пин переменного сопротивление
int analogPin = 0;

//пин реле вентилятора 12 вольт
int V_Pin = 4;
//пин реле компрессора
int K_Pin = 3;
//пин реле тена
int T_Pin = 2;


int raw = 0;
int temp = 0;
int Vin = 5;
float Vout = 0;
float R1 = 50000;
float R2 = 0;
float buffer = 0;
int  Debug = 1;
int flag = 1;


// --------- SETUP ----------
void setup()
{
  lcd_init();

  Serial.begin(9600);
}

// ---------- LOOP ----------
void loop()
{
  delay(1000);

  //чтение температуры
  temp = ret_temp();

  //  вывод отладочной информации
  debug_info();

  //вывод информации на экран
  lcd_print();

  if (temp >= 27)
  {
    flag = 0;
    digitalWrite(V_Pin, HIGH);
    digitalWrite(K_Pin, HIGH);
    digitalWrite(T_Pin, HIGH);
  }
  else
  {
    digitalWrite(V_Pin, LOW);
    digitalWrite(K_Pin, LOW);
    digitalWrite(T_Pin, LOW);
    delay(2000);
    flag = 1;
  }


}

// --------- ФУНКЦИИ --------

int ret_temp()
{
  //  обнуление переменной сопротивления
  R2 = 0;
  //  чтение данных с аналогового пина
  raw = analogRead(analogPin);
  if (raw)
  {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;
  }

  int temp = 999;
  temp = R2 * 0.00009058;
  if (R2 < 100000)
  {
    temp = -temp;
  }
  return temp;
}

void debug_info()
{
  if (Debug)
  {
    Serial.print("Vout: ");
    Serial.println(Vout);
    Serial.print("R2: ");
    Serial.println(R2);

    Serial.print("temp: ");
    Serial.println(temp);

    Serial.print("flag: ");
    Serial.println(flag);

  }

}

void lcd_init()
{
  lcd.init();                 // Инициализация дисплея
  lcd.backlight();            // Подключение подсветки

  lcd.setCursor(0, 0);        // Установка курсора в начало первой строки
  lcd.print(Version);         // вывод версии скетча

  lcd.setCursor(0, 1);        // Установка курсора в начало первой строки
  lcd.print(author);         // вывод авторства


  delay(2000);

}

void lcd_print()
{
  lcd.clear();

  //  вывод значения сопротивленя
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.setCursor(3, 0);
  lcd.print(int(R2 / 1000));

  //  вывод градусов
  lcd.setCursor(0, 1);
  lcd.print("t:");
  lcd.setCursor(3, 1);
  lcd.print(temp);

}
