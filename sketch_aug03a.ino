#define enA 6 
#define in1 2
#define in2 3
#define enB 9
#define in3 4 
#define in4 5 

int rightPin = 11;
int middlePin = 12;
int leftPin = 13;

int Echo1 = A4; //LEFT_SENSOR ECHO
int Trig1 = A5; //LEFT_SENSOR TRIG
int Echo2 = A2; //MID_SENSOR ECHO
int Trig2 = A3; //MID_SENSOR TRIG
int Echo3 = A0; //RIGHT_SENSOR ECHO
int Trig3 = A1; //RIGHT_SENSOR TRIG
int Left_Distance = 0, Right_Distance = 0, Middle_Distance = 0;

int switch1pin = 7;
int switch2pin = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(leftPin, INPUT);
  pinMode(middlePin, INPUT);
  pinMode(rightPin, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig3, OUTPUT);

  pinMode(switch1pin, INPUT);
  pinMode(switch2pin, INPUT);
}

void loop()
{
  int switch1 = digitalRead(switch1pin);
  int switch2 = digitalRead(switch2pin);
//ultrasonic sensor mode
  if (switch1 == LOW)
  {
    Left_Distance = Left_Distance_test();
    Middle_Distance = Middle_Distance_test();
    Right_Distance = Right_Distance_test();
    if (Middle_Distance < 16)
    {
      stopCar(0);
      delay(100);
      backwardCar(100);
      delay(1000);
      backRight(100);
      delay(2000);
    
     else if (Right_Distance < 16)
    {
      stopCar(0);
      delay(200);
      backRight(100);
      delay(2000);
    }
    else if (Left_Distance < 16)
    {
      stopCar(0);
      delay(200);
      backLeft(100);
      delay(2000);
    }
    else if (Middle_Distance > 16 & Left_Distance > 16 & Right_Distance > 16)
    {
      forwardCar(100);
    }
  }
  else
  
    stopCar(0);
  }

//line follower mode
  if (switch2 == LOW)
  {
    int left = digitalRead(leftPin);
    int middle = digitalRead(middlePin);
    int right = digitalRead(rightPin);
    Serial.print(left);
    Serial.print("\t");
    Serial.print(middle);
    Serial.print("\t");
    Serial.println(right);
    if (left == LOW & middle == LOW & right == LOW)
    {
      stopCar(0);
    }
    else if (left == LOW & middle == HIGH & right == HIGH)
    {
      rightCar(200);
    }
    else if (left == HIGH & middle == LOW & right == HIGH)
    {
      forwardCar(60);
    }
    else if (left == HIGH & middle == HIGH & right == LOW)
    {
      leftCar(200);
    }
    else
    {
      forwardCar(60);
    }
  }
  else
  {
    stopCar(0);
  }
}
void forwardCar(int go)
{
  analogWrite(enA, go); //speed of motor A
  analogWrite(enB, go); //speed of motor B
  digitalWrite(in1, LOW); //backward control of motor A
  digitalWrite(in2, HIGH); //forward control of motor A
  digitalWrite(in3, LOW); //backward control of motor B
  digitalWrite(in4, HIGH); //forward control of motor B
}
void backwardCar(int go)
{
  analogWrite(enA, go); //speed of motor A
  analogWrite(enB, go); //speed of motor B
  digitalWrite(in1, HIGH); //backward control of motor A
  digitalWrite(in2, LOW); //forward control of motor A
  digitalWrite(in3, HIGH); //backward control of motor B
  digitalWrite(in4, LOW);  //forward control of motor B
}
void rightCar(int go)
{
  analogWrite(enA, go); //speed of motor A
  analogWrite(enB, go); //speed of motor B
  digitalWrite(in1, LOW); //backward control of motor A
  digitalWrite(in2, HIGH); //forward control of motor A
  digitalWrite(in3, LOW); //backward control of motor B
  digitalWrite(in4, LOW); //forward control of motor B
}
void leftCar(int go)
{
  analogWrite(enA, go); //speed of motor A
  analogWrite(enB, go); //speed of motor B
  digitalWrite(in1, LOW); //backward control of motor A
  digitalWrite(in2, LOW); //forward control of motor A
  digitalWrite(in3, LOW); //backward control of motor B
  digitalWrite(in4, HIGH); //forward control of motor B
}
void stopCar(int go)
{
  analogWrite(enA, go); //speed of motor A
  analogWrite(enB, go); //speed of motor B
  digitalWrite(in1, LOW); //backward control of motor A
  digitalWrite(in2, LOW); //forward control of motor A
  digitalWrite(in3, LOW);  //backward control of motor B
  digitalWrite(in4, LOW);  //forward control of motor B
}
void backLeft(int go)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, go);
  analogWrite(enB, go);
}
void backRight(int go)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  analogWrite(enA, go);
  analogWrite(enB, go);
}

/*Ultrasonic distance measurement Sub function*/
int Left_Distance_test()
{
  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig1, LOW);
  float Fdistance = pulseIn(Echo1, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}
int Middle_Distance_test()
{
  digitalWrite(Trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig2, LOW);
  float Fdistance = pulseIn(Echo2, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}
int Right_Distance_test()
{
  digitalWrite(Trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig3, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig3, LOW);
  float Fdistance = pulseIn(Echo3, HIGH);
  delay(10);
  Fdistance = Fdistance / 29 / 2;
  return (int)Fdistance;
}

