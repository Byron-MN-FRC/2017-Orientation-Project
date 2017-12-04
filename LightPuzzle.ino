// Define the pins that the 3 blue leds are associated with
const int led1Pin = 2;
const int led2Pin = 3;
const int led3Pin = 4;

// Define the pin that the game start/reset button is associate on
const int btnPin = 8;

// Define the pins that the red and green LED's for game status
const int redLedPin=13;
const int greenLedPin=12;

// Length of game in milliseconds (10 seconds)
const unsigned long duration=10000;

// This variable holds a value in milliseconds representing when the 
// start game button was pressed.
unsigned long startTime=0;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // We monitor the  blue leds for power
  pinMode(led1Pin, INPUT);
  pinMode(led2Pin, INPUT);
  pinMode(led3Pin, INPUT);
  
  // Monitor the button pin to determin if it is pressed.
  pinMode(btnPin, INPUT);
  
  // Send power to red or green leds to report game status to the user.
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  printValues();

  // Determine if the button has been pressed by reading the pin (1 equals pressed)
  if (digitalRead(btnPin)==1)
  {
	  // The button has been pressed, set the start time and turn on the red light and turn off the green.
    Serial.println("Button is pressed.");
    startTime = millis();           // Assign the current time in milliseconds to StartTime
    digitalWrite(redLedPin, HIGH);  // HIGH means turn on
    digitalWrite(greenLedPin, LOW); // LOW means turn off
  }

  // if the start time is not equal to 0, then the game is being played.  (see above, startTime = millis();
  if (startTime != 0)
  {
    testGameState(); // this routine determines if the user has solved the game or not.

    // Calculate how long the game has been going.  If it is more than 10000 ms, turn off the red light and reset start time to 0.
    if ((millis() - startTime) > duration)
    {
      digitalWrite(redLedPin,LOW);
      startTime = 0;  // this makes the game play stop until the button is pressed again, making startTime > 0
    }
  }
}

void testGameState()
{
	// Read and store the values of the 3 blue leds.
  bool led1 = digitalRead(led1Pin) == HIGH;
  bool led2 = digitalRead(led2Pin) == HIGH;
  bool led3 = digitalRead(led3Pin) == HIGH;

  // if all the leds are HIGH (turned on) then we have solved the game.  turn the red light off, turn the green light on, set startTime to 0;
  if (led1 && led2 && led3)
  {
      digitalWrite(redLedPin,LOW);
      digitalWrite(greenLedPin,HIGH);
      startTime = 0;
  }
}

// This is for debugging
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


