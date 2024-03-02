int motorPin1 = 13;
int motorPin2 = 12;
int motorPin3 = 14;
int motorPin4 = 27;

int servoPin1 = 25;
int servoPin2 = 26;

int CarStat1 = 0;
int CarStat2 = 0;
int CarStat3 = 0;
int CarStat4 = 0;

int servoStat1 = 0;
int servoStat2 = 0;
int servoStat3 = 0;
int servoStat4 = 0;

int servoValue1 = 80;
int servoValue2 = 105;
int servoSpeed = 5;

int CamStat = 0;
int lightStat = 0;
int lightPin = 35;

int trigPin1 = 33;
int echoPin1 = 32;
int trigPin2 = 34;
int echoPin2 = 35;
int trigPin3 = 5;
int echoPin3 = 18;
int trigPin4 = 5;
int echoPin4 = 18;

int duration;
int distance;
int minDistance = 50;

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32Servo.h>

Servo servo1;
Servo servo2;

const char *ssid = "";
const char *password = "";

WebServer server(80);
const int led = 2;

void handleRoot() {
  digitalWrite(led, 1);  
 String HTML ="<!DOCTYPE html>\
  <html>\
  <head>\
  \t\n<title>CAR</title>\
  \t\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
  \n<style>\
 \na{\n\tdisplay:block\;\ntext-decoration:none\;\nfont-size:30px\;\ncursor:pointer\;\n}\n.btn{\nmargin:5px\;\n\ntext-align:center\;\nwidth:200px\;}\n";
  HTML +="</style>\n\n</head>\n\n<body>\n<h1>Esp_32-Car</h1>\n";
  
  if(CarStat1){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do1=off\">Forward</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do1=on\">Forward</a>\t\n\t</div>\n";
  }
  if(CarStat2){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do2=off\">Backward</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do2=on\">Backward</a>\t\n\t</div>\n";
  }
  if(CarStat3){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do3=off\">Left</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do3=on\">Left</a>\t\n\t</div>\n";
  }
  if(CarStat4){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do4=off\">Right</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do4=on\">Right</a>\t\n\t</div>\n";
  }
  if(servoStat1){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do5=off\">Pan Left</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do5=on\">Pan Left</a>\t\n\t</div>\n";
  }
  if(servoStat2){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do6=off\">Pan Right</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do6=on\">Pan Right</a>\t\n\t</div>\n";
  }
  if(servoStat3){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do7=off\">Tilt Up</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do7=on\">Tilt Up</a>\t\n\t</div>\n";
  }
  if(servoStat4){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do8=off\">Tilt Down</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do8=on\">Tilt Down</a>\t\n\t</div>\n";
  }
  if(CamStat){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do9=off\">Camera Center</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#90ee90\"  href=\"/motor?do9=on\">Camera Center</a>\t\n\t</div>\n";
  }
  if(lightStat){
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton\" style=\"background-color:#90ee90\"  href=\"/motor?do10=off\">Light On</a>\t\n\t</div>\n";
  }else{
    HTML +="\t<div class=\"btn\">\n\t\t<a class=\"angleButton \" style=\"background-color:#f56464\"  href=\"/motor?do10=on\">Light Off</a>\t\n\t</div>\n";
  }
  HTML +="</body>\n</html>\n";
  server.send(200, "text/html", HTML);  
  digitalWrite(led, 0);  
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo1.write(servoValue1);
  servo2.write(servoValue2);
  pinMode(lightPin, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  //pinMode(trigPin2, OUTPUT);
  //pinMode(echoPin2, INPUT);
  //pinMode(trigPin3, OUTPUT);
  //pinMode(echoPin3, INPUT);
  //pinMode(trigPin4, OUTPUT);
  //pinMode(echoPin4, INPUT);
  Serial.begin(115200);
  Serial.println("ESP32 Car");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("Esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/motor", HTTP_GET, motorControl);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

}

void ultraSonic(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  if(distance < minDistance){
    CarStat1 =0;
  }
}

void loop(void) {

  server.handleClient();

  ultraSonic(trigPin1,echoPin1);
  //ultraSonic(trigPin2,echoPin2);
  //ultraSonic(trigPin3,echoPin3);
  //ultraSonic(trigPin4,echoPin4);

  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  if(CarStat1)
  {
    digitalWrite(motorPin1, HIGH);  
    digitalWrite(motorPin4, HIGH);   
  }else if(CarStat2)
  {
    digitalWrite(motorPin2, HIGH);   
    digitalWrite(motorPin3, HIGH);   
  }else if(CarStat3)
  {
     digitalWrite(motorPin3, HIGH); 
    digitalWrite(motorPin1, HIGH); 
  }else if(CarStat4)
  {
    digitalWrite(motorPin4, HIGH);   
    digitalWrite(motorPin2, HIGH); 
  }
  else if(servoStat1)
  {
    if(servoValue1 <= 180){
    servoValue1 += servoSpeed;
    servo1.write(servoValue1);
    delay(1);
    }
  }
  else if(servoStat2)
  {
    if(servoValue1 >= 0){
    servoValue1 -= servoSpeed;
    servo1.write(servoValue1);
    delay(1);
    }
  }
    else if(servoStat3)
  {
    if(servoValue2 >= 0){
    servoValue2 -= servoSpeed;
    servo2.write(servoValue2);
    delay(1);
    }
  }
  else if(servoStat4)
  {
    if(servoValue2 <= 180){
    servoValue2 += servoSpeed;
    servo2.write(servoValue2);
    delay(1);
    }
  }
  else if(CamStat)
  {
    servoValue1 = 80;
    servoValue2 = 105;
    servo1.write(servoValue1);
    servo2.write(servoValue2);
    CamStat = 0;
  }
  else if(lightStat)
  {
    digitalWrite(lightPin, HIGH);
  }
  else if(!lightStat)
  {
    digitalWrite(lightPin, LOW);
  }
  delay(100);
}

void motorControl() {
  CarStat1 =0;
  CarStat2 =0;
  CarStat3 =0;
  CarStat4 =0;
  servoStat1 = 0;
  servoStat2 = 0;
  servoStat3 = 0;
  servoStat4 = 0;
  CamStat = 0;
  if(server.arg("do1") == "on")
  {
    CarStat1 =1;
  }else if(server.arg("do1") == "off"){
    CarStat1 =0;   
  }else if(server.arg("do2") == "on")
  {
    CarStat2 =1;
  }else if(server.arg("do2") == "off"){
    CarStat2 =0;   
  }else if(server.arg("do3") == "on")
  {
    CarStat3 =1;
  }else if(server.arg("do3") == "off"){
    CarStat3 =0;   
  }else if(server.arg("do4") == "on")
  {
    CarStat4 =1;
  }else if(server.arg("do4") == "off"){
    CarStat4 =0;   
  }else if(server.arg("do5") == "on")
  {
    servoStat1 =1;
  }else if(server.arg("do5") == "off"){
    servoStat1 =0;   
  }else if(server.arg("do6") == "on")
  {
    servoStat2 =1;
  }else if(server.arg("do6") == "off"){
    servoStat2 =0;   
  }
  else if(server.arg("do7") == "on")
  {
    servoStat3 =1;
  }else if(server.arg("do7") == "off"){
    servoStat3 =0;   
  }else if(server.arg("do8") == "on")
  {
    servoStat4 =1;
  }else if(server.arg("do8") == "off"){
    servoStat4 =0;   
  }else if(server.arg("do9") == "on")
  {
    CamStat =1;
  }else if(server.arg("do9") == "off"){
    CamStat = 0;   
  }else if(server.arg("do10") == "on")
  {
    lightStat =1;
  }else if(server.arg("do10") == "off"){
    lightStat = 0;   
  }
  handleRoot();
}