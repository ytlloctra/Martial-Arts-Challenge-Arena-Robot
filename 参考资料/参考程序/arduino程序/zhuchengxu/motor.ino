 void move_forward(int speed_right, int speed_left)
 {
    analogWrite(12,255-speed_right);    //P1
    analogWrite(10,255-speed_left);    //P2
    digitalWrite(13,LOW);   //D1
    digitalWrite(11,LOW);   //D2
}

void move_backward(int speed_right, int speed_left, int delay_time)
{
    analogWrite(12,255-speed_right);    //P1
    analogWrite(10,255-speed_left);    //P2
    digitalWrite(13,HIGH);   //D1
    digitalWrite(11,HIGH);   //D2
    delay(delay_time);     
}

void move_rightward(int speed_right,int speed_left, int delay_time)
{
    analogWrite(12,255-speed_right);    //P1
    analogWrite(10,255-speed_left);    //P2
    digitalWrite(13,LOW);   //D1
    digitalWrite(11,HIGH);   //D2
    delay(delay_time);     
}

void move_leftward(int speed_right,int speed_left, int delay_time)
{
    analogWrite(12,255-speed_right);    //P1
    analogWrite(10,255-speed_left);    //P2
    digitalWrite(13,HIGH);   //D1
    digitalWrite(11,LOW);   //D2
    delay(delay_time);     
}


void move_cliff(int speed_right,int speed_left)
{
  analogWrite(12,255-speed_right);       // P1
  analogWrite(10,255-speed_left);        // P2
  digitalWrite(13,LOW);      //D1
  digitalWrite(11,HIGH);       //D2
}

void stop(int delay_time)
{
    analogWrite(12,255);    //P1
    analogWrite(10,255);    //P2
    digitalWrite(13,LOW);   //D1
    digitalWrite(11,LOW);   //D2
    delay(delay_time);     
}


