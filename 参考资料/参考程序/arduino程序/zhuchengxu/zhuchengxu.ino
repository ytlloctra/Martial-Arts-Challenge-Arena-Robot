//#include <IRremote.h>
//#include <Servo.h>
//Servo myservo1;  //头
//Servo myservo2;  //左手
//Servo myservo3;  //右手

int IR_hi=0;
int IR_forward1;
int IR_forward2;
int IR_left1;
int IR_left2;
int IR_right1;
int IR_right2;
int IR_backward1;
int IR_backward2;
int IR_cliff1;
int IR_cliff2;
int flag=0;

int speed_fast = 200;      //冲撞
int speed_normal = 100;    //正常
int speed_turn = 180;     //转弯
void setup()                                                                                                                
{

// myservo1.attach(A0);
// myservo2.attach(A1);
// myservo3.attach(A3);
 
  pinMode(A2,INPUT);     //红外
  pinMode(10,OUTPUT);    // P2
  pinMode(11,OUTPUT);    //D2
  pinMode(12,OUTPUT);    //P1
  pinMode(13,OUTPUT);    //D1

  pinMode(31,INPUT);//定义红外的接口
  pinMode(33,INPUT);
  pinMode(35,INPUT);
  pinMode(37,INPUT);
  pinMode(39,INPUT);
  pinMode(41,INPUT);
  pinMode(43,INPUT);
  pinMode(45,INPUT);
  pinMode(47,INPUT);
  pinMode(49,INPUT);

  digitalWrite(31,HIGH);   
  digitalWrite(33,HIGH);
  digitalWrite(35,HIGH);
  digitalWrite(37,HIGH);   
  digitalWrite(39,LOW);  //悬崖
  digitalWrite(41,HIGH);
  digitalWrite(43,HIGH);
  digitalWrite(45,LOW);  //悬崖
  digitalWrite(47,HIGH);
  digitalWrite(49,HIGH);
                       
  }
void loop()
{
  IR_forward1  = digitalRead(41);
  IR_forward2  = digitalRead(43); 
  IR_left1     = digitalRead(31);
  IR_left2     = digitalRead(47);
  IR_right1    = digitalRead(33);
  IR_right2    = digitalRead(49);
  IR_backward1 = digitalRead(35);
  IR_backward2 = digitalRead(37);
  IR_cliff1    = digitalRead(39);
  IR_cliff2    = digitalRead(45); 
 //stop(20);
//while(1); 
    
      if((IR_forward1 == LOW) ||  (IR_forward2 == LOW))    //forward straight  扫到障碍物 前红外亮 低电平
      {
        move_forward(speed_fast,speed_fast);
      }

      if((IR_forward1 == HIGH) && (IR_forward2 == HIGH))
        {
           move_forward(speed_normal,speed_normal);
        }
      if((IR_left1 == LOW) ||  (IR_left2 == LOW))    //forward straight
      {
        move_leftward(speed_turn,speed_turn,300);
      }

      if((IR_right1 == LOW) ||  (IR_right2 == LOW))    //forward straight
      {
        move_rightward(speed_turn,speed_turn,300);
      }

        
        
      if((IR_cliff1 == HIGH))    //deep cliff left
      {
        stop(20);
        move_backward(120,120,200);
        stop(40);
        move_rightward(speed_turn,speed_turn,300);    
      }
      
      if((IR_cliff2 == HIGH))    //deep cliff right
      {
         stop(20);
        move_backward(120,120,200);
         stop(40);
        move_leftward(speed_turn,speed_turn,300);       
      }
      if((IR_cliff1 == HIGH) && (IR_cliff2 == HIGH))    //deep cliff left  both
      {
         stop(20);
        move_backward(120,120,200);
         stop(40);
        move_rightward(speed_turn,speed_turn,300);    
      }
      if(((IR_left1 == LOW) ||(IR_left2 == LOW)) && ((IR_cliff1 == HIGH) && (IR_cliff2 == LOW)))
       {
        stop(20);
        move_backward(80,80,190);
         stop(40);
         move_rightward(speed_turn,speed_turn,170); 
       }
      if(((IR_left1 == LOW) ||(IR_left2 == LOW)) && ((IR_cliff1 == LOW) && (IR_cliff2 == HIGH)))
      {
        stop(20);
        move_backward(80,80,190);
         stop(40);
         move_leftward(speed_turn,speed_turn,170); 
       }
      
      if(((IR_right1 == LOW) || (IR_right2 == LOW)) && ((IR_cliff1 == HIGH) && (IR_cliff2 == LOW)))
      {
        stop(20);
        move_backward(80,80,190);
         stop(40);
        move_rightward(speed_turn,speed_turn,170); 
       }
      if(((IR_right1 == LOW) || (IR_right2 == LOW)) && ((IR_cliff1 == LOW) && (IR_cliff2 == HIGH)))
      {
        stop(20);
        move_backward(80,80,190);
         stop(40);
        move_leftward(speed_turn,speed_turn,170); 
       }
        
      if((IR_backward1 == LOW) ||(IR_backward2 == LOW))
      {
        move_rightward(200,200,400); 
       }
}
    


   

