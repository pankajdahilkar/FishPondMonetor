/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>

#ifndef APSSID
#define APSSID "Parking"
#define APPSK  "Parking1234"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

WiFiServer server(80);
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
String Slot_1 = "card_green";
String Slot_1_status = "Empty";
String Slot_2 = "card_green";
String Slot_2_status = "Empty";
String Slot_3 = "card_green";
String Slot_3_status = "Empty";
String Slot_4 = "card_green";
String Slot_4_status = "Empty";
int LED = 2;   // led connected to GPIO2 (D4)
int s1 = 1;
int s2 = 1;
int s3 = 1;
int s4 = 1;
int total_available = 0;
void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  check_parking();
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while (!client.available())
  {
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //*------------------HTML Page Code---------------------*//
  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println(" <!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<meta http-equiv=\"refresh\" content=\"10\" > ");

  client.println("<style>");
  client.println("* {");
  client.println("  box-sizing: border-box;");
  client.println("}");
  client.println("body {");
  client.println("  font-family: Arial, Helvetica, sans-serif;");
  client.println("}");
  /* Float four columns side by side */
  client.println(".column {");
  client.println("  float: left;");
  client.println("  width: 25%;");
  client.println("  padding: 0 10px;");
  client.println("}");
  /* Remove extra left and right margins, due to padding */
  client.println(".row {margin: 0 -5px;}");
  /* Clear floats after the columns */
  client.println(".row:after {");
  client.println(" content: \"\";");
  client.println("  display: table;");
  client.println("  clear: both;");
  client.println("   padding: 20px;");
  client.println("}");
  /* Responsive columns */
  client.println("@media screen and (max-width: 600px) {");
  client.println("  .column {");
  client.println("    width: 100%;");
  client.println("    display: block;");
  client.println("    margin-bottom: 20px;");
  client.println("  }");
  client.println("}");
  /* Style the counter cards */
  client.println(".card_red {");
  client.println("  box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2);");
  client.println("  padding: 16px;");
  client.println("  text-align: center;");
  client.println("  background-color: red;");
  client.println("}");
  client.println(".card_green {");
  client.println("  box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2);");
  client.println("  padding: 16px;");
  client.println("  text-align: center;");
  client.println("  background-color: green;");
  client.println("}");
  client.println("</style>");
  client.println("</head>");
  client.println("<body>");
  client.println("<h2>SMART PARKING </h2>");
  client.println("<p> Check parking availability </p>");
  String Availabe = String(total_available);

  client.println("<p> parking slots available = " + Availabe + "</p>");

  client.println("<div class=\"row\">");
  client.println("<div class=\"column\">");
  client.println("<div class=\"" + Slot_1 + "\">");
  client.println("<h3>SLOT 1 </h3>");
  client.println("<p>" + Slot_1_status + "</p>");
  client.println("</div>");
  client.println("</div>");
  client.println("<div class=\"column\">");
  client.println("<div class=\"" + Slot_2 + "\">");
  client.println("<h3> SLOT 2 </h3>");
  client.println("<p>" + Slot_2_status + "</p>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("<div class=\"row\">");
  client.println("<div class=\"column\">");
  client.println("<div class=\"" + Slot_3 + "\">");
  client.println("<h3>SLOT 3 </h3>");
  client.println("<p>" + Slot_3_status + "</p>");
  client.println("</div>");
  client.println("</div>");
  client.println("<div class=\"column\">");
  client.println("<div class=\"" + Slot_4 + "\">");
  client.println("<h3>SLOT 4 </h3>");
  client.println("<p>" + Slot_4_status + "</p>");
  client.println("</div>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

void check_parking()
{
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    Serial.println(data);
    if (data == 'a') {
      s1 = 1;
      Slot_1 = "card_green";
      Slot_1_status = "Empty";
    }
    if (data == 'b') {
      s1 = 0;

      Slot_1 = "card_red";
      Slot_1_status = "Busy";
    }

    if (data == 'c') {
      s2 = 1;

      Slot_2 = "card_green";
      Slot_2_status = "Empty";
    }
    if (data == 'd') {
      s2 = 0;
      Slot_2 = "card_red";
      Slot_2_status = "Busy";
    }

    if (data == 'e') {
      s3 = 1;
      Slot_3 = "card_green";
      Slot_3_status = "Empty";
    }
    if (data == 'f') {
      s3 = 0;
      Slot_3 = "card_red";
      Slot_3_status = "Busy";
    }

    if (data == 'g') {
      s4 = 1;
      Slot_4 = "card_green";
      Slot_4_status = "Empty";
    }
    if (data == 'h') {
      s4 = 0;
      Slot_4 = "card_red";
      Slot_4_status = "Busy";
    }

  }
  total_available = s1 + s2 + s3 + s4;

}
