//*************these two lines are libraries with prewritten code to help us connect to a MQTT broker*************//
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/*  We can store information in variables
 *  below we create some variables with information about our Wi-Fi network
 *  we also have the IP address of our mqtt server
 *  an IP address is like the postcode for your network device
 */
const char* ssid = "Replace me with the wifi name";
const char* password = "Replace me with the wifi password";
const char* mqtt_server = "Replace me with the server IP address";

/*  Here are some more variables we need:
 *  espClient   >   a reference for the Wi-Fi network
 *  client      >   a reference to our mqtt client
 *  msg         >   a reference for any messages we want to send
 *  buttonValue >   a reference for the value we read from our button
 *  teamName    >   a reference to your teams name
 */
WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
int buttonValue = 0;
String buildingName = "Arup/London/no8/";
String teamName = "yourTeamNameHere";
bool ledState = false;

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

//*************callback runs every time a message is received from the broker*************//
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String onTopic = buildingName + teamName + "/lightOn";
  String offTopic = buildingName + teamName + "/lightOff";

  if(strcmp(topic, offTopic.c_str()) == 0)
  {
    digitalWrite(4, LOW);
    Serial.println("off");
    ledState = false;
  }
  
  if(strcmp(topic, onTopic.c_str()) == 0)
  {
    digitalWrite(4, HIGH);
    Serial.println("on");
    ledState = true;
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
      // ... and resubscribe
      String SubscribeLightOnTopic = buildingName + teamName + "/lightOn";
      String SubscribeLightOffTopic = buildingName + teamName + "/lightOff";

      client.subscribe(SubscribeLightOffTopic.c_str());
      client.subscribe(SubscribeLightOnTopic.c_str());
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
  pinMode(4, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
//*************loop runs continuously forever*************//
void loop() {

  /* Here we can check if we need to reconnect */
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /* So now we are going to check what the value of the button is */
  buttonValue = digitalRead(14);

  /* If the button value is pressed lets do something */
  if (buttonValue == 1)
  {
    /*If the led is true (ie On) lets turn it Off*/
    if (ledState)
    {
      String publishTopic = buildingName + teamName + "/lightOff";
      client.publish(publishTopic.c_str(), "0");
      delay(500);
    }
    /*If the led is false (ie Off) lets turn it On*/
    else
    {
      String publishTopic = buildingName + teamName + "/lightOn";
      client.publish(publishTopic.c_str(), "1");
      delay(500);
    }
  }
  delay(1);

}
