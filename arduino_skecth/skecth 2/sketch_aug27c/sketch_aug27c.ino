// LED pins
const int LEDRED = 10;
const int LEDGREEN = 11;
const int LEDYELLOW = 12;

void setup() {
    // Config the pins as output
    pinMode(LEDRED, OUTPUT);
    pinMode(LEDYELLOW, OUTPUT);
    pinMode(LEDGREEN, OUTPUT);
    
    // Initialize serial
    Serial.begin(9600);
    
    // Show main menu
    mainMenu();
}

void loop() {
    if (Serial.available() > 0) {
        char opt = Serial.read();
        
        switch (opt) {
            case '1':
                digitalWrite(LEDRED, HIGH);
                Serial.println("LED RED ON");
                break;
            case '2':
                digitalWrite(LEDRED, LOW);
                Serial.println("LED RED OFF");
                break;
            case '3':
                digitalWrite(LEDYELLOW, HIGH);
                Serial.println("LED YELLOW ON");
                break;
            case '4':
                digitalWrite(LEDYELLOW, LOW);
                Serial.println("LED YELLOW OFF");
                break;
            case '5':
                digitalWrite(LEDGREEN, HIGH);
                Serial.println("LED GREEN ON");
                break;
            case '6':
                digitalWrite(LEDGREEN, LOW);
                Serial.println("LED GREEN OFF");
                break;
            case '7':
                digitalWrite(LEDRED, HIGH);
                digitalWrite(LEDGREEN, HIGH);
                digitalWrite(LEDYELLOW, HIGH);
                Serial.println("ALL LEDS ON");
                break;
            case '8':
                digitalWrite(LEDRED, LOW);
                digitalWrite(LEDGREEN, LOW);
                digitalWrite(LEDYELLOW, LOW);
                Serial.println("ALL LEDS OFF");
                break;
            case '9':
                // Blink mode
                for(int i = 0; i < 5; i++) {  // Blink 5 times
                    digitalWrite(LEDRED, HIGH);
                    digitalWrite(LEDGREEN, HIGH);
                    digitalWrite(LEDYELLOW, HIGH);
                    delay(500);
                    digitalWrite(LEDRED, LOW);
                    digitalWrite(LEDGREEN, LOW);
                    digitalWrite(LEDYELLOW, LOW);
                    delay(500);
                }
                Serial.println("BLINK MODE TERMINATED");
                break;
            case '0':
                // Exit (turn off all)
                digitalWrite(LEDRED, LOW);
                digitalWrite(LEDGREEN, LOW);
                digitalWrite(LEDYELLOW, LOW);
                Serial.println("EXIT");
                break;
            case 'm':
                // Show main menu
                mainMenu();
                break;
            default:
                Serial.println("Invalid option. Press 'm' to show the menu.");
                break;
        }
        
        // Small delay to stabilize reading
        delay(50);
    }
}

void mainMenu() {
    Serial.println("\n::: MENU PRINCIPAL :::");
    Serial.println("[1]. Encender LED ROJO");
    Serial.println("[2]. Apagar LED ROJO");
    Serial.println("[3]. Encender LED AMARILLO");
    Serial.println("[4]. Apagar LED AMARILLO");
    Serial.println("[5]. Encender LED VERDE");
    Serial.println("[6]. Apagar LED VERDE");
    Serial.println("[7]. Encender TODOS los LEDs");
    Serial.println("[8]. Apagar TODOS los LEDs");
    Serial.println("[9]. Modo intermitente");
    Serial.println("[0]. Salir (apagar todo)");
    Serial.println("[m]. Mostrar este menú");
    Serial.print("\nSelecciona una opción: ");
}