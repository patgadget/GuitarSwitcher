// DMX Receiver
// DMX Channel 1,2,3 are copy onto RGB pin of the Arduino
// PWM are from 0-255 on those pins.

#define myubrr (16000000L/16/250000-1)

// The only available pin for PWM are: 3,5,6,9,10,11
#define pin_RED 11
#define pin_GREEN 5
#define pin_BLUE 6

void setup()
{
  Serial.begin(31250);
  pinMode(pin_BLUE,OUTPUT); //BLUE
  pinMode(pin_GREEN,OUTPUT); //GREEN
  pinMode(pin_RED,OUTPUT); //RED
  
  // Baud rate set to 31250 Baud https://en.wikipedia.org/wiki/MIDI_1.0#Hardware_transport_(electrical_and_mechanical_connections)
}

void loop()
{
    analogWrite(pin_RED,0);
    analogWrite(pin_GREEN,0);
    analogWrite(pin_BLUE,0);
}
