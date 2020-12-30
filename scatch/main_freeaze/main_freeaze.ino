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
String Version = "NF_30-12-20";

#define analogPin 0 //пин переменного сопротивление
#define V_Pin 5     //пин реле вентилятора 12 вольт
#define K_Pin 3     //пин реле компрессора
#define T_Pin 2     //пин реле тена

//переменные для расчета температуры с термистора
#define RESIST_BASE 9800   // сопротивление при TEMP_BASE градусах по Цельсию (Ом)
#define TEMP_BASE 25       // температура, при которой измерено RESIST_BASE (градусов Цельсия)
#define RESIST_50K 50000   // точное сопротивление 10к резистора (Ом)
#define BETA_COEF1 3435

int temp = 0;       //значение текущей температуры
String s_status = "k-/v-/t-";
int temp_max = 30;  //максимальная температура выключения компрессора и включения тэнов
int temp_min = 25;  //минимальная температура
int period_ten_timer = 5 * 60; //время работы тэна 5 минут ()
unsigned long ten_timer; //переменная хранения таймера запуска тэна
boolean ten_on = 0;
boolean k_on = 0;
boolean v_on = 0;

boolean Debug = 1; //флаг отладки
boolean work_flag = 0;


#define len_arr 30
int temp_arr[len_arr]; // массив для расчета средней температуры


// --------- SETUP ----------
void setup()
{
  lcd_init();
  pinMode(V_Pin, OUTPUT);
  pinMode(K_Pin, OUTPUT);
  pinMode(T_Pin, OUTPUT);

  //принудительно выключаем все реле
  Kompressor_rele(0);
  Ten_warm_rele(0);
  Vent_rele(0);

  reset_arr(); // заполним массив значениями по умолчанию для чистоты расчета

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
  temp = return_avg_temp();

  //ОСНОВНАЯ ЛОГИКА ПРОГРАММЫ
  if (temp >= temp_max) {
    Kompressor(1);
  }
  else if (temp <= temp_min) {
    Kompressor(0);
  }

  //оформление текущих статусов для информации
  s_status = "k" + String(k_on) + "/v" + String(v_on) + "/t" + String(ten_on);

  //  вывод отладочной информации
  debug_info();

  //вывод информации на экран
  lcd_print();

}

// --------- ФУНКЦИИ --------

int aver_temp()
{
  int summ = 0;
  int parity = 0;
  for (int i = 0; i < len_arr; i++)
  {
    if (temp_arr[i] > -50)
    {
      summ = summ + temp_arr[i];
      parity += 1;
    }

  }

  //рабочий режим включается при 90% накоплении статистики по температуре
  if (len_arr * 0.9 <= parity) {
    work_flag = 1;
  }

  return summ / parity;

}

void reset_arr()
{
  for (int i = 0; i < sizeof(temp_arr) / sizeof(int); i++)
  {
    temp_arr[i] = -50;
  }

}

void print_arr()
{
  Serial.print("temp_arr: ");

  for (int i = 0; i < sizeof(temp_arr) / sizeof(int); i++)
  {
    Serial.print(";");
    Serial.print(temp_arr[i]);
  }

  Serial.println();

}

void add_array(int m_temp)
{

  for (int i = 0; i < (len_arr - 1); i++)
  {
    temp_arr[i] = temp_arr[i + 1];
  }

  temp_arr[len_arr - 1] = m_temp;


}


void Kompressor(boolean m_value)
{

  //    # сигнал на отключение компрессора
  //    # до этого компрессор был включен
  //    # и тен не работал
  if (k_on == 1 and m_value == 0 and ten_on == 0)
  {
    Kompressor_rele(m_value);
    Vent_rele(0);
    Ten_warm(1);
  }
  //    # сигнал на включение компрессора
  //    # до этого компрессор был выключен
  //    # и тен не работал
  else if (k_on == 0 and m_value == 1 and ten_on == 0)
  {
    Kompressor_rele(m_value);
    Vent_rele(1);
  }
  else
  {
    Ten_warm(0);
  }
}

void Ten_warm(boolean m_value)
{

  if (m_value == 1)
  {
    ten_timer = millis();
    Vent_rele(0);
    Ten_warm(m_value);
  }
  else if (m_value == 0)
  {
    if (ten_timer != 0 and ten_on == 1)
    {
      int r_timer = (millis() - ten_timer) / 1000;
      if (Debug) {
        Serial.print("прошло времени (сек): ");
        Serial.println(r_timer);
      }
      if (r_timer >= period_ten_timer)
      {
        Ten_warm_rele(m_value);
        Vent_rele(1);
      }
    }
  }
}

//upr_signal - 1 вкл., 0 - выкл
//реле обратное включение от 0
void Kompressor_rele(boolean upr_signal)
{
  boolean invert = 1;
  k_on = upr_signal;

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
void Ten_warm_rele(boolean upr_signal)
{
  boolean invert = 1;
  ten_on = upr_signal;
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
void Vent_rele(boolean upr_signal)
{
  boolean invert = 0;
  v_on = upr_signal;

  if (invert)
  {
    digitalWrite(V_Pin, !upr_signal);
  }
  else
  {
    digitalWrite(V_Pin, upr_signal);
  }
}

int return_avg_temp()
{
  temp = return_temp();
  add_array(temp);
  temp = aver_temp();

  return temp;
}


int return_temp()
{
  float thermistor;

  //  чтение данных с аналогового пина
  int resistance = analogRead(analogPin);

  thermistor = RESIST_50K / ((float)1024 / resistance - 1);
  thermistor /= RESIST_BASE;                        // (R/Ro)
  thermistor = log(thermistor) / BETA_COEF1;        // 1/B * ln(R/Ro)
  thermistor += (float)1.0 / (TEMP_BASE + 273.15);  // + (1/To)
  thermistor = (float)1.0 / thermistor - 273.15;    // инвертируем и конвертируем в градусы по Цельсию

  return thermistor;
}

void debug_info()
{
  if (Debug)
  {

    Serial.print("status: ");
    Serial.println(s_status);

    Serial.print("temp: ");
    Serial.println(temp);

    //    Serial.print("w_f: ");
    //    Serial.println(work_flag);

    //    Serial.print("period_ten_timer: ");
    //    Serial.println(period_ten_timer);
    //    Serial.print("ten_on: ");
    //    Serial.println(ten_on);
    Serial.print("ten_timer: ");
    Serial.println(ten_timer);
    Serial.print("millis(): ");
    Serial.println(millis());

    //    print_arr();

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
  //  вывод статуса
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.setCursor(2, 0);
  lcd.print(s_status);

  //  вывод градусов
  lcd.setCursor(0, 1);
  lcd.print("t:");
  lcd.setCursor(3, 1);
  lcd.print(temp);

  //  вывод градусов
  lcd.setCursor(10, 1);
  lcd.print("WF:");
  lcd.setCursor(13, 1);
  lcd.print(work_flag);

}
