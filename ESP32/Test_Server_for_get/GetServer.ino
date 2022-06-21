/*
  WiFi Get Server
 */

#include <SPI.h>
#include <WiFi.h>

char ssid[] = "Benga_Boyzzzz";      // your network SSID (name)
char pass[] = "Benga@4321";   // your network password

int status = WL_IDLE_STATUS;
//Below IP Address Will be Used by Client to Connect to this Server
IPAddress staticIP(192,168,1,21); 
//Below is the IP Address of the Mobile Gateway
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(80);

void setup() {

//  ClientRequest = "";

Serial.begin(115200);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin(ssid,pass);
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  WiFi.config(staticIP,gateway,subnet);
  server.begin();

  // you're connected now, so print out the status:

  printWifiStatus();
}

void loop() {

  // listen for incoming clients
  WiFiClient client = server.available();

  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    bool currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          // dummy output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
  
            int sensorReading = 20;
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
