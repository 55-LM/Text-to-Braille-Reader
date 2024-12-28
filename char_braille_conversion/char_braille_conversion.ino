// Pin definitions for solenoids
const int solenoidPins[6] = {2, 3, 4, 5, 6, 7}; // Pins for 6 Braille dots

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set solenoid pins as outputs
  for (int i = 0; i < 6; i++) {
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], LOW); // Initialize solenoids to off
  }
}

void loop() {
  // Check if there's data available from the serial connection
  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Read the character sent by Python
    Serial.println(receivedChar);     // Echo the received character (for debugging)

    // Get the Braille pattern for the received character
    int braillePattern = getBraillePattern(receivedChar);

    // Activate the corresponding solenoids
    activateBrailleDots(braillePattern);
  }
}

// Function to map characters to Braille patterns
int getBraillePattern(char c) {
  switch (c) {
    // Lowercase letters
    case 'a': return 0b000001;
    case 'b': return 0b000011;
    case 'c': return 0b000101;
    case 'd': return 0b000111;
    case 'e': return 0b000110;
    case 'f': return 0b001101;
    case 'g': return 0b001111;
    case 'h': return 0b001110;
    case 'i': return 0b001011;
    case 'j': return 0b001001;
    case 'k': return 0b010001;
    case 'l': return 0b010011;
    case 'm': return 0b010101;
    case 'n': return 0b010111;
    case 'o': return 0b010110;
    case 'p': return 0b011101;
    case 'q': return 0b011111;
    case 'r': return 0b011110;
    case 's': return 0b011011;
    case 't': return 0b011001;
    case 'u': return 0b100001;
    case 'v': return 0b100011;
    case 'w': return 0b101001;
    case 'x': return 0b100101;
    case 'y': return 0b100111;
    case 'z': return 0b100110;

    // Uppercase letters (dot-7 as uppercase indicator)
    case 'A': return 0b100000 | getBraillePattern('a');
    case 'B': return 0b100000 | getBraillePattern('b');
    case 'C': return 0b100000 | getBraillePattern('c');
    case 'D': return 0b100000 | getBraillePattern('d');
    case 'E': return 0b100000 | getBraillePattern('e');
    case 'F': return 0b100000 | getBraillePattern('f');
    case 'G': return 0b100000 | getBraillePattern('g');
    case 'H': return 0b100000 | getBraillePattern('h');
    case 'I': return 0b100000 | getBraillePattern('i');
    case 'J': return 0b100000 | getBraillePattern('j');
    case 'K': return 0b100000 | getBraillePattern('k');
    case 'L': return 0b100000 | getBraillePattern('l');
    case 'M': return 0b100000 | getBraillePattern('m');
    case 'N': return 0b100000 | getBraillePattern('n');
    case 'O': return 0b100000 | getBraillePattern('o');
    case 'P': return 0b100000 | getBraillePattern('p');
    case 'Q': return 0b100000 | getBraillePattern('q');
    case 'R': return 0b100000 | getBraillePattern('r');
    case 'S': return 0b100000 | getBraillePattern('s');
    case 'T': return 0b100000 | getBraillePattern('t');
    case 'U': return 0b100000 | getBraillePattern('u');
    case 'V': return 0b100000 | getBraillePattern('v');
    case 'W': return 0b100000 | getBraillePattern('w');
    case 'X': return 0b100000 | getBraillePattern('x');
    case 'Y': return 0b100000 | getBraillePattern('y');
    case 'Z': return 0b100000 | getBraillePattern('z');

    // Default: Unsupported character
    default: return 0b000000;
  }
}

// Function to activate solenoids based on the Braille pattern
void activateBrailleDots(int pattern) {
  for (int i = 0; i < 6; i++) {
    if (pattern & (1 << i)) {
      digitalWrite(solenoidPins[i], HIGH); // Activate solenoid
    } else {
      digitalWrite(solenoidPins[i], LOW);  // Deactivate solenoid
    }
  }
  delay(1000); // Hold the Braille display for 1 second
  clearBrailleDisplay();
}

// Function to reset all solenoids
void clearBrailleDisplay() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(solenoidPins[i], LOW);
  }
}