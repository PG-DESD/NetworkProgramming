//////////////////////////////////////////////////////////////////////////////////
// Please use Your Mobile HotSpot to Test This Program                          //
// Also Note that CDAC Network has Jammers that Block the HOTSPOT of your Mobile//
//Client and Server Must be Connected to same HotSpot//
////////////////////////////////////////////////
#include <WiFi.h>

String  ClientRequest;
//Below IP Address Will be Used by Client to Connect to this Server
IPAddress staticIP(192,168,1,21); 
//Below is the IP Address of the Mobile Gateway
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);   

char ssid[] = "Benga_Boyzzzz";    // your network SSID (name)
char pass[] = "Benga@4321"; // your network password (use for WPA, or use as key for WEP)

WiFiServer server(80);
WiFiClient client;

String myresultat;

String ReadIncomingRequest()
{
    while(client.available()) 
    {
      ClientRequest = (client.readString());
      if ((ClientRequest.indexOf("HTTP/1.1")>0)&&(ClientRequest.indexOf("/favicon.ico")<0))
        {
          myresultat = ClientRequest;
        }
    }
  return myresultat;
}

void setup()
{
ClientRequest = "";

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
  Serial.println("Configuring IP for Server");
  Serial.println((WiFi.localIP()));
  server.begin();

}


void loop()
{

    client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    ClientRequest = (ReadIncomingRequest());
    client.flush();
    Serial.println("HTTP Request From");
    Serial.println((client.remoteIP()));
    ClientRequest.remove(0, 188);//to remove Http Header
    Serial.println(ClientRequest);

}
