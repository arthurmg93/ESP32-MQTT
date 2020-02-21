# ESP32-MQTT
Projeto para acionar LEDs a partir de um celular usando comunicação MQTT e um microcontrolador ESP32


O projeto consiste basicamente de usar um microcontrolador ESP32 conectado a uma rede WiFi (usando a biblioetaca WiFiManager) que irá monitorar atualizações em um Post no Dashboard MQTT. A partir dessa atualização será dado o comando para ascender ou apagar os LEDs (usando a biblioteca FastLED) de uma Fita de LED RGB.


Como serviço de MQTT foi utilizado uma conta, na versão gratuita, do Cloud MQTT. (https://www.cloudmqtt.com/)
Lá você poderá criar uma conta e ter acesso aos dados necessários para o acesso do ESP32 ao dashboard, que são:

Server = "SeuServidor.cloudmqtt.com";
Port = SuaPorta(apenas números);
User = "SeuUser";
Password = "SeuPassword";

Estes serão usados como constantes no nosso código:

const char* mqtt_server = "SeuServidor.cloudmqtt.com";
const int mqtt_port = SuaPorta(apenas números);
const char* mqtt_user = "SeuUser";
const char* mqtt_pass = "SeuPassword";

Posteriormente, será possível criar uma instância/tópico e um subtópico com os nomes que desejar.
Lembre-se de susbtituir nesta linha de código:

const char* mqtt_client_name = "SuaInstancia";



Neste código é usado uma fita com 24 LEDs RGB. Para alterar as cores ou as quantidades de LEDs acionados basta alterar o código RGB na função LED_ON(). Lembrando que será necessário fazer alterações de inclusão ou exclusão na função LED_OFF() caso haja alteração na quantidade de LEDs acionados.

Para aliementar a fita é possível utilizar as próprias saídas 5V e GND do ESP32. Caso deseje-se aumentar a quantidade de LEDs talvez seja necessário usar uma fonte externa para conseguir manter a alimentação necessária para todos os dispositivos.

O sinal de controle da fita foi conectada a porta I/O 12 do microcontrolador. Altere de acordo com as portas disponíveis na sua placa.



Esse é meu primeiro commit Git então tenham um pouco de paciência. Estou a disposição pelo GitHub.
