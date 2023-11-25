// nombramos los pines
int motor_A1 = 14; // pin motor A1
int motor_A2 = 12; // pin motor A2
int pin_vel_A = 15; // pin control de velocidad motor A

int motor_B1 = 4; // pin motor B1
int motor_B2 = 5; // pin motor B2
int pin_vel_B = 13; // pin control de velocidad motor A

int pin_vel_C = 2;

int MAX_SPEED_A = 255; //velocidades maximas, ajustar para que robot avance recto
int MAX_SPEED_B = 255;
int MAX_SPEED_C = 255; //velocidad maxima robot arma, reducir por temas de seguridad

int SPEED_A = 255; //velocidad maxima actual, se ajusta en base a la velocidad seleccionada en la aplicacion
int SPEED_B = 255;

void motors_setup()
{
  // configuramos el motor A como salida (OUTPUT)
  pinMode(motor_A1, OUTPUT); // motor A1
  pinMode(motor_A2, OUTPUT); // motor A2
  pinMode(pin_vel_A, OUTPUT); // control velocidad A
  
  // configuramos el motor B como salida (OUTPUT)
  pinMode(motor_B1, OUTPUT); // motor B1
  pinMode(motor_B2, OUTPUT); // motor B2
  pinMode(pin_vel_B, OUTPUT); // control velocidad B

  pinMode(pin_vel_C,OUTPUT);
  
  // partimos con el motor A apagado (LOW)
  digitalWrite(motor_A1, LOW); // motor A1
  digitalWrite(motor_A2, LOW); // motor A2

  // partimos con el motor B apagado (LOW)
  digitalWrite(motor_B1, LOW); // motor A1
  digitalWrite(motor_B2, LOW); // motor A2
}

void motor_control(int velocidad, char motor){ //velocidad debe ser un entero entre -100 y 100, motor un char (a,b,c), acciona el motor marcado por el char a una velocidad proporcional al valor entregado y la velocidad maxima de el motor, valores negativos cambian la direccion de giro
  switch(motor) {
    case 'a':
      digitalWrite(motor_A1, velocidad > 0);
      digitalWrite(motor_A2, velocidad < 0);
      analogWrite(pin_vel_A, map(abs(velocidad),0,100,0,SPEED_A));
      break;
    case 'b':
      digitalWrite(motor_B1, velocidad > 0);
      digitalWrite(motor_B2, velocidad < 0);
      analogWrite(pin_vel_B, map(abs(velocidad),0,100,0,SPEED_B));
      break;
    case 'c':
      analogWrite(pin_vel_C, map(abs(velocidad),0,100,0,MAX_SPEED_C));
      break;
    default:
      Serial.println(String(velocidad > 0));
      Serial.println(String(velocidad < 0));
      Serial.println(String(velocidad));
  }
}