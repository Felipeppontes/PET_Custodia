// C++ code
int botao = 2;
int led = 4;
void setup()
{
  pinMode(led,OUTPUT);
  pinMode(botao,INPUT);
}
void loop()
{
  digitalRead(botao);//Ler o pino do botão
  
  //Se a leitura do pino onde esta ligado o botão igual a 5v 
  //escreva no pino onde esta o LED 5v(ou seja, acenda o led)
  if(digitalRead(botao) == HIGH){
  digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
  }else{ // Se a leitura do botão ele não estiver apertado não o forneça 5v.
  digitalWrite(led, LOW);
  }
}
