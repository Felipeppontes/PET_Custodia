//Projeto de acender led Remotamente via Bluetooth
//Materiais: Led - Resistor 1k - jumpers - esp32 - celular com conexão bluetooth - app: Serial bluetooth Terminal.
// Na aba Devices Selecionamos a opção (bluetooth led) que é o nosso esp32.
#include "BluetoothSerial.h" // Inclui a biblioteca BluetoothSerial para comunicação Bluetooth

BluetoothSerial SerialBT; // Cria uma instância da classe BluetoothSerial chamada SerialBT

void setup() {
  Serial.begin(115200); // Inicia a comunicação serial com uma taxa de 115200 baud
  SerialBT.begin("ESP32_BT_Test"); // Inicia o Bluetooth com o nome "ESP32_BT_Test"
  Serial.println("Dispositivo visível"); // Imprime uma mensagem no monitor serial
  pinMode(2, OUTPUT); // Configura o pino 2 como saída para o LED
}

void loop() {
  if (SerialBT.available()) {              // Verifica se há dados disponíveis para leitura via Bluetooth
    char command = SerialBT.read();             // Lê o comando recebido via Bluetooth
    if (command == '1') {                 // Se o comando recebido for '1'
      digitalWrite(2, HIGH);               // Liga o LED conectado ao pino 2
      Serial.println("Comando recebido: 1");             // Exibe o comando recebido no monitor serial
      SerialBT.println("LED ligado");             // Envia uma mensagem de confirmação ao dispositivo Bluetooth
    } else if (command == '2') {                     // Se o comando recebido for '2'
      digitalWrite(2, LOW);                     // Desliga o LED conectado ao pino 2
      Serial.println("Comando recebido: 2");         // Exibe o comando recebido no monitor serial
      SerialBT.println("LED desligado");           // Envia uma mensagem de confirmação ao dispositivo Bluetooth
    }
  }
  delay(50); // Aguarda 50 milissegundos
}

