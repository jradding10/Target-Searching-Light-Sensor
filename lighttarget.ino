// Target Searching Light Sensor
//by Jacqueline Radding
//Finds the brightest source of light by scanning an area over 180 degrees using a servo motor and a photoreistor
#include <Servo.h> 
int beeper = 12; // this is the pin the beeper is located
int val; // this will store the analog value
int BrightnessPercent; // percent
int bigang = 0; // this will notify what angle pops up the brightest
int brightest; // brightest point  
int ang; // angle
const int LED = 2; // LED pin
const int ServoPin = 9; //Servo connection

int i =0;


void setup() {
   pinMode(LED, OUTPUT); // LED pin and output
   pinMode(3, INPUT_PULLUP); // button
   digitalWrite(LED, HIGH); // Turn on the led for scanning
  

  Servo myservo; // create servo object to control servo
  myservo.attach(ServoPin); // attach servo on pin 9 to servo object
 const int ServoPin = 9; //Servo connection
  digitalWrite(A0, INPUT); // sets A0 as input
  digitalWrite(beeper, OUTPUT); // beeper pin
  delay(10);
  
  Serial.begin(9600); // sets up serial monitor
  
  while (i < 180){ // i is each angle, when angles are under 180, do this 
  val = analogRead(A0);
  BrightnessPercent = val / 1023.0 * 100; //calculate to find percentage
  ang = i; // to seperate angle and i values
  myservo.write(i);              //set servo position to full CW (0 degrees)
  delay(10); // delay
  takebright();               // takes the brightness value at this angle//determines which angle is brightest
  i = i+1; // i increases by one so the device can move to the next angle
  }
  delay(2000);
  myservo.write(bigang);              //set servo position to big angle
  delay(2000);
  myservo.write(0); // returns to 0 or full cw position
  delay(100); // delay
  
  int brightmap = map(brightest, 0, 100, 50, 1000); // this will be used for the tone. maps brighness to max/ min tone
  tone(beeper, brightmap, 1000); // plays tone according to brightest percent
  Serial.print("brightest %:"); // displays the brightest percent
  Serial.println(brightest); //prints brightest point
  Serial.println("angle:");
  Serial.println(bigang); // brightest angle

  delay(10); 
  
  

  
}

void loop() {
  int light = digitalRead(3); // button
  if (light == LOW){ // if button pressed
   digitalWrite(LED, HIGH); // Turn on the LED
   delay(100);
   if (light == LOW){ // turn off if not pressed
    digitalWrite(LED, LOW);
    }
  if(light == HIGH){ // turn off if not pressed
    digitalWrite(LED, LOW); // off
    }
  }




}


void takebright(){

  int brightmap = map(BrightnessPercent, 0, 100, 50, 1000); // this will be used for the tone. maps brighness to max/ min tone
  tone(beeper, brightmap, 100); // make a beep
  if (brightest < BrightnessPercent){ // find the biggest brightness percent if brighness is greater than last reading
    brightest = BrightnessPercent; // make brightest the new biggest value
    bigang = ang; // make the brightest angle the new stored angle
    }

  
  }
