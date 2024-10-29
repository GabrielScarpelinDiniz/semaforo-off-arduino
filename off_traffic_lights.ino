#include "Ultrasonic.h"

const int LEDS[3] = {6, 5, 4};  // LEDs: 0 -> Vermelho, 1 -> Amarelo, 2 -> Verde
Ultrasonic sensor(12, 13);         // Configura os pinos do sensor ultrassônico (Trigger, Echo)
unsigned long lastChange = 0;
unsigned long interval = 0;
int ledState = 0;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  int distance = sensor.read();
  
  // Imprime a distância medida pelo sensor ultrassônico
  Serial.println(distance);

  // Verifica a distância para acionar o LED verde se estiver abaixo de 3 cm por mais de 2 segundos
  if (distance < 10 && ledState == 3) {
    interval = 250;
  }
  // Sequência de mudança de LEDs usando millis()
  if (currentMillis - lastChange >= interval) {
    lastChange = currentMillis;
    
    switch (ledState) {
      case 0:
        Serial.println("VERMELHO LIGADO");
        digitalWrite(LEDS[0], HIGH);  // LED vermelho ligado
        digitalWrite(LEDS[1], LOW);
        digitalWrite(LEDS[2], LOW);
        interval = 6000;              // Intervalo de 6 segundos
        ledState = 1;
        break;
        
      case 1:
        digitalWrite(LEDS[0], LOW);
        digitalWrite(LEDS[1], HIGH);  // LED amarelo ligado
        digitalWrite(LEDS[2], LOW);
        interval = 2000;              // Intervalo de 2 segundos
        ledState = 2;
        break;
        
      case 2:
        digitalWrite(LEDS[0], LOW);
        digitalWrite(LEDS[1], LOW);
        digitalWrite(LEDS[2], HIGH);  // LED verde ligado
        interval = 4000;              // Intervalo de 2 segundos
        ledState = 3;
        break;

      case 3:
        digitalWrite(LEDS[0], LOW);
        digitalWrite(LEDS[1], HIGH);  // LED amarelo ligado novamente
        digitalWrite(LEDS[2], LOW);
        interval = 2000;              // Intervalo de 2 segundos
        ledState = 0;
        break;
    }
  }
}
