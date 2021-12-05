#include <WiFi.h>
#include <string.h>;

char ssid[32] = "WLAN";
char pwd[64] = "WLAN";
const char* server = "192.168.2.121";
const char* script = "/Projekt/Sensoren/Tuer.php";  //Script Adresse
const int pin = 34;

WiFiClient client;

int x = 0;

void setup() {
  
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);


  // Verbinde mit dem Netzwerk
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Teste, ob das Netzwerk funktioniert
  WiFiClient client;
  if (!client.connect(server,80)) {
    Serial.println("HTTP-Verbindung geht nicht");
  }

}

void senden(int x) {

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


void loop() {

  
  delay(20);
  x=analogRead(pin);
  if( x > 0){
    Serial.println(x);
    //senden(x);
  };
}
