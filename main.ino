// -- CONSTANTES -- //

// Pinos dos componentes
const int BTN_PIN = 1;
const int BUZZER_PIN = 3;
const int LED_PIN = 5;
const int ECHO_PIN = 6;
const int TRIG_PIN = 7;

// Valores
const int INTRUD_TONE = 1000;

// -- FUNCOES --
void setup() {
  pinMode(BTN_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT); 
}

// Pisca o led e o som do alarme ate que o botao seja pressionado
void tocaAlarme(int freq) {
  do {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, freq);
    delay(100);
    
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    delay(100);
  } while (!digitalRead(BTN_PIN));
}

// Loop (funcao principal)
void loop() {
  // Disparo do sensor ultrassonico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Com base na duracao, calcula a distancia do objeto
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  
  // Se distancia < 30cm e > 0 (evitar erros)
  if (distance < 30 && distance > 0) {
    tocaAlarme(INTRUD_TONE);
  }
  
  // Delay no loop para evitar bugs no sensor e evitar disparar novamente
  delay(2000);
}