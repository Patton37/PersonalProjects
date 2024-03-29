/*********
 * 
 * 
 *Drew Patton 
 *
 HTML Formating: 
  Rui Santos
  Complete project details at http://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>

/*
// Replace with your network credentials
const char* ssid = "Big-Daddy";
const char* password = "IWantToGraduate";
*/

//wifi variables
const char* ssid     = "ESP8266-AP-4D"; //name of wifi network
const char* password = "POTR238"; //password of wifi network

WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String IO2State = "off";
int IO4Value;
int A0Value;
// Assign output variables to GPIO pins
const int IO2 = 2;
 int IO4 = 4;
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Setup
//_____________________________________________________________________________________________________________________________________________________________________
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(IO2, OUTPUT);
  pinMode(IO4, INPUT);
  pinMode(A0, INPUT); 
  
  // Set outputs to LOW
  digitalWrite(IO2, LOW);
  //digitalWrite(IO4, LOW);

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  server.begin();
}
//_____________________________________________________________________________________________________________________________________________________________________
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>


void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("GPIO 2 on");
              IO2State = "on";
              digitalWrite(IO2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("GPIO 2 off");
              IO2State = "off";
              digitalWrite(IO2, LOW);
            }

            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>3D Printed Smart Business BRICK</h1>");

            
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>GPIO 2 - State " + IO2State + "</p>");
            // If the IO2State is off, it displays the ON button       
            if (IO2State=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  

            //const char* IO4output = dtostrf(IO4Value,3,3); 
            //IO4Value = analogRead(IO4); 
           // IO4Value = (IO4Value * ( 3.3 / 1023.0)); 
            //float holder = (IO4Value* ( 3.3 / 1023.0));
            
            
//            Serial.print("\n IO4 Voltage is: ");
//            Serial.println(holder);
//            client.printf("<p>GPIO 4 - Voltage: %2.3f", holder);
//            client.printf("<p>");
           

              

            //A0Value = analogRead(A0); 
           // A0Value = (IO4Value * ( 3.3 / 1023.0)); 
            //float aHolder = (A0Value* ( 3.3 / 1023.0));
            
            
//            Serial.print("\n A0 Voltage is: ");
//            Serial.println(aHolder);
//            client.printf("<p>A0 - Voltage: %2.3f", aHolder);
//            client.printf("<p>");

            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
