#include <Servo.h>

int front_left = 2;
int back_left = 3;

int front_right = 9;
int back_right = 8;

int Speed = 6;

bool frntDetected = false;

//sonar sensor
int trig = 4;
int ech = 5;

int trigS = 12;
int echS = 10;

float duration;
float distance;
float sDistance;

unsigned long previousTime = 0;

Servo neck;

void setup(){

  pinMode(front_right, OUTPUT);
  pinMode(front_left, OUTPUT);

  pinMode(back_right, OUTPUT);
  pinMode(back_left, OUTPUT);

  pinMode(Speed, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  SetSpeed(Speed, 0.5);

  pinMode(trig, OUTPUT);
  pinMode(ech, INPUT);

  pinMode(trigS, OUTPUT);
  pinMode(echS, INPUT);

  neck.attach(11);
  neck.write(90);

  delay(2000);

  Serial.begin(9600);  

}

void loop(){  
  
   distance = Distance();

   Serial.println(distance);
   
     if (distance <= 16) {
        m_back();
        delay(80);
  
        SetSpeed(Speed, 0.65);
        Look();  
        SetSpeed(Speed, 0.5);
  
        previousTime = millis();

  
          
    } else {
  
      m_front();
    }

  sDistance = DistanceS();

  if ((sDistance <= 6 || (sDistance >= 55 && sDistance <= 75)) && (millis() - previousTime >= 1500) && (Distance() >= 25)){// && !frntDetected) {
    m_back();
    delay(100);
    
    m_stop();
    LookS(sDistance);
    
    

    previousTime == millis();

  }

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
  for (int i = 0; i<3; i++) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
  
    duration = pulseIn(ech, HIGH);
    // Calculating the distance in cm
    if ((duration*0.034/2) > 500) { _d += 0; } else {
      _d += duration*0.034/2;
    }
  }

  return (_d/3);
}


float DistanceS(){
  
  float _d = 0;
  // Sets the trigPin on HIGH state for 10 micro seconds and find avg
  
  for (int i = 0; i<2; i++) {
    digitalWrite(trigS, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trigS, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigS, LOW);
  
    duration = pulseIn(echS, HIGH);
    // Calculating the distance in cm
    if ((duration*0.034/2) > 500) { _d += 0; } else {
      _d += duration*0.034/2;
    }
    

  }

  return (_d/2);
}




void Look(){

  delay(100);
  m_stop();
  delay(100);
  
  float dirs[5];

  int lookDirs[] = {0, 45, 135, 180, 90};

  
  for (int i = 0; i < 5; i++){
    neck.write(lookDirs[i]);
    
    delay(1250);

    dirs[i] = Distance();
    
  }

  int dir = GetMax(dirs);

  //Serial.println(dir);
  
  if (dir < 5) {
    int angle = lookDirs[dir];

    //Serial.println(angle);
    
    if (angle > 90){


      m_left();

      delay(280 * ( dir - 1 ));
      
      m_stop();
      delay(200);
      
    } else if (angle < 90) {

      m_right();

      delay(280 * ( dir + 1 ) );
      
      m_stop();
      delay(200);
    } 

    
  }

  
}


void LookS( float dist ){

  delay(100);
  m_stop();
  delay(100);
  
  int dir;

  if (dist <= 10) {
    dir = 1;
  } else if ( dist >= 48 ) {
    dir = 0;
  }

  //Serial.println(dir);

    
  if (dir == 1){


    m_right();

    delay(280);
    
    m_stop();
    delay(200);
    
  } else if (dir == 0) {

    m_left();

    delay(280 );
    
    m_stop();
    delay(200);
  } 

  if ( Distance() <= 15 ) {
    Look();
  }

  m_front();

  delay(500);

  
}




void SetSpeed(int p, float speed) {
  analogWrite(p, round(speed*255));
}


int GetMax(float d[]) {


   int maxVal = d[0];
   int maxInd = 0;
   
   for (int i = 0; i < 5; i++) {
      if (d[i] > maxVal) {
        maxInd = i;
        maxVal = d[i];
      }

   }

   return maxInd;

}
