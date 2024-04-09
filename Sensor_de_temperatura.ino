/*********
  Rui Santos
  Detalhes completos do projeto em https://randomnerdtutorials.com 
*********/

//CUIDADOS: 
//--> No módulo do sensor não é preciso adicionar um sensor mas se for o próprio senhor será necessário resistor de 4,7 Koms no 2º pino
//->> Atenção em descomentar o tipo do sensor na linha 21
// --> A instalação das bibliotecas é feita na aba rascunho em incluir biblioteca adicionado a pasta zipada  instalada em: https://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/
// --> É preciso verificar se o pino usado para se comunicar com o sensor é compatível.


// Importa as bibliotecas necessárias
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Substitua pelas credenciais da sua rede
const char* ssid = "Rute";
const char* password = "fpp@pontes";

#define DHTPIN 27    // Pino digital conectado ao sensor DHT

// Descomente o tipo de sensor em uso:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// Cria o objeto AsyncWebServer na porta 80
AsyncWebServer server(80);

String readDHTTemperature() {
  // As leituras do sensor podem ter até 2 segundos 'antigas' (é um sensor muito lento)
  // Lê a temperatura em Celsius (o padrão)
  float t = dht.readTemperature();
  // Lê a temperatura em Fahrenheit (isFahrenheit = true)
  //float t = dht.readTemperature(true);
  // Verifica se alguma leitura falhou e sai prematuramente (para tentar novamente).
  if (isnan(t)) {    
    Serial.println("Falha ao ler do sensor DHT!");
    return "--";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity() {
  // As leituras do sensor podem ter até 2 segundos 'antigas' (é um sensor muito lento)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return "--";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>Servidor DHT ESP32</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i> 
    <span class="dht-labels">Temperatura</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i> 
    <span class="dht-labels">Umidade</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Substitui o espaço reservado pelos valores do DHT
String processor(const String& var){
  //Serial.println(var);
  if(var == "TEMPERATURE"){
    return readDHTTemperature();
  }
  else if(var == "HUMIDITY"){
    return readDHTHumidity();
  }
  return String();
}

void setup(){
  // Porta serial para fins de depuração
  Serial.begin(115200);

  dht.begin();
  
  // Conecta ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi..");
  }

  // Imprime o Endereço IP Local do ESP32
  Serial.println(WiFi.localIP());

  // Rota para a página raiz /
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readDHTHumidity().c_str());
  });

  // Inicia o servidor
  server.begin();
}
 
void loop(){
  
}