#include <IRremote.h>

int RECV_PIN = 18; // define input pin on Arduino 
int LED_PIN = 19;

IRrecv irrecv(RECV_PIN); 
IRsend irsend(LED_PIN);
decode_results results; // decode_results class is defined in IRremote.h

//power (single press only)
unsigned int power[33] = {2200,850, 750,1600, 750,850, 700,850, 750,1600, 700,850, 750,800, 750,800, 750,850, 750,850, 700,900, 700,850, 700,850, 750,800, 750,1600, 700,850, 700};

//rotation (single press only)
unsigned int rotation[33] = {2200,900, 700,1650, 700,850, 700,850, 750,1600, 700,850, 700,850, 700,850, 700,1700, 700,850, 700,1650, 700,850, 750,1600, 700,850, 700,850, 750,800, 750};  // UNKNOWN 8A2D42AB 

// volUp
unsigned int volUp[33] = {2200,900, 700,1600, 750,850, 700,850, 750,1600, 700,850, 700,850, 750,800, 750,850, 750,1600, 750,850, 700,1600, 750,800, 750,1600,  750,800, 750,1550, 750};  // UNKNOWN 4B4E40B2

// volDown
unsigned int volDown[33] = {2200,850, 750,1600, 700,850, 750,850, 700,1650, 700,850, 700,850, 700,850, 700,1650, 750,1600, 750,1600, 700,1600, 750,1600, 750,1600, 700,1600, 750,800, 750};  // UNKNOWN 1015645B

//volDown2
unsigned int rawData[33] = {2200,850, 700,1650, 700,850, 750,850, 700,1600, 750,800, 750,800, 750,800, 750,1650, 700,1650, 700,1600, 750,1600, 750,1600, 700,1600, 750,800, 750,800, 750};  // UNKNOWN 1C33A44F

//volDown longpress
unsigned int volDownlongpress[5] = {2200,800, 700,1550, 750};  // UNKNOWN 4CB0FADC

void sendCommand(unsigned int *command){
  for (int i = 0; i < 3; i++) {
    irsend.sendRaw(command, 33, 38);
    delay(40);
  }
}

void setup() { 
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver 
}

void loop() { 

  //power up
  sendCommand(power);

  //vol down to one
  for(int j = 0; j < 9; j++){
    sendCommand(volDown);
    delay(200);
  }

  //vol to 5
  for(int j = 0; j < 4; j++){
    sendCommand(volUp);
    delay(200);
  }

  sendCommand(rotation);
  
  delay(10000);

  sendCommand(power);
  
  delay(5000);

}
