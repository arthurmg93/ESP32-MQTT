#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP32_RAW_PIN_ORDER

/************************* BIBLIOTECAS *************************/
#include <FS.h>
#include <FastLED.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

/************************* VARIAVEIS GERAIS DE CONTROLE (MUDE DE ACORDO COM SUA REDE E MQTT SERVER *************************/
#define NUM_LEDS 24               


/************************* VARIAVEIS DE CONTROLE (MUDE DE ACORDO COM SUA REDE E MQTT SERVER *************************/
//const char* ssid = "NET_2G98B94B";
//const char* password = "DE98B94B";

const char* mqtt_server = "SeuServidor.cloudmqtt.com";
const int mqtt_port = SuaPorta(apenas números);
const char* mqtt_user = "SeuUser";
const char* mqtt_pass = "SeuPassword";
const char* mqtt_client_name = "SuaInstancia";

/****************************************************************************/
//define your default values here, if there are different values in config.json, they are overwritten.
char mqtt_server2[40] = "SeuServidor.cloudmqtt.com";
char mqtt_port2[6]  = "SuaPorta(apenas números)";
char api_token[32] = "SuaInstancia";

//flag for saving data
bool shouldSaveConfig = true;

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setupSpiffs(){
  //clean FS, for testing
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server2, json["mqtt_server"]);
          strcpy(mqtt_port2, json["mqtt_port"]);
          strcpy(api_token, json["api_token"]);

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read
}


/************************* DECLARANDO AS INSTANCIAS *************************/
WiFiClient espClient;
//WiFiManager wifiManager;
PubSubClient client(espClient);
CRGB leds[NUM_LEDS];
const char* mqttTopicSub = "SuaInstancia";

/************************* VARIAVEIS GLOBAIS *************************/
const int ledPin = 12; //pino onde o led sera conectado


/************************* FUNCOES *************************/
/*void setup_wifi()
{
  //Conectando a uma rede WiFi
  Serial.println();
  Serial.print("Conectando...");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }

  Serial.println("");
  Serial.println("WiFi Conectado!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}*/


//Função que reconecta ao servidor MQTT
void reconectar() {
  //Repete até conectar
  while (!client.connected()) {
    Serial.println("Tentando conectar ao servidor MQTT...");
    
    //Tentativa de conectar. Se o MQTT precisa de autenticação, será chamada a função com autenticação, caso contrário, chama a sem autenticação. 
    bool conectado = strlen(mqtt_user) > 0 ?
                     client.connect(mqtt_client_name, mqtt_user, mqtt_pass) :
                     client.connect(mqtt_client_name);
    if(conectado) {
      Serial.println("Conectado!");
      //Subscreve para monitorar os comandos recebidos
      client.subscribe(mqttTopicSub, 1);
    } else {
      Serial.println("Falhou ao tentar conectar. Codigo: ");
      Serial.println(String(client.state()).c_str());
      Serial.println(" tentando novamente em 5 segundos");
      //Aguarda 5 segundos para tentar novamente
      delay(5000);
    }
  }
}

void LED_ON ()
{
  leds[0] = CRGB(248,247,237);
  leds[1] = CRGB(248,247,237);
  leds[2] = CRGB(248,247,237);
  leds[3] = CRGB(255,0,0);
  leds[4] = CRGB(248,247,237);
  leds[5] = CRGB(248,247,237);
  leds[6] = CRGB(248,247,237);
  leds[7] = CRGB(255,0,0);
  leds[8] = CRGB(248,247,237);
  leds[9] = CRGB(248,247,237);
  leds[10] = CRGB(248,247,237);
  leds[11] = CRGB(255,0,0);
  leds[12] = CRGB(248,247,237);
  leds[13] = CRGB(248,247,237);
  leds[14] = CRGB(248,247,237);
  leds[15] = CRGB(255,0,0);
  leds[16] = CRGB(248,247,237);
  leds[17] = CRGB(248,247,237);
  leds[18] = CRGB(248,247,237);
  leds[19] = CRGB(255,0,0);
  leds[20] = CRGB(248,247,237);
  leds[21] = CRGB(248,247,237);
  leds[22] = CRGB(248,247,237);
  leds[23] = CRGB(255,0,0);
  FastLED.show();
}

