
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
#define V_Pin 5
//пин реле компрессора
#define K_Pin 3
//пин реле тена
#define T_Pin 2


int raw = 0;
int temp = 0;
int Vin = 5;
float Vout = 0;
float R1 = 50000;
float R2 = 0;
float buffer = 0;
boolean Debug = 1;
boolean flag = 0;


// --------- SETUP ----------
void setup()
{
  lcd_init();
  pinMode(V_Pin, OUTPUT);
  pinMode(K_Pin, OUTPUT);
  pinMode(T_Pin, OUTPUT);

  //принудительно выключаем все реле
  Kompressor(0);
  Ten_warm(0);
  Vent(0);

  if (Debug)
  {
    Serial.begin(9600);
  }
}

// ---------- LOOP ----------
void loop()
{
  delay(1000);

  //чтение температуры
  temp = return_temp();

  //  вывод отладочной информации
  debug_info();

  //вывод информации на экран
  lcd_print();


  flag = !flag;
  Kompressor(flag);
  Ten_warm(flag);
  Vent(flag);



}

// --------- ФУНКЦИИ --------
//upr_signal - 1 вкл., 0 - выкл
//реле обратное включение от 0
void Kompressor(boolean upr_signal)
{
  boolean invert = 1;
  if (invert)
  {
    digitalWrite(K_Pin, !upr_signal);
  }
  else
  {
    digitalWrite(K_Pin, upr_signal);
  }
}

//upr_signal - 1 вкл., 0 - выкл
//реле обратное включение от 0
void Ten_warm(boolean upr_signal)
{
  boolean invert = 1;
  if (invert)
  {
    digitalWrite(T_Pin, !upr_signal);
  }
  else
  {
    digitalWrite(T_Pin, upr_signal);
  }
}

//upr_signal - 1 вкл., 0 - выкл
//реле обратное включение от 0
void Vent(boolean upr_signal)
{
  boolean invert = 0;
  if (invert)
  {
    digitalWrite(V_Pin, !upr_signal);
  }
  else
  {
    digitalWrite(V_Pin, upr_signal);
  }
}

int return_temp()
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

  //  вывод градусов
  lcd.setCursor(10, 1);
  lcd.print("F:");
  lcd.setCursor(12, 1);
  lcd.print(flag);

}
