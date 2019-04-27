
#include <ESP8266WiFi.h>

String  i;
WiFiServer server(80);

void setup()
{
i = "";
Serial.begin(9600);
pinMode(4, OUTPUT);
  WiFi.disconnect();
  delay(3000);
   WiFi.begin("Realme 2 Pro","realme2pro123");
  Serial.println("Connecting to WiFi");
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print(".");
  }
  Serial.println("Wifi is Connected");
  Serial.println((WiFi.localIP().toString()));
  server.begin();

}



void loop()
{
    
    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    Serial.println(i);
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    //Serial.println(i);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");

      client.println("<button><a href= 'http://192.168.43.173/ON'>ON</a></button>");
      client.println("<button><a href='http://192.168.43.173/OFF'>OFF</a></button>");
      if(i=="ON")
      {
      Serial.println("LED is turned ON");
      client.println("<br>LED IS TURNED ON");
      }
      else if(i=="OFF")
      {
      Serial.println("LED is turned OFF");
      client.println("<br>LED is turned OFF");
      }
      client.println("</html>");
      delay(1);

}
