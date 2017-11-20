const int led1Pin = 2;
const int led2Pin = 3;
const int led3Pin = 4;

const int btnPin = 8;

const int redLedPin=13;
const int greenLedPin=12;

const unsigned long duration=10000;
unsigned long startTime=0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(led1Pin, INPUT);
  pinMode(led2Pin, INPUT);
  pinMode(led3Pin, INPUT);
  pinMode(btnPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  printValues();

  if (digitalRead(btnPin)==1)
  {
    Serial.println("Button is pressed.");
    startTime = millis();
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
  }

  if (startTime != 0)
  {
    testGameState();
    if ((millis() - startTime) > duration)
    {
      digitalWrite(redLedPin,LOW);
      startTime = 0;
    }
  }
}

void testGameState()
{
  bool led1 = digitalRead(led1Pin) == HIGH;
  bool led2 = digitalRead(led2Pin) == HIGH;
  bool led3 = digitalRead(led3Pin) == HIGH;

  if (led1 && led2 && led3)
  {
      digitalWrite(redLedPin,LOW);
      digitalWrite(greenLedPin,HIGH);
      startTime = 0;
  }
}
void printValues()
{
  int pinVal = digitalRead(led1Pin);
  if (pinVal==1)
  {
    Serial.println("LED 1 is on.");
  }
  pinVal = digitalRead(led2Pin);
  if (pinVal==1)
  {
    Serial.println("LED 2 is on.");
  }
  pinVal = digitalRead(led3Pin);
  if (pinVal==1)
  {
    Serial.println("LED 3 is on.");
  }
}