void LED_OFF ()
{
  leds[0] = CRGB(0,0,0);
  leds[1] = CRGB(0,0,0);
  leds[2] = CRGB(0,0,0);
  leds[3] = CRGB(0,0,0);
  leds[4] = CRGB(0,0,0);
  leds[5] = CRGB(0,0,0);
  leds[6] = CRGB(0,0,0);
  leds[7] = CRGB(0,0,0);
  leds[8] = CRGB(0,0,0);
  leds[9] = CRGB(0,0,0);
  leds[10] = CRGB(0,0,0);
  leds[11] = CRGB(0,0,0);
  leds[12] = CRGB(0,0,0);
  leds[13] = CRGB(0,0,0);
  leds[14] = CRGB(0,0,0);
  leds[15] = CRGB(0,0,0);
  leds[16] = CRGB(0,0,0);
  leds[17] = CRGB(0,0,0);
  leds[18] = CRGB(0,0,0);
  leds[19] = CRGB(0,0,0);
  leds[10] = CRGB(0,0,0);
  leds[21] = CRGB(0,0,0);
  leds[22] = CRGB(0,0,0);
  leds[23] = CRGB(0,0,0);
  FastLED.show();
}

void callback (char* topic, byte* payload, unsigned int length)
{
  Serial.print("Mensagem recebida! {");
  String newTopic = topic;
  Serial.print(topic);
  Serial.print("} ");
  payload[length] = '\0';
  String newPayload = String((char *)payload);
  int intPayload = newPayload.toInt();
  Serial.println(newPayload);
  Serial.println();
  
  String msgString = String(newPayload);
  
  Serial.println(msgString);
  if (newTopic == "SuaInstancia/SeuSubTopico")
  {
    if (msgString == "On")
    {
      LED_ON();
    }
    if (msgString == "Off")
    {
      LED_OFF();
    }
  }
}

/************************* SETUP *************************/
void setup() 
{
  Serial.begin(115200);
  //WiFi.setSleepMode(WIFI_NONE_SLEEP);
  FastLED.addLeds<WS2812B, ledPin, RGB>(leds, NUM_LEDS);

  WiFiManager wm;
  wm.setSaveConfigCallback(saveConfigCallback);
  // setup custom parameters
  // 
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server2, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port2, 6);
  WiFiManagerParameter custom_api_token("api", "api token", api_token, 32);

  //add all your parameters here
  wm.addParameter(&custom_mqtt_server);
  wm.addParameter(&custom_mqtt_port);
  wm.addParameter(&custom_api_token);
  
  //automatically connect using saved credentials if they exist
  //If connection fails it starts an access point with the specified name
  //here  "AutoConnectAP" if empty will auto generate basedcon chipid, if password is blank it will be anonymous
  //and goes into a blocking loop awaiting configuration
  if (!wm.autoConnect()) 
  {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    // if we still have not connected restart and try all over again
    ESP.restart();
    delay(5000);
  }

  // always start configportal for a little while
  wm.setConfigPortalTimeout(60);
  wm.startConfigPortal();

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  //read updated parameters
  strcpy(mqtt_server2, custom_mqtt_server.getValue());
  strcpy(mqtt_port2, custom_mqtt_port.getValue());
  strcpy(api_token, custom_api_token.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) 
  {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server2;
    json["mqtt_port"]   = mqtt_port2;
    json["api_token"]   = api_token;

    File configFile = SPIFFS.open("/config.json", FILE_WRITE);
    if (!configFile) 
    {
      Serial.println("failed to open config file for writing");
    }

    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
    shouldSaveConfig = false;
  }
  
  //PIN SETUP
  WiFi.mode(WIFI_STA);
  //setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.subscribe(mqttTopicSub, 1);
}

void loop() 
{
  if (!client.connected())
  {
    reconectar();
  }
  client.loop();
}
