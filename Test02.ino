int trig2 = A2;
int echo2 = A3;
int trig1 = A1;
int echo1 = A0;
int trig3 = A4;
int echo3 = A5;

int IN1 = 5;
int IN2 = 3;
int IN3 = 9;
int IN4 = 10;
int ENA = 6;
int ENB = 11;
int LeftSpeed = 208;
int RightSpeed = 175;

// Khai báo khoảng cách, thời gian
long pingTime2, middleDistance, pingTime1, leftDistance, pingTime3, rightDistance;

void setup() {
pinMode(trig2, OUTPUT);
pinMode(echo2, INPUT);
pinMode(trig1, OUTPUT);
pinMode(echo1, INPUT);
pinMode(trig3, OUTPUT);
pinMode(echo3, INPUT);

pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);

Serial.begin(9600);
}

void loop() {
// Đọc sensor và tính khoảng cách
digitalWrite(trig2, LOW);
delayMicroseconds(2);
digitalWrite(trig2, HIGH);
delayMicroseconds(5);
digitalWrite(trig2, LOW);
pingTime2 = pulseIn(echo2, HIGH);
middleDistance = pingTime2 / 29 / 2;

digitalWrite(trig1, LOW);
delayMicroseconds(2);
digitalWrite(trig1, HIGH);
delayMicroseconds(5);
digitalWrite(trig1, LOW);
pingTime1 = pulseIn(echo1, HIGH);
leftDistance = pingTime1 / 29 / 2;

digitalWrite(trig3, LOW);
delayMicroseconds(2);
digitalWrite(trig3, HIGH);
delayMicroseconds(5);
digitalWrite(trig3, LOW);
pingTime3 = pulseIn(echo3, HIGH);
rightDistance = pingTime3 / 29 / 2;

Serial.print(rightDistance);
Serial.print(":");
Serial.print(middleDistance);
Serial.print(":");
Serial.println(leftDistance);

if (rightDistance > 7 && leftDistance <= 7 && middleDistance > 3) {
right(100);
}
else if (leftDistance > 7 && rightDistance <= 7 && middleDistance > 3) {
left(20);
}
else if (middleDistance <= 7) {
back(50);
}
else {
bamtrai();
}
}

void right(int a) {
analogWrite(ENA, LeftSpeed);
analogWrite(ENB, RightSpeed);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
delay(a);
}

void Stop (int a) {
analogWrite(ENA, 0);
analogWrite(ENB, 0);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
delay(a);
}
void left(int a) {
analogWrite(ENA,LeftSpeed);
analogWrite(ENB,RightSpeed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
delay(a);
}

void forward() {
analogWrite(ENA,LeftSpeed);
analogWrite(ENB,RightSpeed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}

void back(int a){
analogWrite(ENA,LeftSpeed);
analogWrite(ENB,RightSpeed);
digitalWrite(IN1, LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
delay(a);
}

void bamtrai(){
if (leftDistance < 5){
right(3);
}
if (leftDistance > 5){
left(3);
}
}

