#include <HTTP_Method.h>
#include <Uri.h>
#include <WebServer.h>
#include <stdio.h>
#include <ESP32Servo.h>

#include <WiFi.h>
// ip - 192.168.4.1
// Replace with your network credentials
const char* ssid = "Esp32";
const char* password = "123456789000";

Servo myservo;
Servo myservo2;
int pos = 0;
int pos2 = 0;
int a = 0;
int ba = 0;
int c = 0;
int d = 0;
int Speed = 99;
const int IA1=13;
const int IA2 = 14;
int l1 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "wait";
String output27State = "wait";
String output28State = "wait";
String output29State = "wait";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;
const int output28 = 28;
const int output29 = 29;

// назначаем имена для портов
#define s2  25
#define s3  32
#define out 34
// освобождаем память для переменных
byte red = 0;
byte green = 0;
byte blue = 0;

const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 =1;
const int resolution = 8;


void color()
{
 // если 2 и 3 порты отключить, то получим значение красного цвета
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

 // если 3 порт включить, а 2 отключить, то получим синий цвет
  digitalWrite(s3, HIGH);
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

 // если 2 включить, а 3 отключить, то получим зеленый цвет
  digitalWrite(s2, HIGH);
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 

}

void Green()
{
  if (l3 = 1)
    {
      Serial.println("it is GREEN");
      for (pos = 0; pos <= 180; pos += 1)
      {  
        myservo.write(pos);
      }     
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
      }
    }
    l3 = 0;
}

void Red()
{
  if (l1 = 1)
    {
      Serial.println("it is RED");
      for (pos = 0; pos <= 180; pos += 1)
      {  
        myservo.write(pos);
      }     
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
      }
    }
    l1 = 0;
}

void Blue()
{
  if (l2 = 1)
    {
      Serial.println("it is BLUE");
      for (pos = 0; pos <= 180; pos += 1)
      {  
        myservo.write(pos);
      }     
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
      }
      delay(15);
    }
    l2 = 0;
}

void Yellow()
{
  if (l4 = 1)
    {
      Serial.println("it is YELLOW");
      for (pos = 0; pos <= 180; pos += 1)
      {  
        myservo.write(pos);
      }     
      for (pos = 180; pos >= 0; pos -= 1)
      {
        myservo.write(pos);
      }
      delay(15);
    }
    l4 = 0;
}

int r = 0;
int g = 0;
int b = 0;

int R[10];
int G[10];
int B[10];


void setup() {
  
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  pinMode(output28, OUTPUT);
  pinMode(output29, OUTPUT);
  
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  digitalWrite(output28, LOW);
  digitalWrite(output29, LOW);

  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  myservo.attach(27);
  myservo2.attach(26);

  pinMode(IA1, OUTPUT);
  pinMode(IA2, OUTPUT);

  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcAttachPin(IA1, ledChannel1);
  ledcAttachPin(IA2, ledChannel2);
  Speed = 0;
  ledcWrite(ledChannel1, 0); 
  ledcWrite(ledChannel2, 255); 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.begin();
}

void loop()
{
  color();
  for (int i = 0; i < 9; i++)
  {
    R[i] = red;
    G[i] = green;
    B[i] = blue;
  }
  for (int i = 0; i < 9; i++)
  {
    r = r + R[i];
    g = g + G[i];
    b = b + B[i];
  }

  r = r/10;
  g = g/10;
  b = b/10;

  Serial.println(r);
  Serial.println(g);
  Serial.println(b);

  WiFiClient client = server.available();  // Listen for incoming clients

  Serial.print(" red: " + String(red));
  Serial.print(" green: " + String(green));
  Serial.println(" blue: " + String(blue));
  // выводим значения цветов
  if (red > 35 && red < 45)
  {
    l1 = 1;
    Red();
    ledcWrite(ledChannel1, 255); 
    ledcWrite(ledChannel2, 0); 
    delay(1000);
    ledcWrite(ledChannel1, 0); 
    ledcWrite(ledChannel2, 255); 
  }
  
  if (blue > 15 && blue < 25)
  {
    l2 = 1;
    Blue();
    ledcWrite(ledChannel1, 255); 
    ledcWrite(ledChannel2, 0); 
    delay(1000);
    ledcWrite(ledChannel1, 0); 
    ledcWrite(ledChannel2, 255); 
  }                    
  if (green > 25 && green < 40)
  {
    l3 = 1;
    Green();
    ledcWrite(ledChannel1, 255); 
    ledcWrite(ledChannel2, 0); 
    delay(1000);
    ledcWrite(ledChannel1, 0); 
    ledcWrite(ledChannel2, 255); 
  }
  if (red > 20 && green > 20)
  {
    l4 = 1;
    Yellow();
    ledcWrite(ledChannel1, 255); 
    ledcWrite(ledChannel2, 0); 
    delay(1000);
    ledcWrite(ledChannel1, 0); 
    ledcWrite(ledChannel2, 255); 
  }
  
  delay(500);

  if (client)
  {                     // If a new client connects,
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
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
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "drop";
              a=1;
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "wait";
              a=0;
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "drop";
              b=1;
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "wait";
              b=0;
              digitalWrite(output27, LOW);
            } else if (header.indexOf("GET /28/on") >= 0) {
              Serial.println("GPIO 28 on");
              output28State = "drop";
              c=1;
              digitalWrite(output28, HIGH);
            } else if (header.indexOf("GET /28/off") >= 0) {
              Serial.println("GPIO 28 off");
              output28State = "wait";
              c=0;
              digitalWrite(output28, LOW);
            } else if (header.indexOf("GET /29/on") >= 0) {
              Serial.println("GPIO 29 on");
              output29State = "drop";
              d=1;
              digitalWrite(output29, HIGH);
            } else if (header.indexOf("GET /29/off") >= 0) {
              Serial.println("GPIO 29 off");
              output29State = "wait";
              d=0;
              digitalWrite(output29, LOW);
            }
            
  

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Zelenograd Predators</h1>");
            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>Red button " + output26State + "</p>");
            // If the output26State is off, it displays the ON button
            if (output26State == "wait") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">Drop button..</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">Wait red button</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>Blue button " + output27State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output27State == "wait") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">Drop button..</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">Wait blue button..</button></a></p>");
            }
            client.println("<p>Yellow button " + output28State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output28State == "wait") {
              client.println("<p><a href=\"/28/on\"><button class=\"button\">Drop button..</button></a></p>");
            } else {
              client.println("<p><a href=\"/28/off\"><button class=\"button button2\">Wait yellow button..</button></a></p>");
            }
            client.println("<p>Green button " + output29State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output29State == "wait") {
              client.println("<p><a href=\"/29/on\"><button class=\"button\">Drop button..</button></a></p>");
            } else {
              client.println("<p><a href=\"/29/off\"><button class=\"button button2\">Wait green button..</button></a></p>");
            }
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
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