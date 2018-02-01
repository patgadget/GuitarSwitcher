/*******************************************
Programme pour selectionner une sortie d'ampli
selon un Message Midi sur le Cannal 9 
Message: Program Change 1 a 8*/


//Definition des pins utilise pour input des foot switch

#define FS1 3
#define FS2 12
#define FS3 11
#define FS4 10
#define FS5 9
#define FS6 8
#define FS7 7
#define FS8 6
#define FSMUTE 5


//Definition des pins utiliser pour les sorties relais
#define R1 13
#define R2 2
#define R3 A5
#define R4 A4
#define R5 A3
#define R6 A2
#define R7 A1
#define R8 A0
#define RMUTE 4

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

void setup()
{
  //Serial1.begin(31250);
  Serial.begin(31250);
  
  // Baud rate set to 31250 Baud https://en.wikipedia.org/wiki/MIDI_1.0#Hardware_transport_(electrical_and_mechanical_connections)


  // Configuration des entree/sortie
  pinMode(FS1, INPUT_PULLUP);
  pinMode(FS2, INPUT_PULLUP);
  pinMode(FS3, INPUT_PULLUP);
  pinMode(FS4, INPUT_PULLUP);
  pinMode(FS5, INPUT_PULLUP);
  pinMode(FS6, INPUT_PULLUP);
  pinMode(FS7, INPUT_PULLUP);
  pinMode(FS8, INPUT_PULLUP);
  pinMode(FSMUTE, INPUT_PULLUP);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(RMUTE, OUTPUT);
  for (int i=0;i<10;i++){
    relaisMem[i]=0;
  }

}

void loop()
{    
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
      // Est ce la Messagee 0x90 NOTE ON?
      // et le bon Channel Midi?
      if (!((incomingByte & 0xF0) ^ MSG_MIDI_PROG_CHG ) & !((incomingByte& 0x0F) ^ (MIDI_CHANNEL-1))){
        lastValidMessage= (incomingByte & 0xF0); //On Garde la partie du message de gauche et on detruit le channel Midi
      }
    }
    else{
      // Si c'est un timecode on srap et on repar a neuf
      lastValidMessage=-1;
    }
  }
  else{
    if (lastValidMessage > 0){ //j'ai deja recu une Messagee Midi
      if (lastValidMessage == MSG_MIDI_PROG_CHG){ //et PROGRAM CHANGE
        if (firstByte < 0 ){
          if (incomingByte == 0x01){
            relaisMemWriter(1);
          }
          if (incomingByte == 0x02){
            relaisMemWriter(2);
          }
          if (incomingByte == 0x03){
            relaisMemWriter(3);
          }
          if (incomingByte == 0x04){
            relaisMemWriter(4);
          }
          if (incomingByte == 0x05){
            relaisMemWriter(5);
          }
          if (incomingByte == 0x06){
            relaisMemWriter(6);
          }
          if (incomingByte == 0x07){
            relaisMemWriter(7);
          }
          if (incomingByte == 0x08){
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
  for (int i=0;i<9;i++){
    if (relaisMem[i]==1)
      if (i==1){
        digitalWrite(R1,HIGH);
      }else {
        digitalWrite(R1,LOW);
      }
      if (i==2){
        digitalWrite(R2,HIGH);
      }else {
        digitalWrite(R2,LOW);
      }
      if (i==3){
        digitalWrite(R3,HIGH);
      }else {
        digitalWrite(R3,LOW);
      }
      if (i==4){
        digitalWrite(R4,HIGH);
      }else {
        digitalWrite(R4,LOW);
      }
      if (i==5){
        digitalWrite(R5,HIGH);
      }else {
        digitalWrite(R5,LOW);
      }
      if (i==6){
        digitalWrite(R6,HIGH);
      }else {
        digitalWrite(R6,LOW);
      }
      if (i==7){
        digitalWrite(R7,HIGH);
      }else {
        digitalWrite(R7,LOW);
      }
      if (i==8){
        digitalWrite(R8,HIGH);
      }else {
        digitalWrite(R8,LOW);
      }
  }
}

void relaisMemWriter(int relaisMemNumber)
{
  for (int i=1;i<9;i++){
    if (relaisMemNumber == i){
      relaisMem[i]=1;
      
    }else{
      relaisMem[i]=0;
    }
  }
}

