/*******************************************
Programme pour selectionner une sortie d'ampli
selon un Message Midi sur le Cannal 9 
Message: Program Change 1 a 8*/


//Definition des pins utilise pour input des foot switch

#define PB1 13
#define PB2 12
#define PB3 11
#define PB4 10
#define PB5 9
#define PB6 8
#define PB7 7
#define PB8 6
#define PBMUTE 5


//Definition des pins utiliser pour les sorties relais
#define R1 3
#define R2 2
#define R3 A5
#define R4 A4
#define R5 A3
#define R6 A2
#define R7 A1
#define R8 A0
#define RMUTE 4
#define HEARTBEAT 5
#define HEARTBEATVALUE 1000


// Midi Receiver
// 


#define MIDI_CHANNEL 9 //1 to 16 - Midi Channel number
#define MSG_MIDI_ACT_SENSE 0xFE // Active Sense
#define MSG_MIDI_NOTE_ON 0x90
#define MSG_MIDI_NOTE_OFF 0x80
#define MSG_MIDI_POLY_KEY_PRS 0xA0 //Polyphonic Key pressure
#define MSG_MIDI_CTRL_CHG 0xB0 // Control Change
#define MSG_MIDI_PROG_CHG 0xC0 // Program Change
#define MSG_MIDI_CHANNEL_PRS 0xD0 // Channel Pressure
#define MSG_MIDI_PITCH_BEND 0xE0 // Pitch Bend

int incomingByte =-1;
int lastValidMessage=0;
int firstByte=-1;
int relaisMem[10];
int relaisOrder[] = {0, R1, R2, R3, R4, R5, R6, R7, R8, 0, 0 };
int pushButtonOrder[] = {0, PB1, PB2, PB3, PB4, PB5, PB6, PB7, PB8, 0, 0 };
int heartBeat=0;

void setup()
{
  //Serial1.begin(31250);
  Serial.begin(31250);
  
  // Baud rate set to 31250 Baud https://en.wikipedia.org/wiki/MIDI_1.0#Hardware_transport_(electrical_and_mechanical_connections)


  // Configuration des entree/sortie
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);
  pinMode(PB5, INPUT_PULLUP);
  pinMode(PB6, INPUT_PULLUP);
  pinMode(PB7, INPUT_PULLUP);
  pinMode(PB8, INPUT_PULLUP);
  pinMode(PBMUTE, INPUT_PULLUP);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(RMUTE, OUTPUT);
  pinMode(HEARTBEAT, OUTPUT);
  for (int i=0;i<10;i++){
    relaisMem[i]=0;
  }

}

void loop()
{ 
  if (heartBeat-- <= 0 )
    heartBeat = HEARTBEATVALUE;
  if (heartBeat < (HEARTBEATVALUE / 2)){
    digitalWrite(HEARTBEAT, 1);
  }else {
    digitalWrite(HEARTBEAT, 0);
  }
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
      /*if (incomingByte != MSG_MIDI_ACT_SENSE){ // Si ce n'est pas un ActiveSense on continue http://midi.teragonaudio.com/tech/midispec/sense.htm
        Serial.println(incomingByte, HEX);
      }*/
  }
  // Message MIDI car le bit 7 a ON
  if (incomingByte&0x80){
    firstByte=-1; //Donc ce n'est pas un DATA
    if (incomingByte != MSG_MIDI_ACT_SENSE){ // Si ce n'est pas un ActiveSense on continue http://midi.teragonaudio.com/tech/midispec/sense.htm
      // Est ce la Messagee 0xC0 PROGRAM CHANGE?
      // et le bon Channel Midi?
      if (!((incomingByte & 0xF0) ^ MSG_MIDI_PROG_CHG ) & !((incomingByte& 0x0F) ^ (MIDI_CHANNEL-1))){
        lastValidMessage= (incomingByte & 0xF0); //On Garde la partie du message de gauche et on detruit le channel Midi
      }
    }
    else{
      // Si c'est un timecode on srap et on repar a neuf
      // Ou tout autre Midi Message qu'attendu et que pas bon midi Channel
      lastValidMessage=-1;
    }
  }
  else{
    if (lastValidMessage > 0){ //j'ai deja recu une Messagee Midi
      if (lastValidMessage == MSG_MIDI_PROG_CHG){ //et PROGRAM CHANGE
        if (firstByte < 0 ){
          if (incomingByte == 0x00){
            relaisMemWriter(1);
          }
          if (incomingByte == 0x01){
            relaisMemWriter(2);
          }
          if (incomingByte == 0x02){
            relaisMemWriter(3);
          }
          if (incomingByte == 0x03){
            relaisMemWriter(4);
          }
          if (incomingByte == 0x04){
            relaisMemWriter(5);
          }
          if (incomingByte == 0x05){
            relaisMemWriter(6);
          }
          if (incomingByte == 0x06){
            relaisMemWriter(7);
          }
          if (incomingByte == 0x07){
            relaisMemWriter(8);
          }
        firstByte=-1; // Receive my 2 bytes
        }
        else{
          if (firstByte == 0x26 ){
            if (incomingByte | 1){ // Any Velocity
              //digitalWrite(R1, HIGH);
            }
          }  
          if (firstByte == 0x27 ){
            if (incomingByte | 1){ // Any Velocity
              //digitalWrite(R1, LOW);
            }
          }
        firstByte=-1; // Receive my 2 bytes
        }
      }
    }
  }
  //Read Push Button and send only one into mem
  readPushButtonToMem(); 
  // Send the mem on the relay output
  refreshRelaisFromMem(); 
}

void relaisMemWriter(int relaisMemNumber)
{
  for (int i=1;i<9;i++){
    if (relaisMemNumber == i){
      relaisMem[i]=1;
      clearAllMem(i); // Clear all the other mem, only one can be valid
      
    }else{
      relaisMem[i]=0;
    }
  }
  refreshRelaisFromMem();
}


// send the relaisMem[] array to the output pin
void refreshRelaisFromMem(){
  for (int i=1;i<9;i++){
    if (relaisMem[i]==1){
      digitalWrite(relaisOrder[i],HIGH);
      clearAllMem(i); //Clear all mem exept 
    }else {
      digitalWrite(relaisOrder[i],LOW);
    }
  }
}

void readPushButtonToMem()
{
  for (int i=1;i<9;i++){
    if (digitalRead(pushButtonOrder[i]) == LOW){
      relaisMem[i]=1;
      clearAllMem(i);
    }
  }
    
}
void clearAllMem(int exeptRelais){
  for (int i=0;i<9;i++){
    if (i != exeptRelais)
      relaisMem[i]=0;
  }  
}


