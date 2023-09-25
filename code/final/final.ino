#include <Servo.h>
Servo myservo;

int l_fsensor = 13; //SENSORS
int f_fsensor = 12;
int r_fsensor = 11;

int pump = 10; //MOTORS
int LM1 = 9;
int LM2 = 8;
int RM1 = 7;
int RM2 = 6;   

int r_flame = 0; //CHECKING FIRE
int f_flame = 0;
int l_flame = 0;
int servo_pos = 0; //POSITION OF ROTATE MOTOR

int trigPin = 3; //ULRTA SONIC
int echoPin = 2; 
float duration, distance;
int led = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(pump, HIGH);
  pinMode(l_fsensor, INPUT);
  pinMode(r_fsensor, INPUT);
  pinMode(f_fsensor, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  myservo.attach(5);
  myservo.write(90); 

  pinMode(trigPin, OUTPUT);      
  pinMode(echoPin, INPUT);          
}

void check_distance() {
  delay(300);
  digitalWrite(trigPin, HIGH);     //SEND WAVE FOR 10 MICROS
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //RECIEVE WAVE
  distance = duration / 58.2;   //DISTANCE
  Serial.println(distance);
  delay(100);

  if (distance < 400)            
  {
    digitalWrite(led, HIGH);
    digitalWrite(LM1, HIGH); //STOP
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    delay(200);
    digitalWrite(LM1, HIGH); //BACK
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW); 
    delay(200);
    digitalWrite(LM1, HIGH); //STOP
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH); 
    delay(200);  
    digitalWrite(LM1, LOW); //ROTATE RIGHT
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH); 
    delay(200);
    digitalWrite(LM1, LOW); //FORWARD
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    delay(200);
    digitalWrite(led, LOW);                                                     
  }   
}

void fire_detected() {  
  digitalWrite(LM1, HIGH); //STOP
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  digitalWrite(pump,LOW); //START PUMP AND ROTATE
  for (servo_pos = 50; servo_pos <= 130; servo_pos += 1) { 
    myservo.write(servo_pos); 
    delay(10);  
  }
  for (servo_pos = 130; servo_pos >= 50; servo_pos -= 1) { 
    myservo.write(servo_pos); 
    delay(10);
  }

  digitalWrite(pump,HIGH); //STOP PUMP AND CHECK AGAIN
  myservo.write(90);
}

void loop() { 
  f_flame = digitalRead(f_fsensor); //FLAME SENSORS
  r_flame = digitalRead(r_fsensor);
  l_flame = digitalRead(l_fsensor);

  if (f_flame == 1 && r_flame == 1 && l_flame == 1) { //CHECK FLAME DIRECTION
    digitalWrite(LM1, HIGH); //NO FIRE 
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  } else if (f_flame == 0){
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    check_distance();
    fire_detected();
  } else if (r_flame == 0){
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    delay(300);    
    fire_detected();
  } else if (l_flame == 0){
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    delay(300);
    fire_detected();
  }
}
