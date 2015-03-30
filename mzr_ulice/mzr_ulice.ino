const int distanceLimit = 1000;
//int state = 0; // positions 0 - 4
int stepUp = 15;
int stepDown = 5;

// analog inputs
int aPins[] = {
  A1,A2,A3,A4,A5
};

// values readed from analog inputs
int aVals[] = {
  1024,1024,1024,1024,1024
};

// pwm enabled pins
int pwmPins[] = {
  3, 4, 5, 9, 10
};

// pwm values for LEDs
int pwmVals[] = {
  255,255,255,255,255
};


void setup() {
  Serial.begin(9600);
  Serial.println("hello, this is the street diorama arduino");
  Serial.println("---");
  delay(1000);
  Serial.println("setting pwm outputs");
  Serial.println("---");
  
  for(int i = 0; i < 5; i++){
    pinMode(pwmPins[i],OUTPUT);
    analogWrite(pwmPins[i],pwmVals[i]);    
    delay(100);
    Serial.print("pin ");
    Serial.print(i);
    Serial.println("ok");
    delay(100);
  } 
}

void loop() {
  readAnalogInputs();  
  pwmFlowControll();    
  writePwms();
  delay(100);
  for(int i = 0; i < 5; i++){
    Serial.print(pwmVals[i]);
    Serial.print("  -  ");
  }
  Serial.println("|");
  
  
}

void readAnalogInputs(){
  for(int i = 0; i < 5; i++){
    aVals[i] = analogRead(aPins[i]);
    delay(2);
  }
}


void pwmFlowControll(){
  // mapping of logic to continuous pwm values
  // search for on gates
  for(int i = 0; i < 5; i++){
    
    // grab values
    int aVal = aVals[i];
    int pwmVal = pwmVals[i];
    
    // rise or fall of pwm according to logic
    // !!! reverse logic, 0 means full light
    if(aVal<distanceLimit){
      pwmVals[i] = constrain(pwmVal-stepUp,0,255);
    } else {
      pwmVals[i] = constrain(pwmVal+stepDown,0,255);
    }
  }
  delay(10);
}


void writePwms(){
  for(int i = 0; i < 5; i++){
    analogWrite(pwmPins[i],pwmVals[i]);
    delay(2);
  }
}
