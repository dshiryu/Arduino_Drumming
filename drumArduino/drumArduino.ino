//Libraries
#include <SD.h>
#include <TMRpcm.h> // to play file

//Constants
#define SD_ChipSelectPin 10//4 
const int speakerPin = 9;
int snareSensor = A0; // indicates where the pin is connected
char* snareSound1 = "snare1.wav"; // file names
char* snareSound2 = "snare2.wav";
char* snareSound3 = "snare3.wav";
char* snareSound4 = "snare4.wav";
char* snareSound5 = "snare5.wav";

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

	/* 
  The piezo sensor reads values from 0 to 127, 
  starting at 10 so sounds aren't played without a hit.
  */
	if(snareValue > 10 && snareValue <= 33) {
		tmrpcm.play(snareSound1); // pp
	} else if (snareValue > 33 && snareValue <= 56){
		tmrpcm.play(snareSound2); // p
	} else if (snareValue > 56 && snareValue <= 79){
		tmrpcm.play(snareSound3);
	} else if (snareValue > 79 && snareValue <= 102){
		tmrpcm.play(snareSound4); // f
	} else if (snareValue > 102 && snareValue <= 127){
		tmrpcm.play(snareSound5); // ff
	}
	
}