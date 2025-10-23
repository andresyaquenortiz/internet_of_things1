v// Pinout
const int TRIG_PIN = 9;     // Pin al que se envía el pulso de disparo
const int ECHO_PIN = 10;    // Pin desde el que se lee la duración del eco

const int LED_VERDE_PIN = 3;    // LED verde - distancia amplia (normal)
const int LED_AMARILLO_PIN = 4; // LED amarillo - distancia intermedia
const int LED_ROJO_PIN = 5;      // LED rojo - distancia cercana (peligro)

const unsigned int MAX_DISTANCE_CM = 200; // Distancia máxima esperada en cm (ajusta según tu montaje)
const unsigned int NUM_MUESTRAS = 5;       // Número de lecturas para promediar
const unsigned int DELAY_BETWEEN_SAMPLES_MS = 50; // Retraso entre muestras

void setup() {
  // Inicializar pines
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_AMARILLO_PIN, OUTPUT);
  pinMode(LED_ROJO_PIN, OUTPUT);

  // Inicialización
  digitalWrite(LED_VERDE_PIN, LOW);
  digitalWrite(LED_AMARILLO_PIN, LOW);
  digitalWrite(LED_ROJO_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  // Leer distancia promediando varias muestras para mayor estabilidad
  unsigned long suma = 0;
  for (unsigned int i = 0; i < NUM_MUESTRAS; i++) {
    unsigned int d = leerDistanciaCM();
    suma += d;
    delay(DELAY_BETWEEN_SAMPLES_MS);
  }
  unsigned int distancia_cm = suma / NUM_MUESTRAS;

  // Lógica de alarmas basada en distancia
  // Umbrales (ajusta según tu instalación):
  // - Verde: distancias >= 60 cm
  // - Amarillo: 20 cm <= distancias < 60 cm
  // - Rojo: distancias < 20 cm
  if (distancia_cm >= 60) {
    encenderLED(LED_VERDE_PIN);
    apagarLED(LED_AMARILLO_PIN);
    apagarLED(LED_ROJO_PIN);
  } else if (distancia_cm >= 20) {
    encenderLED(LED_AMARILLO_PIN);
    apagarLED(LED_VERDE_PIN);
    apagarLED(LED_ROJO_PIN);
  } else { // distancia < 20 cm
    encenderLED(LED_ROJO_PIN);
    apagarLED(LED_VERDE_PIN);
    apagarLED(LED_AMARILLO_PIN);
  }

  // Enviar lectura para registro
  Serial.print("Distancia(cm): ");
  Serial.println(distancia_cm);

  // Pequeño retardo antes de la siguiente iteración
  delay(100);
}

// Función para medir distancia en centímetros usando HC-SR04
unsigned int leerDistanciaCM() {
  // 1. Enviar pulso de disparo de 10 us
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // 2. Medir duración del eco en microsegundos
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 20000); // timeout de 20 ms para evitar bloqueo
  if (duration == 0) {
    // No se obtuvo eco dentro del tiempo esperado
    return MAX_DISTANCE_CM;
  }

  // 3. Convertir duración a distancia en cm
  // El sonido viaja aproximadamente a 343 m/s = 0.0343 cm/µs
  // Distancia (cm) = (duration / 2) * 0.0343
  unsigned int distancia = (unsigned int)((duration / 2.0) * 0.0343);

  // Limitar a rango razonable
  if (distancia > MAX_DISTANCE_CM) distancia = MAX_DISTANCE_CM;

  return distancia;
}

// Utilidades simples de control de LEDs
void encenderLED(int pin) {
  digitalWrite(pin, HIGH);
}
void apagarLED(int pin) {
  digitalWrite(pin, LOW);
}
