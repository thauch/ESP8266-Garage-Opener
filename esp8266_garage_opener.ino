#include <ESP8266WiFi.h>

const char* ssid     = "...";            // SSID to your WLAN
const char* password = "...";    // Password to your WLAN

int r1 = 5;       //relay connected to D1(note on nodemcu)/pin 5

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(3000);
  
  pinMode(r1, OUTPUT);
  digitalWrite(r1, LOW);
  
  // Connect to WLAN
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  Serial.println("");
  Serial.println("WLAN connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {

  String website;
  website +="HTTP/1.1 200 OK \n Content-Type: text/html\n Connection: close\n\n<!DOCTYPE HTML><html>";
  website +="<button style=\"width:100%;font-size: 120px;\"><a href=\"/one\">GarageDoor</a></button><br /></html>\n";

   // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  //Serial.println("something");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  int val;
  if (req.indexOf("/trigger") != -1) {
   digitalWrite(r1, HIGH);
   delay(1000);
   digitalWrite(r1, LOW);
  }
  else if (req.indexOf("/trigger2") != -1) {
  //if you want to add more
  }
  else {
    Serial.println("Not a valid url.");
  }
  client.flush();

  // Prepare the response - if you want to add more text do it to string s.
  String s = website; 

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected.");
}
