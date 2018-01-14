/*******************************************
Programme pour selectionner une sortie d'ampli
selon une Foot Switch */


//Definition des pins utilise pour input des foot switch

#define FS1 13
#define FS2 12
#define FS3 11
#define FS4 10
#define FS5 9
#define FS6 8
#define FS7 7
#define FS8 6
#define FSMUTE 5


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




void setup() {
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
}

void loop() {
  if (!FS1){
    digitalWrite(R1,HIGH);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS2){
    digitalWrite(R1,LOW);
    digitalWrite(R2,HIGH);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS3){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,HIGH);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS4){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,HIGH);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS5){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,HIGH);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS6){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,HIGH);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS7){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,HIGH);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,LOW);
  }
  if (!FS8){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,HIGH);
    digitalWrite(RMUTE,LOW);
  }
  if (!FSMUTE){
    digitalWrite(R1,LOW);
    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);
    digitalWrite(R4,LOW);
    digitalWrite(R5,LOW);
    digitalWrite(R6,LOW);
    digitalWrite(R7,LOW);
    digitalWrite(R8,LOW);
    digitalWrite(RMUTE,HIGH);
  }
  
}
