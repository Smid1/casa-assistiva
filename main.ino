const int trigPin = 7;
const int echoPin = 6;
const int buzzerPin = 3;
const int btnPin = 1;
const int LED_RED = 5;

long duration;
int distance;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void tocaAlarme() {
  do {
    digitalWrite(LED_RED, HIGH);
    tone(buzzerPin, 1000); 
    delay(100);            // Som por 100ms
  
    digitalWrite(LED_RED, LOW);
    noTone(buzzerPin);      // Silêncio por 100ms (cria o efeito de intermitência)
    delay(100);  
  } while (!digitalRead(btnPin));     
}

void loop() {
  // Disparo do sensor ultrassônico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Se a distância for menor que 30cm (e maior que 0 para evitar erros)
  if (distance < 30 && distance > 0) {
    tocaAlarme();
  } else {
    // Se estiver longe, desliga tudo
    digitalWrite(LED_RED, LOW);
    noTone(buzzerPin);
  }
  
  // Pequena pausa para estabilizar o sensor no próximo ciclo
  delay(50); 
}