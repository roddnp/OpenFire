// HPIK Engine Gen3 Arduino code
// Jan Hamalainen

#include <esp32-hal-gpio.h>
#include <HardwareSerial.h>

int Trigger = 18;     // Trigger input
int FullAuto = 19;  //Full Auto Input
int Solenoid =  23;      // Solenoid output

int fullAutoState = 0;  // Read full auto state
int triggerState = 0;         // Read trigger state


int solenoidDelay = 10; // Solenoid Delay Amount
int fullAutoRps = 100; // RPS delay amount between full auto shots
int semiRps = 100;  // RPS delay amounts between semi auto shots


bool OnceAlreadyShot = false; //determines if trigger has been depressed in semi auto

void setup() {
  Serial.begin(115200);
  delay(1000); //Take some time to open up the Serial Monitor
  pinMode(Solenoid, OUTPUT); // Define solenoid output
  pinMode(Trigger, INPUT);  // Define pushbutton input trigger
  pinMode(FullAuto, INPUT);    // Define Full auto input button
 
}

void loop() {
  
  triggerState = digitalRead(Trigger); // Reading trigger 
  
  if (triggerState == HIGH) {        // If pressed, state is HIGH
    Serial.println("state is high");
    fullAutoState = digitalRead(FullAuto);       // Full auto state. Activate Full auto
  
  
    if (fullAutoState == HIGH) {                // If pressed
      digitalWrite(Solenoid, HIGH);  // Solenoid open
      delay (solenoidDelay);
      digitalWrite(Solenoid, LOW);  // Solenoid closed
      delay (fullAutoRps);                     //debounce delay always to the end!
    }                                 // In other case, single fire
    else if (!OnceAlreadyShot) {      //shoot once, if not already shot
      digitalWrite(Solenoid, HIGH);  // solenoid open
      delay (solenoidDelay);
      digitalWrite(Solenoid, LOW);   // solenoid closed
      delay (semiRps);
      OnceAlreadyShot = true;         //Shot once
    }
  }
  else
  {
    Serial.println("state is not high");
    OnceAlreadyShot = false;          //restore to the beginning
  }
}