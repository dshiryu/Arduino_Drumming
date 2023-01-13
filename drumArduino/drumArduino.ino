//Libraries
#include <SD.h>
#include <TMRpcm.h>             // to play files
#include <Adafruit_NeoPixel.h>  // for LEDs
#include <SPI.h>                // SPI protocoll
#include <Servo.h>


// LED
#define PIN 2
#define NUM_PIXELS 60

// SD
#define SD_ChipSelectPin 4

int speakerPin = 9;
int snareSensor = A0;
int snareRingSensor = A1;


//int buttonPin = 3;
// variables will change:
//int buttonState = 0;


// Sensor values
int snareValue = 0;
int snareRingValue = 0;

// Threshold Reference Values
int ref1 = 80;
int ref2 = 120;
int ref3 = 160;
int ref4 = 190;
int ref5 = 200;
int ref6 = 600;

// Soundfile names, the lower the number, the lighter the sound
// bit resolution = 8bit; Audio frequency = 16.000 Hz; Audio Channel = Mono; PCM format = U8
char* snareSound1 = "sno.wav";   // Snare 1
char* snareSound2 = "snt.wav";   // Snare 2
char* snareSound3 = "snth.wav";  // Snare 3
char* snareSound4 = "snf.wav";   // Snare 4
char* snareSound5 = "snfi.wav";  // Snare 5
char* snareSound6 = "sns.wav";   // Snare 6
char* snareSound7 = "snse.wav";  // Snare 7

char* snareRingSound1 = "aroo.wav";  // Aro 1
char* snareRingSound2 = "art.wav";   // Aro 2
char* snareRingSound3 = "arth.wav";  // Aro 3
char* snareRingSound4 = "arf.wav";   // Aro 4
char* snareRingSound5 = "arfi.wav";  // Aro 5
char* snareRingSound6 = "ars.wav";   // Aro 6

//Test Sound
//char* testSound = "tes.wav";

//Objects
TMRpcm tmrpcm;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// twelve servo objects can be created on most boards
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

/*	
	note durations: 4 = quarter note, 8 = eighth note, etc.:
	possible values: 0, 1, 2, 4, 8, 16, 32 (zero: silence/pause)
	indicates how many beats per bar on the sheet music
	considers 4 by 4 intervals, i.e. 4 times the quarter note
*/
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};



/*
	Note strength determines the height (position) of the arm,
	the higher it goes, the louder the sound gets.
	p = 17 // piano, weak
	m = 41 // mezzo, normal hit
	f = 65 // forte, hard
*/
//char noteStrenghts[sizeof(noteDurations)] = "mmmmmmmm";
char noteStrenghts[sizeof(noteDurations)] = "ffffffff";

// Beats Per Minute, 60 = one every second
int bpm = 120;
double bpmDelay = 60 / bpm;
int timeSignature = 4;



void setup() {

  tmrpcm.speakerPin = speakerPin;

  Serial.begin(9600);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
    return;
  }

  tmrpcm.setVolume(5);
  tmrpcm.quality(1); // 0 = normal, 1 = 2x oversampling

  pinMode(snareSensor, INPUT);
  pinMode(snareRingSensor, INPUT);
  //pinMode(buttonPin, INPUT);

  // Initialize LED Bib
  pixels.begin();

  /* CODE ON SETUP() SO IT ONLY PLAYS ONCE AND DON'T REPEAT*/
  // iterate over the notes of the melody:
  myservo.write(5);  // Set initial position
  myservo.attach(6);  // attaches the servo on pin 6 to the servo object



  //Test Sound
  //tmrpcm.setVolume(5);
  //tmrpcm.play("tes.wav");
  //Serial.println("test");
}

