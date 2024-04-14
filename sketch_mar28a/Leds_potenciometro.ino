// PROJETO 1 - APRESENTAÇÃO CUSTÓDIA

// Materiais:  [Leds - Potenciômetro - jumpers - resistores de 1k - protoboard -esp32]
// Atenção: Verificar quais saidas operam em sinal analógico, para uso do potenciômetro

int vermelho = 2;
int amarelo = 4;
int verde = 5;

void setup() //Informa ao ESP32 os parâmetros iniciais no qual ele vai trabalhar
{
  Serial.begin(9600); //Serve para habilitar os dados fornecido no monitor serial.
  // Declarando quais pinos vamos usar e que são pinos de saida de dados.
  pinMode(amarelo,OUTPUT);
  pinMode(verde,OUTPUT);
  pinMode(vermelho ,OUTPUT);
}
void loop()// É a função de ciclo do ESP32, destinada para as ações desejadas.
{
  Serial.println(analogRead(15)); // função para mostrar no monitor serial os dados enviados pelo potenciômetro.
  
  if (analogRead(15) <1650){ //Se o ponteiro estiver abaixo de 40% do total -- > Acender o led verde.
    digitalWrite(verde, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(vermelho, LOW);
  }
  else if(analogRead(15) >1650 && analogRead(15) < 2450 ){ // Se o ponteiro estiver entre 40% e 60% do total -- > Acender o led Amarelo.
  	digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
    digitalWrite(vermelho, LOW);
  }
  else if(analogRead(15) > 2450 ){  // Se o ponteiro estiver acima de 60% do total -- > Acender o led vermelho.
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);    
  }
};






