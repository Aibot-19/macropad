#include <HID-Project.h>   // Libreria per funzioni avanzate HID

// --- Pin collegati ai pulsanti ---
const int buttonPins[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16};

// --- Stato precedente di ogni pulsante ---
bool lastButtonState[10] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

// --- Tempo per debounce ---
unsigned long lastDebounceTime[10] = {0};
const unsigned long debounceDelay = 50; // ms

void setup() {
  // Inizializza tastiera HID
  Keyboard.begin();

  // Imposta i pin come input con pull-up interno
  for (int i = 0; i < 10; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < 10; i++) {
    int reading = digitalRead(buttonPins[i]);

    // Controllo debounce
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
      lastButtonState[i] = reading;
    }

    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      // Pulsante premuto (ricorda: attivo LOW)
      if (reading == LOW) {
        performAction(i);
        // Attendi rilascio per evitare ripetizioni
        while (digitalRead(buttonPins[i]) == LOW);
        delay(100);
      }
    }
  }
}

// --- Azioni assegnate ai tasti ---
void performAction(int index) {
  switch (index) {
    case 0: // P.2 → Copia
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 1: // P.3 → Incolla
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 2: // P.4 → Taglia
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('x');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 3: // P.5 → Salva
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('s');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 4: // P.6 → Annulla
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('z');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 5: // P.7 → Nuovo file
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('n');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 6: // P.8 → Apri file
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('o');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 7: // P.9 → Seleziona tutto
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('a');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 8: // P.10 → Trova
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('f');
      delay(50);
      Keyboard.releaseAll();
      break;

    case 9: // P.16 → Screenshot (Win + Shift + S)
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      delay(100);
      Keyboard.releaseAll();
      break;
  }
}
