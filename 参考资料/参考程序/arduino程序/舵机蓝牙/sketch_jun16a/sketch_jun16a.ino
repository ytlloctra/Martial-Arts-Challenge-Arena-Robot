#include <Servo.h>    // 声明调用Servo.h库
Servo myservo1;
Servo myservo2;


int flag = 1;
int pos = 0;          // 变量pos用来存储舵机位置

void setup()
{
  // 设置波特率为 38400
  Serial.begin(9600);

  myservo1.attach(9);  // 将引脚9上的舵机与声明的舵机对象连接起来
  myservo2.attach(8);

  myservo1.write(90);
  myservo2.write(90);
}

void loop()
{
  if (flag == 1)
  {
    for (pos = 180; pos >= 1; pos -= 1) { // 舵机从180°转回到0°，每次减小1°
      myservo1.write(90);  //右边
      myservo2.write(0);
      delay(10);                 // 延时15ms让舵机转到指定位置
    }
    for (pos = 0; pos < 180; pos += 1) {  // 舵机从0°转到180°，每次增加1°
      myservo1.write(0);
      myservo2.write(90);
      delay(10);                    // 延时15ms让舵机转到指定位置
    }
    while (1);
  }
}
