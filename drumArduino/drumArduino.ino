//Libraries
#include <SD.h>
#include <TMRpcm.h> // to play file

//Constants
#define SD_ChipSelectPin 10//4 
const int speakerPin = 9;
int snareSensor = A0; // indicates where the pin is connected
int snareRingSensor = A1;

// Sensor values
int snareValue = 0;
int snareRingValue = 0;

// Threshold Reference Values
int ref1 = 10;
int ref2 = 100;
int ref3 = 200;
int ref4 = 400;
int ref5 = 600;
int ref6 = 800;

// Test values for when hits won't surpass 500
/*
int ref1 = 10;
int ref2 = 80;
int ref3 = 160;
int ref4 = 240;
int ref5 = 320;
int ref6 = 400;
*/

// Test values for when hits won't surpass 250
/*
int ref1 = 10;
int ref2 = 50;
int ref3 = 85;
int ref4 = 120;
int ref5 = 155;
int ref6 = 190;
*/

// Soundfile names, the lower the number, the lighter the sound
char* snareSound1 = "snare1.wav"; 
char* snareSound2 = "snare2.wav";
char* snareSound3 = "snare3.wav";
char* snareSound4 = "snare4.wav";
char* snareSound5 = "snare5.wav";
char* snareSound6 = "snare6.wav";
char* snareSound7 = "snare7.wav";

char* snareRingSound1 = "Aro1.wav"; 
char* snareRingSound2 = "Aro2.wav";
char* snareRingSound3 = "Aro3.wav";
char* snareRingSound4 = "Aro4.wav";
char* snareRingSound5 = "Aro5.wav";
char* snareRingSound6 = "Aro6.wav";

//Objects
TMRpcm tmrpcm;

void setup() {
	Serial.begin(9600);
	pinMode(snareSensor, INPUT);
  pinMode(snareRingSensor, INPUT);
	
	//Initialize SD Shield
	if (!SD.begin(SD_ChipSelectPin)) {
		Serial.println("SD fail");
		return;
	}
	
	//Initialize Speaker
	tmrpcm.speakerPin = speakerPin;
	tmrpcm.setVolume(3);
}

void loop() {
	
  // Saves value read from each sensor
  snareValue = analogRead(snareSensor); 
  snareRingValue = analogRead(snareRingSensor);

	/* 
  The piezo sensor reads values from 0 to 1023, 
  starting at 10 so sounds aren't played without a hit.
  */
	if(snareValue > ref1 && snareValue <= ref2) { // pp
		tmrpcm.play(snareSound1); 
    Serial.println(snareValue);
	} else if (snareValue > ref2 && snareValue <= ref3){ // p
		tmrpcm.play(snareSound2); 
    Serial.println(snareValue);
	} else if (snareValue > ref3 && snareValue <= ref4){ // mp
		tmrpcm.play(snareSound3); 
    Serial.println(snareValue);
	} else if (snareValue > ref4 && snareValue <= ref5){ // mf
		tmrpcm.play(snareSound4); 
    Serial.println(snareValue);
	} else if (snareValue > ref5 && snareValue <= ref6){ // f
		tmrpcm.play(snareSound5); 
    Serial.println(snareValue);
	} else if (snareValue > ref6){ //ff
		tmrpcm.play(snareSound6); 
    Serial.println(snareValue);
	} else if (snareValue > ref6 && snareRingValue > ref3){ // sfx
		tmrpcm.play(snareSound7); 	
    Serial.println(snareValue);
  } 
  
  // Sounds for when the rim alone is hit
  if (snareRingValue > ref1 && snareRingValue <= ref2){
		tmrpcm.play(snareRingSound1); 
    Serial.println(snareRingValue);
	} else if (snareRingValue > ref2 && snareRingValue <= ref3){
		tmrpcm.play(snareRingSound2); 
    Serial.println(snareRingValue);
	} else if (snareRingValue > ref3 && snareRingValue <= ref4){
		tmrpcm.play(snareRingSound3); 
    Serial.println(snareRingValue);
	} else if (snareRingValue > ref4 && snareRingValue <= ref5){
		tmrpcm.play(snareRingSound4); 
    Serial.println(snareRingValue);
	} else if (snareRingValue > ref5 && snareRingValue <= ref6){
		tmrpcm.play(snareRingSound5); 
    Serial.println(snareRingValue);
	} else if (snareRingValue > ref6){
		tmrpcm.play(snareRingSound6); 
    Serial.println(snareRingValue);
	}
	
}