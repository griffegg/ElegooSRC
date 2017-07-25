//www.elegoo.com
//2016.06.13

#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo
int Echo = A4;  
int Trig = A5; 
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int ENA = 5;
int ENB = 11;
int ABS_r = 130;
int ABS_l = 105;
int ABS_turn = 130;
int rightDistance = 0,leftDistance = 0,middleDistance = 0, right45=0, left45=0 ;
int i;

void _mForward()
{
 analogWrite(ENA,ABS_r);
 analogWrite(ENB,ABS_l);
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 Serial.println("go forward!");
}

void _mBack()
{
 analogWrite(ENA,ABS_r);
 analogWrite(ENB,ABS_l);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 Serial.println("go back!");
}

void _mleft()
{
 analogWrite(ENA,ABS_turn);
 analogWrite(ENB,ABS_turn);
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 Serial.println("go left!");
}

void _mright()
{
 analogWrite(ENA,ABS_turn);
 analogWrite(ENB,ABS_turn);
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 Serial.println("go right!");
} 
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("Stop!");
} 
 /*Ultrasonic distance measurement Sub function*/
int Distance_test()   
{
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}  

void setup() 
{ 
  myservo.attach(3);// attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
} 

void loop() 
{ 
    _mStop();

    myservo.write(90);//setservo position according to scaled value
    delay(100); 
    for(i=0; i <= 4; ++i) {
      middleDistance += Distance_test();
      delay(50); 
    }
    middleDistance /= i;
    Serial.print("middleDistance=");
    Serial.println(middleDistance);

    myservo.write(45);//setservo position according to scaled value
    delay(100); 
    for(i=0; i <= 3; ++i) {
      right45 += Distance_test();
      delay(50); 
    }
    right45 /= i;
    Serial.print("right45=");
    Serial.println(right45);

    myservo.write(135);//setservo position according to scaled value
    delay(100); 
    for(i=0; i <= 3; ++i) {
      left45 += Distance_test();
      delay(50); 
    }
    left45 /= i;
    Serial.print("left45=");
    Serial.println(left45);

    myservo.write(90);//setservo position according to scaled value

    if(middleDistance<=50 || right45<=50 || left45<=50)
    {     
      _mStop();
      delay(300);                         
      _mBack();
      delay(300);
      _mStop();
      delay(500);                         
      myservo.write(5);          
      delay(100);      
      for(i=0; i <= 3; ++i) {
        rightDistance += Distance_test();
        delay(100); 
      }
      rightDistance /= i;
      Serial.print("rightDistance=");
      Serial.println(rightDistance);

      delay(100);                                                  
      myservo.write(180);              
      delay(100); 
      for(i=0; i <= 3; ++i) {
        leftDistance += Distance_test();
        delay(100); 
      }
      leftDistance /= i;
      Serial.print("leftDistance=");
      Serial.println(leftDistance);

      myservo.write(90);    
                
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(100);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(100);
       }
       else if((rightDistance<=30)||(leftDistance<=30))
       {
        _mBack();
        delay(500);
       }
       else
       {
        _mForward();
       }
    }  
    else
        _mForward();   
        delay(500);
                  
}

