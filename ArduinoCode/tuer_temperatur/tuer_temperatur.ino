#include <DHT.h>
#include <WiFi.h>
#include <string.h>;
//char ssid[32] = "WLAN";
//char pwd[64] = "83384356414185029572";
char ssid[32] = "Ka";
char pwd[64] = "12345678";
const char* server = "neronelo.ddns.net";
const char* script = "/Projekt/Sensoren/Tuer.php";    //Script Pfad Tuer
const char* scriptT = "/Projekt/Sensoren/Temperatur.php";   // Script Pfad Temperatur

const int triggerPin = 18;
const int echoPin=19;
DHT dht(16,DHT11);

int letzterWert=0;
float letzterWertTemperatur= 0;

void wlanAufbau(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  //Verbinde mit Netzwerk
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  WiFiClient client;
  if((!client.connect(server,80))or (!client.connect(server,443))){
    Serial.println("HTTP Verbindung fehlgeschlagen");
  }
}

void senden(float x,const char* script) {
  // Verbinde mit dem Webserver
  WiFiClient client;
  const int httpPort = 80;
  int erg;
  do
  {
    erg = client.connect(server, httpPort);
  } while (erg!=1);

  // Baue URL-String zusammen und setze Messwerte ein
  String url = script;
  url += "?t=";
  url += x;
 
  // Baue HTTP-Verbindung auf
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
  client.stop();
}

void senden2(int x,const char* script) {
  // Verbinde mit dem Webserver
  WiFiClient client;
  const int httpPort = 80;
  int erg;
  do
  {
    erg = client.connect(server, httpPort);
  } while (erg!=1);

  // Baue URL-String zusammen und setze Messwerte ein
  String url = script;
  url += "?t=";
  url += x;
 
  // Baue HTTP-Verbindung auf
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
  client.stop();
}

int messen(){
  digitalWrite(triggerPin, 0);
  delayMicroseconds(2);
  digitalWrite(triggerPin, 1);
  delayMicroseconds(10);
  digitalWrite(triggerPin, 0);
  long zeit = pulseIn(echoPin, 1);
  int lange = zeit *0.034/2;
  return(lange);
}

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
  
  wlanAufbau();
}

void loop() {
  int ka = messen();
  float kaT = dht.readTemperature();
  Serial.println(ka);
  Serial.println(kaT);
  if (ka != letzterWert){
    senden2(ka,script);
  }
  letzterWert=ka;
  if (kaT!= letzterWertTemperatur){
    senden(kaT,scriptT);
  }
  letzterWertTemperatur = kaT;
  
  delay(1000);
  
}
