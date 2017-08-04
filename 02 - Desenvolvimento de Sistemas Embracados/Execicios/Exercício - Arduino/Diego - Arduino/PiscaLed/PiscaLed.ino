
#define pedestreVerde 11
#define pedestreVermelho 10
#define carroVerde 9
#define carroAmarelo 8
#define carroVermelho 7

void interrupcao();
void pedestre();
void carro();

int pedestreChamou = 0;

void setup() {
  // put your setup code here, to run once:
  
  for(int x = 11; x >= 7; x--){
     pinMode(x, OUTPUT);
  }
  
  pinMode(2, INPUT);
  attachInterrupt(0, interrupcao, RISING);//(PINO, FUNÇÂO, STATUS DO PINO)Interrupções externas 
  
}

void loop() {

  carro();

  if(pedestreChamou == 1){

    pedestre();
    
    pedestreChamou = 0;
  }

}

void interrupcao(){
  pedestreChamou = 1;
  //pedestre();
}

void pedestre(){

  if(digitalRead(carroVerde)){
    digitalWrite(carroVerde, LOW);
    digitalWrite(carroAmarelo, HIGH);
    delay(1000);
    digitalWrite(carroAmarelo, LOW);
    digitalWrite(carroVermelho, HIGH);
  }else{
    if(digitalRead(carroAmarelo)){
      digitalWrite(carroAmarelo, LOW);
      digitalWrite(carroVermelho, HIGH);      
    }
  }
  
  digitalWrite(pedestreVermelho, LOW);
  digitalWrite(pedestreVerde, HIGH);
  delay(5000);
  digitalWrite(pedestreVerde, LOW); 

  for(int i = 1; i <= 5; i++){
    if(digitalRead(pedestreVermelho)){
      digitalWrite(pedestreVermelho, LOW);
    }else{
      digitalWrite(pedestreVermelho, HIGH);
    }

    delay(500);
  }
  
  digitalWrite(pedestreVermelho, HIGH);
}

void carro(){
  
  digitalWrite(carroVermelho, LOW);
  digitalWrite(pedestreVermelho, HIGH);
  
  digitalWrite(carroVerde, HIGH);
  delay(5000);
  digitalWrite(carroVerde, LOW);

  for(int i = 1; i <= 5; i++){
    if(digitalRead(carroAmarelo)){
      digitalWrite(carroAmarelo, LOW);
    }else{
      digitalWrite(carroAmarelo, HIGH);
    }

    delay(500);
  }

  digitalWrite(carroAmarelo, LOW);

  digitalWrite(carroVermelho, HIGH);
  
  delay(5000);


  
}





