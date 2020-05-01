//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#include<Servo.h>
Servo myservo;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define carSpeed 90
#define turnspeed 190

int Echo = A4;
int Trig = A5;

int distance=0;
int find_line=0;

void forward()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back()
{
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left()
{
  analogWrite(ENA, turnspeed);
  analogWrite(ENB, turnspeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right()
{
  analogWrite(ENA, turnspeed);
  analogWrite(ENB, turnspeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop()
{
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

int find_distance()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  return (int)pulseIn(Echo, HIGH)/58;
}

void setup()
{
  myservo.attach(3);
  Serial.begin(9600);
  pinMode(10,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT);
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
}

void loop() 
{
  myservo.write(90);
  
  
  forward();
  
  if(LT_R or LT_L or LT_M)
  {
    find_line=1;
  }
  while(find_line==1)
  {
    if(LT_M)
    {
      //distance= find_distance();
      forward();
    }
    else if(LT_R) 
    {
      while(!LT_M)
      {
        right();
      }                           
    }   
    else if(LT_L) 
    {
      while(!LT_M)
      {
        left();
      }
    }
    else if(!LT_R and !LT_M and !LT_L)
    {
      forward();
      delay(500);
      if(!LT_R and !LT_M and !LT_L)
      {
        stop();
        back();
        delay(500);
        right();
        while(!LT_R);
      }
    }//end of if where the line ends and it detects back
    if(LT_R and LT_L and LT_M)
    {
      forward();
      delay(200);
      if(LT_R and LT_L and LT_M)
      {
        stop();
        while(1);
      }
      else
      {
        right();
        while(!LT_R);
      }
    }// end of if
    if(LT_M and LT_R)
    {
      while(!LT_M)
      {
        right();
      }  
    }//end of if
    
    else if(distance<=25)
    {
      delay(500);
      stop();
      left();
      while(!LT_L);
      
    }// end for obstacle
    distance=find_distance();
  }// end of while(findings==1)
}//end of void loop()
