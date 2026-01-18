const int solenoidPins[30] = {
  2, 3, 4, 5, 6, 7,
  8, 9, 10, 11, 12, 13,
  14, 15, 16, 17, 18, 19,
  20, 21, 22, 23, 24, 25,
  26, 27, 28, 29, 30, 31
};

const int buttonPin = 32;

char msg[256];
int msgLen = 0;
int offsetIndex = 0;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 35;

int getBraillePattern(char c) {
  if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
  switch (c) {
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
    case ' ': return 0b000000;
    default: return 0b000000;
  }
}

void showWindow() {
  for (int cell = 0; cell < 5; cell++) {
    int pattern = 0;
    int idx = offsetIndex + cell;
    if (idx >= 0 && idx < msgLen) pattern = getBraillePattern(msg[idx]);
    for (int dot = 0; dot < 6; dot++) {
      int pinIndex = cell * 6 + dot;
      digitalWrite(solenoidPins[pinIndex], (pattern & (1 << dot)) ? HIGH : LOW);
    }
  }
}

void clearDisplay() {
  for (int i = 0; i < 30; i++) digitalWrite(solenoidPins[i], LOW);
}

void resetMessage() {
  msgLen = 0;
  offsetIndex = 0;
  clearDisplay();
}

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 30; i++) {
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], LOW);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  resetMessage();
}

void handleButton() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        offsetIndex += 5;
        if (offsetIndex >= msgLen) {
          clearDisplay();
        } else {
          showWindow();
        }
      }
    }
  }

  lastButtonState = reading;
}

void handleSerial() {
  static int writePos = 0;

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\r') continue;

    if (c == '\n') {
      msg[writePos] = '\0';
      msgLen = writePos;
      offsetIndex = 0;
      writePos = 0;
      if (msgLen > 0) showWindow(); else clearDisplay();
      return;
    }

    if (writePos < (int)sizeof(msg) - 1) {
      msg[writePos++] = c;
    }
  }
}

void loop() {
  handleSerial();
  handleButton();
}
