#include <Servo.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int rojo = 0;
int verde = 0;
int azul = 0;
int color = 0;
 
Servo servoarriba;
Servo servoabajo;

void setup() {
  
  Serial.begin(9600);
  
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  pinMode(sensorOut, INPUT);
  
  // Frecuencia al 20%, funcionamiento óptimo
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  servoabajo.attach(2); //Servo abajo
  servoarriba.attach(3); //Servo arriba
   // Begins serial communication 
  
}
void loop() {
  
  servoarriba.write(136);
  delay(1000);
  servoarriba.write(100);
  delay(1000);

  color = colorlec();
  
  switch (color){
    case 1:
    servoabajo.write(40);
    delay(1000);
    break;
    case 2:
    servoabajo.write(90);
    delay(1000);
    break;
    case 3:
    servoabajo.write(130);
    delay(1000);
    break;
  }
  servoarriba.write(70);
  delay(1000);
}

int colorlec(){
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  rojo = pulseIn(sensorOut, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(rojo);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  verde = pulseIn(sensorOut, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(verde);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  azul = pulseIn(sensorOut, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.println(azul);
  delay(100);

  if (rojo > 145 & rojo < 175){
    color = 1;
  }
  if ( verde > 125 & verde < 155){
    color = 2;
  }
  if ( rojo > 105 & rojo < 130 & verde > 100 & verde < 135){
    color = 3;
  }

  return color;
}
