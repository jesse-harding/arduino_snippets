/*
  Simple WebSocket client for ArduinoHttpClient library
  Connects to the WebSocket server, and sends a hello
  message every 300 milliseconds

  created 28 Jun 2016
  by Sandeep Mistry
  modified 22 Jan 2019
  by Tom Igoe
  modified 2 Mar 2024
  by Jesse Harding (with features from https://github.com/tigoe/DataloggingExamples/tree/main/WiFiDatalogger)

  this example is in the public domain
*/

// unity websockets: https://docs-multiplayer.unity3d.com/transport/current/minimal-workflow-ws/
// unity json documentation https://docs.unity3d.com/ScriptReference/JsonUtility.html

#include <ArduinoHttpClient.h> //install this library
#include <WiFiNINA.h> //changed from WiFi101.h, you might need to install NINA library //WiFi.h for esp32 boards
#include "arduino_secrets.h" //put wifi login info in second tab

// for simplifying JSON formatting:
#include <Arduino_JSON.h>

// a JSON variable for the body of your requests:
JSONVar data;

JSONVar dataIn; //change name to rx or tx?

// the content type to post data to server:
const char contentType[] = "application/json";

//WILL NOT WORK ON NETWORKS WITH CAPTIVE PORTAL LOGIN OR SOME SECURITY SETTINGS
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
///// WiFi Settings ///////
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;



char serverAddress[] = "192.168.1.92";  // your ip address (on mac, option click wifi)
int port = 8080;


WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;

int count = 0; //record of how many messages have been sent to server

void setup() {
  Serial.begin(9600);

pinMode(LED_BUILTIN, OUTPUT); //pin 16 for 18650 esp32

  if (!Serial) delay(3000);
  // get the MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  String macAddress = "";
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      macAddress += "0";
    }
    macAddress += String(mac[i], HEX);
  }

  data["uid"] = macAddress;

  Serial.println("mac address: " + macAddress); 

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

void loop() {

// digitalWrite(LED_BUILTIN, LOW);

  Serial.println("starting WebSocket client");
  client.begin();

  while (client.connected()) {
    // Serial.print("Sending: ");
    // Serial.println(count);

    // send a hello #
    // client.print("hello ");
    data["direction"] = "rx"; //relative to JSON file stored on computer
    data["messageNum"] = count;
    data["message"] = 0;
    client.beginMessage(TYPE_TEXT);

    

    client.print(JSON.stringify(data));
 
    client.endMessage();

    // increment count for next message
    count++;

    // check if a message is available to be received
    int messageSize = client.parseMessage();
    dataIn = JSON.parse(client.readString());
    Serial.println(JSON.stringify(data) + "\t" + JSON.stringify(dataIn) );
    if(JSON.stringify(dataIn["direction"]) == "\"tx\"" && JSON.stringify(dataIn["uid"]) == JSON.stringify(data["uid"])){
      if(JSON.stringify(dataIn["message"]).toInt() == 1){
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else{
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
    

    if (messageSize > 0) {
      // Serial.println("Received a message:");
      // Serial.println(JSON.stringify(dataIn));
    }

    // wait a specified number of milliseconds
    delay(100); //replace with millis? //100 is pushing the upper limit it seems
  }

  Serial.println("disconnected");
}





