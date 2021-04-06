#include <ESP8266WiFi.h>
const char* ssid = "Pankaj D";    //  Your Wi-Fi Name
const char* password = "pankaj4u24";   // Wi-Fi Password
int LED = 2;   // led connected to GPIO2 (D4)
WiFiServer server(80);

String Slot_1 = "card_green";
String Slot_1_status = "Empty";
String Slot_2 = "card_green";
String Slot_2_status = "Empty";
String Slot_3 = "card_green";
String Slot_3_status = "Empty";
String Slot_4 = "card_green";
String Slot_4_status = "Empty";

void setup()
{
  Serial.begin(9600); //Default Baudrate
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  server.begin();  // Starts the Server
  Serial.println("Server started");
  Serial.print("IP Address of network: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: https://"); // Will print IP address in URL format
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop()
{
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    Serial.println(data);
    if (data == 'a') {
      Slot_1 = "card_green";
      Slot_1_status = "Empty";
    }
    if (data == 'b') {
      Slot_1 = "card_red";
      Slot_1_status = "Busy";
    }

     if (data == 'c') {
      Slot_2 = "card_green";
      Slot_2_status = "Empty";
    }
    if (data == 'd') {
      Slot_2 = "card_red";
      Slot_2_status = "Busy";
    }

     if (data == 'e') {
      Slot_3 = "card_green";
      Slot_3_status = "Empty";
    }
    if (data == 'f') {
      Slot_3 = "card_red";
      Slot_3_status = "Busy";
    }
    
    if (data == 'g') {
      Slot_4 = "card_green";
      Slot_4_status = "Empty";
    }
    if (data == 'h') {
      Slot_4 = "card_red";
      Slot_4_status = "Busy";
    }

  }
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
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(LED, HIGH); // Turn LED ON
    value = HIGH;
  }

  if (request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(LED, LOW); // Turn LED OFF
    value = LOW;
  }
  //*------------------HTML Page Code---------------------*//
  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println(" <!DOCTYPE html>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
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
