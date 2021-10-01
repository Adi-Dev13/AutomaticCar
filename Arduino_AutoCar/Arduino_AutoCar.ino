#include <Servo.h>

int front_left = 2;
int back_left = 3;

int front_right = 9;
int back_right = 8;

int Speed = 6;

bool firstIter = true;

//sonar sensor
int trig = 4;
int em = 5;

float duration;

Servo neck;

void setup(){

  pinMode(front_right, OUTPUT);
  pinMode(front_left, OUTPUT);

  pinMode(back_right, OUTPUT);
  pinMode(back_left, OUTPUT);

  pinMode(Speed, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  SetSpeed(Speed, 0.45);

  pinMode(trig, OUTPUT);
  pinMode(em, INPUT);

  neck.attach(11);
  neck.write(90);

  delay(2000);

  Serial.begin(9600);  

}

void loop(){  
  float distance = Distance();
  Serial.println(distance);
 // m_right();
 if (distance >= 150) {
  m_back();
  delay(2000);
  m_stop();
 }
  if (distance <= 16) {
      m_back();
      delay(100);
      Look();  
        
  } else {

    m_front();
  }

  firstIter = false;
}

void m_front(){
  digitalWrite(front_left, HIGH);
  digitalWrite(front_right, HIGH);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
}

void m_right(){
  digitalWrite(front_left, HIGH);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, HIGH);  
}

void m_left(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, HIGH);

  digitalWrite(back_left, HIGH);
  digitalWrite(back_right, LOW);  
}

void m_back(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, HIGH);
  digitalWrite(back_right, HIGH);  
}

void m_stop(){
  digitalWrite(front_left, LOW);
  digitalWrite(front_right, LOW);

  digitalWrite(back_left, LOW);
  digitalWrite(back_right, LOW);  
  
}

float Distance(){
  
  float _d = 0;
  // Sets the trigPin on HIGH state for 10 micro seconds and find avg
  
  for (int i = 0; i<5; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
    duration = pulseIn(em, HIGH);
    // Calculating the distance in cm
    if ((duration*0.034/2) > 500) { _d += 0; } else {
      _d += duration*0.034/2;
    }
    

  }

  return (_d/5);
}

void Look(){

  delay(100);
  m_stop();
  delay(100);

  SetSpeed(Speed, 0.5);
  
  float dirs[3];

  int lookDirs[] = {0, 180, 90};
  
  for (int i = 0; i < 3; i++){
    neck.write(lookDirs[i]);
    
    delay(1500);

    dirs[i] = Distance();
    Serial.println(dirs[i]);
    
  }
  
  int dir = GetMax(dirs);

  if (dirs[dir] > 150) {
    m_back();
    delay(1000);
    m_stop();
    return;
  }
  
  if (dir < 3) {
    int angle = lookDirs[dir];
    Serial.println(angle);
    
    if (angle > 90){


      m_left();

      delay(576);
      
      m_stop();
      delay(200);
      
    } else if (angle < 90) {

      m_right();

      delay(576);
      
      m_stop();
      delay(200);
    } 

    
  }
  
}

void SetSpeed(int p, float speed) {
  analogWrite(p, round(speed*255));
}


int GetMax(float d[]) {
  bool isLargest = false;
  
  for (int i = 0; i < 3; i++) {
    isLargest = false;
    
    for (int j = 0; j < 3; j++) {
      if (d[i] > d[j]){
        isLargest = true;
      } else {
         if (i != j) {
          isLargest = false;
          break;
         }
      }
    }

    if (isLargest) {
      return i;
    }
    
  }
  
  if (!isLargest) {
    return 3;
  }
}
