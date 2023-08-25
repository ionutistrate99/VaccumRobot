#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 
#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define DISTANCE_MAX 200 
#define SPEED 400
#define MAX_SPEED_OFFSET 50
#define speedSet 500

NewPing sonar(TRIG_PIN, ECHO_PIN,DISTANCE_MAX); 

AF_DCMotor M1(1, MOTOR12_1KHZ); 
AF_DCMotor M2(2, MOTOR12_1KHZ);
AF_DCMotor M3(3, MOTOR34_1KHZ);
AF_DCMotor M4(4, MOTOR34_1KHZ);
Servo servo;   
boolean goesForward=false;
int distance = 100;

void setup() {
  servo.attach(10);  
  servo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=20)
 {
  MoveStop();
  delay(100);
  MoveBackward();
  delay(300);
  MoveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>distanceL)
  {
    TurnR();
    MoveStop();
  }else
  {
    TurnL();
    MoveStop();
  }
 }else
 {
  MoveForward();
 }
 distance = readPing();
}

int lookRight()
{
    servo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    servo.write(115); 
    return distance;
}

int lookLeft()
{
    servo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    servo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void MoveStop() {
  M1.run(RELEASE); 
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
  } 
  
void MoveForward() {
 if(!goesForward)
  {
    goesForward=true;
    M1.run(BACKWARD);      
    M2.run(BACKWARD);
    M3.run(BACKWARD); 
    M4.run(BACKWARD);     
   {
    M1.setSpeed(speedSet);
    M2.setSpeed(speedSet);
    M3.setSpeed(speedSet);
    M4.setSpeed(speedSet);
    delay(5);
   }
  }
}

void MoveBackward() {
    goesForward=false;
    M1.run(FORWARD);      
    M2.run(FORWARD);
    M3.run(FORWARD);
    M4.run(FORWARD);  
  
  {
    M1.setSpeed(speedSet);
    M2.setSpeed(speedSet);
    M3.setSpeed(speedSet);
    M4.setSpeed(speedSet);
    delay(5);
  }
}  
void TurnR() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);     
  delay(500);
  M3.run(BACKWARD);      
  M4.run(BACKWARD);
  M1.run(BACKWARD);
  M2.run(BACKWARD);      
}  
void TurnL() {
  M3.run(BACKWARD);     
  M4.run(BACKWARD);  
  M1.run(FORWARD);
  M2.run(FORWARD);   
  delay(500);
  M1.run(BACKWARD);      
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}  
