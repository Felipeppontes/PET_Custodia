//Projeto de acender led Remotamente via Bluetooth
//Materiais: Led - Resistor 1k - jumpers - esp32 - celular com conexão bluetooth - app: Serial bluetooth Terminal.
// Na aba Devices Selecionamos a opção (bluetooth led) que é o nosso esp32.

#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run 'make menuconfig' to and enable it
#endif

BluetoothSerial SerialBT; 

char valorRecebido;

void setup() {
  
  Serial.begin(115200);
  SerialBT.begin("bluetooth led"); // Dando o Nome da placa esp32 que estará disponível para os outros dispositívos.  
  Serial.println("Dispositivo visível");

  pinMode(13,OUTPUT);
}

void loop() {
    valorRecebido =(char)SerialBT.read();

  if(Serial.available()){
    SerialBT.write(Serial.read());

  }
  if(SerialBT.available()){

    if(valorRecebido == '1'){
      SerialBT.println("LED 1 ligado:");
      digitalWrite(13,HIGH);
    }
    if(valorRecebido == '2'){
      SerialBT.println("LED 1 desligado:");
      digitalWrite(13,LOW);
    }
  }
  delay(50);

}
