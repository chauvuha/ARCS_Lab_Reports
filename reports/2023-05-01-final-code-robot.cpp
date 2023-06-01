/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";

WiFiServer server(80);

// Import the library for the servo run
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


void setup() {
  pwm.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
 
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
 

}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");
            client.print("Click <a href=\"/F\">here</a> to run the servos forward.<br>");
            client.print("Click <a href=\"/B\">here</a> to run the servos backward.<br>");
            client.print("Click <a href=\"/S\">here</a> to stop the servos.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);    // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);     // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /F")) {
           // wheel 3
            for (int i = 2; i < 4; i++) {
                pwm.setPWM(i, 0, 100);
            }  
            // wheel 1
            for (int i = 4; i < 6; i++) {
                pwm.setPWM(i, 0, 100);
            }  
             // wheel 4
            for (int i = 0; i < 2; i++) {
                pwm.setPWM(i, 0, 800);
            }    
               // wheel 2
            for (int i = 6; i < 8; i++) {
                pwm.setPWM(i, 0, 800);
            }        
           
        }
         if (currentLine.endsWith("GET /B")) { 
            // wheel 3
            for (int i = 2; i < 4; i++) {
                pwm.setPWM(i, 0, 800);
            }  
            // wheel 1
            for (int i = 4; i < 6; i++) {
                pwm.setPWM(i, 0, 800);
            }  
             // wheel 4
            for (int i = 0; i < 2; i++) {
                pwm.setPWM(i, 0, 100);
            }    
               // wheel 2
            for (int i = 6; i < 8; i++) {
                pwm.setPWM(i, 0, 100);
            }        
                     
        }
        if (currentLine.endsWith("GET /S")) {
            // wheel 4
            for (int i = 0; i < 2; i++) {
                pwm.setPWM(i, 0, 274);
            }    
            // wheel 3
            for (int i = 2; i < 4; i++) {
                pwm.setPWM(i, 0, 270);
            }  
            // wheel 1
            for (int i = 4; i < 6; i++) {
                pwm.setPWM(i, 0, 270);
            }  
            // wheel 2
            for (int i = 6; i < 8; i++) {
                pwm.setPWM(i, 0, 267);
            }              
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
