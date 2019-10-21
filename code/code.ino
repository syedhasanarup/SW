//*************these two lines are libraries with prewritten code to help us connect to a MQTT broker*************//
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/*  We can store information in variables
 *  below we create some variables with information about our Wi-Fi network
 *  we also have the IP address of our mqtt server
 *  an IP address is like the postcode for your network device
 */
const char* ssid = "ReplaceMeWithTheWifiName";
const char* password = "ReplaceMeWithTheWifiPassword";
const char* mqtt_server = "ReplaceMeWithTheIPAddress";

/*  Here are some more variables we need:
 *  espClient   >   a reference for the Wi-Fi network
 *  client      >   a reference to our mqtt client
 *  msg         >   a reference for any messages we want to send
 *  buttonValue >   a reference for the value we read from our button
 */
WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int buttonValue = 0;
//****************************************************************************************************************//

//*************setup_wifi connects the PLC to the network and prints it's allocated IP address*************//
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//*********************************************************************************************************//

//*************callback runs everytime a message is recieved from the broker*************//
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if(topic == "lightOn")
  {
    digitalWrite(16, HIGH);
  }
  if(topic == "lightOff")
  {
    digitalWrite(16, LOW);
  }

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}
//***************************************************************************************//

//*************reconnect runs when a connection needs to be made with the broker*************//
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
      client.subscribe("lightOn");
      client.subscribe("lightOff");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//*************setup runs when the PLC starts************//
void setup() {
  pinMode(16, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//*************loop runs continuosly forever*************//
void loop() {

  /* Here we can check if we need to reconnect */
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /* So now we are going to check what the value of the button is */
  buttonValue = digitalRead(14);

  /* If the button value is 1 lets do something */
  if (buttonValue == 1)
  {
    char buf[4];
    itoa (buttonValue, buf, 10);
    client.publish("lightOn", buf);
    delay(500);
  }
  delay(1);
    //client.publish("outTopic", msg);

}