void loop() {

  //buttonState = digitalRead(buttonPin);

  //  Serial.println(buttonState);
  // if (buttonState == HIGH) {
   startServo();
  //  Serial.println(buttonState);
  // }

  // Saves value read from each sensor
  snareValue = analogRead(snareSensor);
  snareRingValue = analogRead(snareRingSensor);


  /*The piezo sensor reads values from 0 to 1023, 
  starting at 10 so sounds aren't played without a hit.
  */
  if (snareValue > ref1 && snareValue <= ref2) {  // pp

    playSnareSound(snareSound5, 10);
    blinkLed(0, 0, 255);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareValue);

  } else if (snareValue > ref2 && snareValue <= ref3) {  // p

    playSnareSound(snareSound6, 10);
    blinkLed(0, 255, 0);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareValue);

  } else if (snareValue > ref3 && snareValue <= ref4) {  // mp

    playSnareSound(snareSound7, 10);
    blinkLed(255, 0, 0);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareValue);
  }
  // else if (snareValue > ref4 && snareValue <= ref5){ // mf

  //     playSnareSound(snareSound4, 0);
  //     blinkLed(100, 150, 100);
  //     Serial.println(snareValue);

  // } else if (snareValue > ref5 && snareValue <= ref6){ // f

  //     playSnareSound(snareSound5, 0);
  //     blinkLed(100, 0, 150);
  //     Serial.println(snareValue);

  // } else if (snareValue > ref6){ //ff

  //     playSnareSound(snareSound6, 0);
  //     blinkLed(0, 100, 100);
  //     Serial.println(snareValue);

  //    } //else if (snareValue > ref6 && snareRingValue > ref3){ // sfx

  //     playSnareSound(snareSound7, 1000);
  //     blinkLed(0, 0, 100);
  //     Serial.println(snareValue);
  //  }



  // Sounds for when the rim alone is hit
  if (snareRingValue > ref1 && snareRingValue <= ref2) {

    playSnareRingSound(snareRingSound4, 10);
    blinkLed(255, 255, 255);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareRingValue);

  } else if (snareRingValue > ref2 && snareRingValue <= ref3) {

    playSnareRingSound(snareRingSound5, 10);
    blinkLed(255, 255, 255);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareRingValue);

  } else if (snareRingValue > ref3 && snareRingValue <= ref4) {

    playSnareRingSound(snareRingSound6, 10);
    blinkLed(255, 255, 255);
    delay(150);
    blinkLed(0, 0, 0);
    Serial.println(snareRingValue);

  }  //else if (snareRingValue > ref4 && snareRingValue <= ref5){

  // 		playSnareRingSound(snareRingSound4, 1000);
  //     blinkLed(255, 255, 255);
  //     Serial.println(snareRingValue);

  // 	} else if (snareRingValue > ref5 && snareRingValue <= ref6){

  // 		playSnareRingSound(snareRingSound5, 1000);
  //     blinkLed(255, 255, 255);
  //     Serial.println(snareRingValue);

  // 	} else if (snareRingValue > ref6){

  // 		playSnareRingSound(snareRingSound6, 1000);
  //     blinkLed(255, 255, 255);
  //     Serial.println(snareRingValue);
  // 	  }
}



// Functions
void playSnareSound(char* snareSound, int delayNumber) {
  tmrpcm.play(snareSound);
  delay(delayNumber);
}

void playSnareRingSound(char* snareRingSound, int delayNumber) {
  tmrpcm.play(snareRingSound);
  delay(delayNumber);
}

void blinkLed(int red, int green, int blue) {
  pixels.fill(pixels.Color(red, green, blue), 0, NUM_PIXELS);
  pixels.show();
}

void startServo() {
  for (int thisNote = 0; thisNote < sizeof(noteDurations); thisNote++) {

    switch (noteStrenghts[thisNote]) {
      case 'p':
        pos = 17;
        break;
      case 'm':
        pos = 41;
        break;
      case 'f':
        pos = 65;
        break;
    }
    // Hit the drumhead
    myservo.write(pos);  // go back to waiting position
    myservo.write(0);    // tell servo to go to position 0 (a hit)
    myservo.write(pos);  // gets back to previous position


    /* Multiply by 1000 because delay() uses miliseconds. 
	Using 1 second and 60 bpm as reference
	A 4 by 4 time signature means 4 beats of value 4 every bar. 
	To get a 1 and have a beat on the right time, we divide 4 by 4.
	Dividing 4 by 8 gets 0.2, i.e. 2 beats per note (which is intended).
	*/
    delay(bpmDelay * 1000 * (timeSignature / thisNote));

    //delay(1000);
  }
}