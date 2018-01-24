// Midi Receiver
// 


// The only available pin for PWM are: 3,5,6,9,10,11
#define pin_RED 11
#define pin_GREEN 5
#define pin_BLUE 6
#define pin_LED 13


int incomingByte =-1;
int mainCommand=0;
int firstByte=-1;
void setup()
{
  Serial1.begin(31250);
  Serial.begin(9600);
  pinMode(pin_BLUE,OUTPUT); //BLUE
  pinMode(pin_GREEN,OUTPUT); //GREEN
  pinMode(pin_RED,OUTPUT); //RED
  pinMode(pin_LED,OUTPUT); //RED
  digitalWrite(pin_LED, LOW);
  
  // Baud rate set to 31250 Baud https://en.wikipedia.org/wiki/MIDI_1.0#Hardware_transport_(electrical_and_mechanical_connections)
}

void loop()
{    
  //Serial.print("N");

  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
    //Serial.println(incomingByte, HEX);
    if (incomingByte&0x80){
      mainCommand=1;
    }
    if (incomingByte == 0xFE){
      //Drop, only Sync
      mainCommand=-1;
    }
    //Serial.print("mainCommandIN:");
    //Serial.println(mainCommand, HEX);
    if (mainCommand > 0){
      Serial.println(incomingByte, HEX);
      if (mainCommand==1){
        if (incomingByte == 0x90){
          //Note ON,
          mainCommand=0x90;
          //digitalWrite(pin_LED, HIGH);
        }
      }
      if (mainCommand==0x90){
        if (firstByte < 0 ){
          if (incomingByte == 0x26){
            //Serial.println("incomingByte=0x26");
            //Note 0x26 ON,
            digitalWrite(pin_LED, HIGH);
            firstByte=0x26;
          }
          if (incomingByte == 0x27){
            //Serial.println("incomingByte=0x27");
            //Note 0x27 ON
            digitalWrite(pin_LED, LOW);
            firstByte=0x27;
          }
          else{
            if (firstByte == 0x26 ){
              if (incomingByte | 1){ // Any Velocity
                digitalWrite(pin_LED, HIGH);
                
              }
            if (firstByte == 0x27 ){
              if (incomingByte | 1){ // Any Velocity
                digitalWrite(pin_LED, LOW);
              }

            }
          }
        }
      }
    }
    //Serial.print("mainCommandOUT:");
    //Serial.println(mainCommand, HEX);

  }
     
  //digitalWrite(pin_LED, HIGH);
  //Serial.print("Code: ");
  //Serial.println(incomingByte, HEX);
    
  
  //analogWrite(pin_RED,0);
  //analogWrite(pin_GREEN,0);
  //analogWrite(pin_BLUE,0);
}
