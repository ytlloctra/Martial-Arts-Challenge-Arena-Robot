int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

int EN1 = 10; //使能端口1
int EN2 = 11; //使能端口2
//数字端口4与5为一组，6与7为另一组
//数字端口10 11 作为直流电机的使能端

void setup()
{
  int i;
  for (i = 4; i <= 7; i++) //为Ardunio 电机驱动板
  pinMode(i, OUTPUT); //设置数字端口4,5,6,7为输出模式

  for (i = 4; i <= 7; i++)
  digitalWrite(i, OUTPUT); //设置数字端口4,5,6,7为HIGH,电机保持不动
  pinMode(10, OUTPUT); //设置数字端口10  11为输出模式
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(EN1, 125);
  analogWrite(EN2, 125);
}

