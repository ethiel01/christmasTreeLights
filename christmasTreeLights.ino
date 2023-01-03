int IN1=9;
int IN2=8;
int ENA=10;
int MIN=10;
int color = 0;
int state = 1;

void ChangeWhite() {
    // This is white mode
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
}

void ChangeColor() {
    // This is color mode
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
}

void ChangeState() {
  if(color==1) {
    ChangeWhite();
    color = 0;
  }
  else {
    ChangeColor();
    color = 1;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);  
  pinMode(ENA,OUTPUT);
  
  if(color) {
    ChangeColor();
  }
  else {
    ChangeWhite();
  }
  int i = 0;
  for(i = 0 ; i <= MIN; i+=1) {
    analogWrite(ENA, i);
    delay(5);
  }


}

void DelayAdjustment(int index) {
  float b = 40;
  float endValue = 20;
  float mLinear = (endValue - b) / 255;
  float mExp = (endValue - b) / pow(255,2);
  // float delayValue = endValue; // Fixed 
  // float delayValue = mLinear * index + b; // Linear
  float delayValue = mExp* pow(index, 2) + b; // Exponential
  delay(int(delayValue));
}

void Brighten() {
  int i = 0;
  for(i = MIN ; i <= 255; i+=1) { 
    analogWrite(ENA, i);
    DelayAdjustment(i);
  }
}

void Dim() {
  int i = 0;
  for(i = 255; i >=MIN; i-=1) {
    analogWrite(ENA, i);
    DelayAdjustment(i);
  }
  
}


void Blinking() {
  Brighten();
  delay(10000);
  Dim();
  delay(5000);
}

void SwitchBlinking() {
  Brighten();
  delay(10000);
  Dim();
  delay(5000);
  ChangeState();
  Brighten();
  delay(10000);
  Dim();
  delay(5000);
  ChangeState();
}


void Solid() {
  analogWrite(ENA, 255);
}

void loop() {
  if(state == 0) {
    Blinking();
  }
  else if(state==1) {
    SwitchBlinking();
  }
  else {
    Solid();
  }
}
