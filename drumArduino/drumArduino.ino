//Libraries
#include <SD.h>
#include <TMRpcm.h> // to play file

//Constants
#define SD_ChipSelectPin 10//4 
const int speakerPin = 9;
int snareSensor = A0; // indicates where the pin is connected
int snareRingSensor = A1;

// soundfile names, the lower the number, the lighter the sound
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
	
	//Init sd shield
	if (!SD.begin(SD_ChipSelectPin)) {
		Serial.println("SD fail");
		return;
	}
	
	//Init speaker
	tmrpcm.speakerPin = speakerPin;
	tmrpcm.setVolume(3);
}

void loop() {
	int snareValue = analorRead(snareSensor); // saves value read on the sensor
  int snareRingValue = analorRead(snareRingSensor);

	/* 
  The piezo sensor reads values from 0 to 127, 
  starting at 10 so sounds aren't played without a hit.
  */
	if(snareValue > 10 && snareValue <= 27) {
		tmrpcm.play(snareSound1); // pp
	} else if (snareValue > 27 && snareValue <= 44){
		tmrpcm.play(snareSound2); // p
	} else if (snareValue > 44 && snareValue <= 61){
		tmrpcm.play(snareSound3); // normal1
	} else if (snareValue > 61 && snareValue <= 78){
		tmrpcm.play(snareSound4); // normal2
	} else if (snareValue > 78 && snareValue <= 95){
		tmrpcm.play(snareSound5); // f
	} else if (snareValue > 95 && snareValue <= 112){
		tmrpcm.play(snareSound6); //ff
	} else if (snareValue > 112 && snareValue <= 127 && snareRingValue > 60){
		tmrpcm.play(snareSound7); // sfx
	} 
  
  // sounds for when the ring alone is hit
  if (snareRingValue > 10 && snareRingValue <= 30){
		tmrpcm.play(snareRingSound1); 
	} else if (snareRingValue > 30 && snareRingValue <= 50){
		tmrpcm.play(snareRingSound2); 
	} else if (snareRingValue > 50 && snareRingValue <= 70){
		tmrpcm.play(snareRingSound3); 
	} else if (snareRingValue > 70 && snareRingValue <= 90){
		tmrpcm.play(snareRingSound4); 
	} else if (snareRingValue > 90 && snareRingValue <= 110){
		tmrpcm.play(snareRingSound5); 
	} else if (snareRingValue > 110 && snareRingValue <= 127){
		tmrpcm.play(snareRingSound6); 
	}
	
}