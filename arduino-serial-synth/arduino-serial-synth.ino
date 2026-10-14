// Ho dovuto mettere degli asterischi al posto dei dati sensibili (secret data)
// in seguito alla pubblicazione di questo file, quindi non sarà eseguibile così com'è.

/*
  Sintetizzatore Arduino Fisico
  Controllo via Tastiera PC + Filtro Analogico
  
  Hardware:
  - Arduino Uno/Nano
  - Piezo → Pin 13 → Filtro Analogico → Output
  
  Comunicazione:
  - Riceve comandi dalla tastiera PC via seriale
  - Usa lo script Python per catturare i tasti
  
  Piezo:
  + → Pin 13 (poi attraverso filtro analogico)
  - → GND
*/

const int speakerPin = 13;

// ============ MAPPA NOTE MUSICALI ============
struct KeyNote {
  char key;
  int frequency;
  String noteName;
};

KeyNote noteMap[] = {
  {'a', 262, "Do"},   // Do (C4)
  {'s', 294, "Re"},   // Re (D4)
  {'d', 330, "Mi"},   // Mi (E4)
  {'f', 349, "Fa"},   // Fa (F4)
  {'g', 392, "Sol"},  // Sol (G4)
  {'h', 440, "La"},   // La (A4)
  {'j', 494, "Si"},   // Si (B4)
  {'k', 523, "Do5"},  // Do (C5)
  
  // Diesis
  {'w', 277, "Do#"},  // Do# (C#4)
  {'e', 311, "Re#"},  // Re# (D#4)
  {'t', 370, "Fa#"},  // Fa# (F#4)
  {'y', 415, "Sol#"}, // Sol# (G#4)
  {'u', 466, "La#"},  // La# (A#4)
  
  // Ottava bassa
  {'z', 131, "Do3"},  // Do (C3)
  {'x', 147, "Re3"},  // Re (D3)
  {'c', 165, "Mi3"},  // Mi (E3)
  {'v', 175, "Fa3"},  // Fa (F3)
  {'b', 196, "Sol3"}, // Sol (G3)
  {'n', 220, "La3"},  // La (A3)
  {'m', 247, "Si3"},  // Si (B3)
  
  // Controlli
  {' ', 0, "Stop"}    // Spazio = ferma suono
};

const int numNotes = sizeof(noteMap) / sizeof(noteMap[0]);

char currentKey = 0;
bool isPlaying = false;

// ============ SETUP ============
void setup() {
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("=================================");
  Serial.println("  SINTETIZZATORE ARDUINO");
  Serial.println("  Con Filtro Analogico");
  Serial.println("=================================");
  Serial.println();
  Serial.println("Mappa tasti:");
  Serial.println("a s d f g h j k = Do Re Mi Fa Sol La Si Do5");
  Serial.println("w e t y u = Do# Re# Fa# Sol# La#");
  Serial.println("z x c v b n m = Do3 Re3 Mi3 Fa3 Sol3 La3 Si3");
  Serial.println("SPAZIO = Stop");
  Serial.println();
  Serial.println("Usa lo script Python per inviare i tasti!");
  Serial.println("=================================");
}

// ============ LOOP PRINCIPALE ============
void loop() {
  // Controlla se arrivano comandi dalla seriale
  if (Serial.available() > 0) {
    char key = Serial.read();
    
    // Ignora caratteri di controllo
    if (key == '\n' || key == '\r') {
      return;
    }
    
    // Converti in minuscolo
    if (key >= 'A' && key <= 'Z') {
      key = key + 32; // converti in minuscolo
    }
    
    // Se è un nuovo tasto, suona
    if (key != currentKey) {
      currentKey = key;
      playNote(key);
    }
  }
}

// ============ SUONA NOTA ============
void playNote(char key) {
  // Cerca la nota nella mappa
  for (int i = 0; i < numNotes; i++) {
    if (noteMap[i].key == key) {
      
      if (noteMap[i].frequency > 0) {
        // Suona la nota continuamente
        tone(speakerPin, noteMap[i].frequency);
        isPlaying = true;
        
        Serial.print("♪ ");
        Serial.print(noteMap[i].noteName);
        Serial.print(" (");
        Serial.print(noteMap[i].frequency);
        Serial.println(" Hz)");
        
      } else {
        // Spazio = stop
        noTone(speakerPin);
        isPlaying = false;
        Serial.println("■ Stop");
      }
      
      return;
    }
  }
  
  // Tasto non riconosciuto = ferma suono
  if (isPlaying) {
    noTone(speakerPin);
    isPlaying = false;
    Serial.println("□ Tasto non riconosciuto - Stop");
  }
}
