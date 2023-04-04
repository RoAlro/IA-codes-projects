#include <Servo.h>
#include <String.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int servos_giro_radial = 0;
int servos_inclinacion = 0;
int angulo_giro_radial = 135;
int angulo_inclinacion = 0;

String datos; 
String servos_giro_radial_str, servos_inclinacion_str;
String angulo_giro_radial_str, angulo_inclinacion_str;
volatile char coma = ',';

void setup() {
  servo1.attach(5, 500, 2500);
  servo2.attach(6, 450, 2450);
  servo3.attach(9, 500, 2405);
  servo4.attach(10, 500, 2400);
  Serial.begin(9600);  // Inicia la comunicación serie a 9600 baudios
  delay(1000);
  servo1.write(angulo_giro_radial*2/3);
  servo2.write(angulo_giro_radial*2/3); 
  servo3.write(angulo_inclinacion);
  servo4.write(180-angulo_inclinacion);
  delay(3000);
}

void loop() {
  if (Serial.available() > 0) {
    datos = Serial.readString();
    separador();
    if (servos_giro_radial == 1) {
      servo1.write(angulo_giro_radial*2/3);
      servo2.write(angulo_giro_radial*2/3); 
    }
    if (servos_inclinacion == 1) {
      servo3.write(angulo_inclinacion);
      servo4.write(180-angulo_inclinacion);
    }
  }
}
void separador(){
  servos_giro_radial_str = datos.substring(0, datos.indexOf(coma));
  servos_giro_radial = servos_giro_radial_str.toInt();
  datos = datos.substring(servos_giro_radial_str.length() + 1);

  servos_inclinacion_str = datos.substring(0, datos.indexOf(coma));
  servos_inclinacion = servos_inclinacion_str.toInt();
  datos = datos.substring(servos_inclinacion_str.length() + 1);

  angulo_giro_radial_str = datos.substring(0, datos.indexOf(coma));
  angulo_giro_radial = angulo_giro_radial_str.toInt();
  datos = datos.substring(angulo_giro_radial_str.length() + 1);

  angulo_inclinacion = datos.substring(0, datos.indexOf(coma)).toInt();
}
