// connect motor controller pins to Arduino digital pins
// motor one(
int enA = 8;
int in1 = 9;
int in2 = 10;
// motor two
int enB = 13;
int in3 = 11;
int in4 = 12;
//motor three
int enax = 2;
int in1x = 3;
int in2x = 4;
//motor four
int in3x = 5;
int in4x = 6;
int enbx = 7;

//motor four
void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enax, OUTPUT);
  pinMode(enbx, OUTPUT);
  pinMode(in1x, OUTPUT);
  pinMode(in2x, OUTPUT);
  pinMode(in3x, OUTPUT);
  pinMode(in4x, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in1x, HIGH);
  digitalWrite(in2x, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 250);
  analogWrite(enax, 250);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   digitalWrite(in3x, HIGH);
  digitalWrite(in4x, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 250);
  analogWrite(enbx, 250);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1x, LOW);
  digitalWrite(in2x, HIGH); 
  digitalWrite(in3x, LOW);
  digitalWrite(in4x, HIGH);
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
    digitalWrite(in1x, LOW);
  digitalWrite(in2x, LOW); 
  digitalWrite(in3x, LOW);
  digitalWrite(in4x, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1x, LOW);
  digitalWrite(in2x, HIGH); 
  digitalWrite(in3x, LOW);
  digitalWrite(in4x, HIGH);
  // accelerate from zero to maximum speed
 
 for (int i = 0; i < 250; i++) {
analogWrite(enA, i);
analogWrite(enB, i);
analogWrite(enax, i);
analogWrite(enbx, i);
delay(10);
}
// decelerate from maximum speed to zero
for (int i = 250; i > 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    analogWrite(enax, i);
    analogWrite(enbx, i);
    delay(10);
  }
 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  digitalWrite(in1x, LOW);
  digitalWrite(in2x, LOW); 
  digitalWrite(in3x, LOW);
  digitalWrite(in4x, LOW); 
}
void loop()
{
  demoOne();
  delay(500);
  demoTwo();
  delay(1000);
}
