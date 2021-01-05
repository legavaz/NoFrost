#define in1 3     //пин шаг. двигателя 1
#define in2 4     //пин шаг. двигателя 2

#define in3 6     //пин шаг. двигателя 3
#define in4 7     //пин шаг. двигателя 4


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {

rotate_degree(10, 1 , 5);
delay(1000);
rotate_degree(10, -1, 5);

  
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);
//  delay(dl);
//
//  digitalWrite(in1, HIGH);
//  digitalWrite(in2, HIGH);
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, LOW);
//  delay(dl);
//
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);
//  delay(dl);
//
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, LOW);
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, HIGH);
//  delay(dl);
}


//degree - количество циклов поворота
//direct - направление
//del - задержка (мс)
void rotate_degree(int degree, boolean direct, int del)
{

  for ( int i = 0; i < degree; i++)
  {

    digitalWrite(in1, direct);
    digitalWrite(in2, !direct);
    digitalWrite(in3, !direct);
    digitalWrite(in4, direct);
    delay(del);

    digitalWrite(in1, direct);
    digitalWrite(in2, direct);
    digitalWrite(in3, !direct);
    digitalWrite(in4, !direct);
    delay(del);

    digitalWrite(in1, !direct);
    digitalWrite(in2, direct);
    digitalWrite(in3, direct);
    digitalWrite(in4, !direct);
    delay(del);

    digitalWrite(in1, !direct);
    digitalWrite(in2, !direct);
    digitalWrite(in3, direct);
    digitalWrite(in4, direct);
    delay(del);

  }

}
