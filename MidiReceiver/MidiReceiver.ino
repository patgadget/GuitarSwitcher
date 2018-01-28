// Midi Receiver
// 


// The only available pin for PWM are: 3,5,6,9,10,11
#define pin_RED 11
#define pin_GREEN 5
#define pin_BLUE 6
#define pin_LED 13
#define MIDI_CHANNEL 1 //1 to 16 - Midi Channel number
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
  if (Serial1.available() > 0) {
    incomingByte = Serial1.read();
      if (incomingByte != MSG_MIDI_ACT_SENSE){ // Si ce n'est pas un ActiveSense on continue http://midi.teragonaudio.com/tech/midispec/sense.htm
        Serial.println(incomingByte, HEX);
      }
    // Message MIDI car le bit 7 a ON
    if (incomingByte&0x80){
      firstByte=-1; //Donc ce n'est pas un DATA
      if (incomingByte != MSG_MIDI_ACT_SENSE){ // Si ce n'est pas un ActiveSense on continue http://midi.teragonaudio.com/tech/midispec/sense.htm
        // Est ce la Messagee 0x90 NOTE ON?
        // et le bon Channel Midi?
        if (!((incomingByte & 0xF0) ^ MSG_MIDI_NOTE_ON ) & !((incomingByte& 0x0F) ^ (MIDI_CHANNEL-1))){
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
        if (lastValidMessage == MSG_MIDI_NOTE_ON){ //et c'est NOTE ON
          if (firstByte < 0 ){
            if (incomingByte == 0x26){
              //Note 0x26 ON,
              firstByte=0x26;
            }
            if (incomingByte == 0x27){
              //Note 0x27 ON
              firstByte=0x27;
            }
          }
          else{
            if (firstByte == 0x26 ){
              if (incomingByte | 1){ // Any Velocity
                digitalWrite(pin_LED, HIGH);
              }
            }  
            if (firstByte == 0x27 ){
              if (incomingByte | 1){ // Any Velocity
                digitalWrite(pin_LED, LOW);
              }
            }
          firstByte=-1; // Receive my 2 bytes
          }
        }
      }
    }
  }
  //analogWrite(pin_RED,0);
  //analogWrite(pin_GREEN,0);
  //analogWrite(pin_BLUE,0);
}
