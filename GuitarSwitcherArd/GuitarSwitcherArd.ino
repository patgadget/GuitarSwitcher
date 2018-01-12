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

//Definition des pins utiliser pour les sorties relais
#define R1 A0
#define R2 A1
#define R3 A2
#define R4 A3
#define R5 A4
#define R6 A5
#define R7 5
#define R8 4




void setup() {
  // Configuration des entree/sortie
  pinMode(FS1, INPUT);
  pinMode(FS2, INPUT);
  pinMode(FS3, INPUT);
  pinMode(FS4, INPUT);
  pinMode(FS5, INPUT);
  pinMode(FS6, INPUT);
  pinMode(FS7, INPUT);
  pinMode(FS8, INPUT);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
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
  }
  
}
