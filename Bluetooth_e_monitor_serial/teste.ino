#include "BluetoothSerial.h" // Inclui a biblioteca BluetoothSerial para comunicação Bluetooth

BluetoothSerial SerialBT; // Cria uma instância da classe BluetoothSerial chamada SerialBT
  //SerialBT: É como um apelido que damos à nossa Biblioteca (Bluetooth). Quando queremos usar Bluetooth em nosso código, nos referimos a ele pelo apelido SerialBT.


void setup() {
  Serial.begin(115200); // Inicia a comunicação serial com uma taxa de 115200 baud
  SerialBT.begin("ESP32_BT_Test"); // Inicia o Bluetooth com o nome "ESP32_BT_Test"
  Serial.println("Dispositivo visível"); // Imprime uma mensagem no monitor serial
}

void loop() {
  if (SerialBT.available()) { // Verifica se há dados disponíveis para leitura via Bluetooth
    char command = SerialBT.read(); // Lê o comando recebido via Bluetooth
    Serial.print("Comando recebido: "); // Imprime uma mensagem no monitor serial
    Serial.println(command); // Exibe o comando recebido no monitor serial
    delay(50); // Aguarda um curto período de tempo para evitar a repetição da mensagem
  }
}

