#define MotorA0    5  //A1A핀에 연결
#define MotorA1    6  //A1B핀에 연결
#define MotorB0   9  //B1A핀에 연결
#define MotorB1   10 //B1B핀에 연결

#include <Servo.h>
#include <NewPing.h>
Servo servo;
const int servoPin = 11;
const int TRIG = A4;
const int ECHO = A5;
const int TRIG2 = A2;
const int ECHO2 = A3;
int distance1, distance2;
const int MAX_DISTANCE = 200;

NewPing sonar[2] = {
  NewPing(TRIG, ECHO, MAX_DISTANCE),
  NewPing(TRIG2, ECHO2, MAX_DISTANCE),
};

int state = 3;
int angle = 90;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(angle);
  delay(1000);  
}
// DC 모터 전진
void forward()
{
    analogWrite(MotorA1,200);

    analogWrite(MotorB1,200);

    analogWrite(MotorA0,0);

    analogWrite(MotorB0,0);
}
// DC 모터 후진
void backward()
{
    analogWrite(MotorA1,0);

    analogWrite(MotorB1,0);

    analogWrite(MotorA0,200);

    analogWrite(MotorB0,200);
}
// DC 모터 우회전
void turnright()
{
    analogWrite(MotorA1,200);

    analogWrite(MotorB1,0);

    analogWrite(MotorA0,0);

    analogWrite(MotorB0,200);
}
// DC 모터 좌회전
void turnleft()
{
    analogWrite(MotorA1,0);

    analogWrite(MotorB1,200);

    analogWrite(MotorA0,200);

    analogWrite(MotorB0,0);
}


void loop() {
  servo.write(angle);
  delay(50);
  
  distance1 = sonar[0].ping_cm();
  distance2 = sonar[1].ping_cm();

  // 장애물 탐지 시 동작 
  if (0 < distance1 && distance1 < 20)
  {
    // 후진
    backward();
    delay(750);
    // 좌측 장애물 우회전
    if (angle >= 90) 
    {
      turnright();
      delay(500);
    }
    // 우측 장애물 좌회전
    else
    {
      turnleft();
      delay(500);
    }
    // 초음파 센서 재정렬
    angle = 90;
    servo.write(angle);
    delay(250);
    forward();
  }
  else 
  {
    forward();
  }
  // 초음파 센서 회전
  if (angle > 140) state = -10;    
  else if (angle< 40) state = 10; 
  angle += state;
}
