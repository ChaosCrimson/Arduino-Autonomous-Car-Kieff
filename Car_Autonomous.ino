int EN1 = 9;
int EN2 = 10;
int M1 = 2;
int M2 = 3;
int M3 = 6;
int M4 = 5;
int S2T = 11;
int S2E = 12;
int S1E = 7;
int S1T = 8;
int BUTTON = 13;
boolean lastButton = LOW;
boolean currentButton = LOW;
double val = 0;
double val2 = 0;



void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  pinMode(S1E, INPUT);
  pinMode(S2E, INPUT);
  pinMode(S1T, OUTPUT);
  pinMode(S2T, OUTPUT);
  Serial.begin(9600);
}



void rightForward(int rate) {
  digitalWrite(EN1, LOW);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(EN1, rate);

}

void rightReverse(int rate) {
  digitalWrite(EN1, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(EN1, rate);

}


void leftForward(int rate) {
  digitalWrite(EN2, LOW);
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  analogWrite(EN2, rate);

}

void leftReverse(int rate) {
  digitalWrite(EN2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
  analogWrite(EN2, rate);
}

void brake() {
  digitalWrite(EN1, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(EN1, HIGH);

  digitalWrite(EN2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  digitalWrite(EN2, HIGH);
}

boolean debounce(boolean last) {
  boolean current = digitalRead(BUTTON);
  if (last != current) {
    delay(5);
    current = digitalRead(BUTTON);
  }
  return current;

}

void loop() {
  currentButton = debounce(lastButton);

  //if (lastButton == LOW && currentButton == HIGH) {
    digitalWrite(S1T, LOW);
    digitalWrite(S2T, LOW);
    delayMicroseconds(5);
    digitalWrite(S1T, HIGH);
    digitalWrite(S2T, HIGH);
    delayMicroseconds(10);
    digitalWrite(S1T, LOW);
    digitalWrite(S2T, LOW);


    val = pulseIn(S1E, HIGH) / 58.2;
    val2 = pulseIn(S2E, HIGH) / 58.2;
    Serial.println("FRONT");
    Serial.println(val);
    Serial.println("Side");
    Serial.println(val2);
    if (val < 76) {
      rightForward(0);
      leftForward(0);
    } else {
      rightForward(55.5);
      leftForward(50);
    }
    /*
    else if (val > 81) {
      rightForward(150);
      leftForward(150);
    } else if (val2 < 81) {
      rightForward(120);
      leftForward(150);
    } else {
      rightForward(150);
      leftForward(120);
    }
    */
  //}
}
