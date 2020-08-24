
/*
  Данный скетч обеспечивает работу холодильника типа "NoFrost"
  циклическая работа копмрессора и тэна
  by legavaz
*/

//Описание пинов 
#define pin_compressor_rele 10
#define pin_ten_rele 12
#define pin_coller_rele 14

//Описание Переменных 
bool flag_ten_bl;
float val_temp_fl;
int ten_minite;

//
void setup() {
  flag_ten_bl = false
  val_temp_fl = 0;              //20-30 кОм при достижении -10 градусво
  ten_sec_int = 7*(60*60)*1000; //время работы тэна оттайки - 7 минут
  
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
