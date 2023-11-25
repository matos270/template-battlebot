#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//Librerias propias
#include "index.h" //Nuestra página web en HTML 

ESP8266WebServer server(80); //Crea el objeto server en el puerto 80

//Nombre y password del punto WIFI
const char *ssid = "BattleBotDesierto";
// const char *password = "123456"; //no usamos password


/** Handle Root
 * @brief Envía el contenido de index.h
 */
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


/** Handle Button Request
 * @brief Esta función toma los valores enviados desde la página web y según su valor, llama a distintas funciones de motores.
  * Los botones de la página web ejecutan esta funcion -> sendRequest('http://192.168.4.1/B?val=1') 
 * La función sendRequest() crea una instancia de XMLHttpRequest() y la envía a través de WiFi a nuestra ESP8266.
 */
void handleButtonRequest(void) {

  //La ESP recibe requests con parametros A,B,V (y C) con numeros enteros entre 0 y 100, representando las velocidades de los motores A, B (y C) y la velocidad maxima actual de los motores A y B

  int velocidadA = server.arg("A").toInt(); // guarda argumento A en una variable, velocidad de motor izquierdo
  int velocidadB = server.arg("B").toInt(); // guarda argumento B en una variable, velocidad de motor derecho
  int velocidadC = server.arg("C").toInt(); // guarda argumento C en una variable, velocidad de motor arma
  int velocidad = server.arg("V").toInt();  // guarda argumento V en una variable, velocidad de movimiento del robot
  SPEED_A = MAX_SPEED_A * velocidad / 100; //calculo de las velocidades maximas actuales en base a las velocidades maximas y la velocidad enviada
  SPEED_B = MAX_SPEED_B * velocidad / 100;
  motor_control(velocidadA, 'a'); // codigo para controlar motor rueda izquierda
  motor_control(velocidadB, 'b'); // codigo para controlar motor rueda derecha
  motor_control(velocidadC, 'c'); // codigo para controlar velocidad de un tercer motor (arma)


  // Serial.print(velocidadC);  //comunicacion serial para debugging  
  // Serial.println("  ");

  server.send(200, "text/plain", "OK");
}




/** Run Web Server
 * @brief Función principal que configura la conección wifi, crea el servidor y conecta las funciones.
 */

void run_web_server(void) {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Create a new SoftAP network
  WiFi.softAP(ssid);


  // Print the IP address of the SoftAP network
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Copien esta IP y péguenla en su navegador");




  server.on("/Button", HTTP_GET, handleButtonRequest); //Cuando estemos en la página Button, llamamos a la función handleButtonRequest y le 
  server.on("/", handleRoot);      //Which routine to handle at root location
  
  // Set up web server
  server.onNotFound([]() {
    handleRoot();
  });

  server.begin();
  Serial.println("Web server started");
}

void handle_client(void) {
  server.handleClient();
}