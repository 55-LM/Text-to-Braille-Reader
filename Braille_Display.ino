// store the code for each letter a-z in a 2D array
int braille[26][6] = {
  {1,0,0,0,0,0},  // a (first bump is raised, others are lowered)
  {1,1,0,0,0,0},  // b (first and second bumps are raised)
  {1,0,0,1,0,0},  // c (and so on...)
  {1,0,0,1,1,0},  // d
  {1,0,0,0,1,0},  // e
  {1,1,0,1,0,0},  // f
  {1,1,0,1,1,0},  // g
  {1,1,0,0,1,0},  // h
  {0,1,0,1,0,0},  // i
  {0,1,0,1,1,0},  // j
  {1,0,1,0,0,0},  // k
  {1,1,1,0,0,0},  // l
  {1,0,1,1,0,0},  // m
  {1,0,1,1,1,0},  // n
  {1,0,1,0,1,0},  // o
  {1,1,1,1,0,0},  // p
  {1,1,1,1,1,0},  // q
  {1,1,1,0,1,0},  // r
  {0,1,1,1,0,0},  // s
  {0,1,1,1,1,0},  // t
  {1,0,1,0,0,1},  // u
  {1,1,1,0,0,1},  // v
  {0,1,0,1,1,1},  // w
  {1,0,1,1,0,1},  // x
  {1,0,1,1,1,1},  // y
  {1,0,1,0,1,1},  // z
};

// array of the Arduino pins used to control the solenoids
int controlPins[6] = {2,3,4,5,6,7};

// array for the alphabet
char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

// string to convert to braille
String text = "alvi";

// variable for getting the individual letter of the text[] array
char letter;

// variable for finding the index of letter in alphabet
int index;

// length of the text[] array
int length = text.length();

void setup(){ // setup code that only runs once
  // initialize serial communication (allows printing to serial monitor)
  Serial.begin(9600);
  // set control pins as outputs
  for(int i=0; i<6; i++){
    pinMode(controlPins[i],OUTPUT);
  }
}

void loop(){  // code that loops forever
  static int i = 0;  // to keep track of the current letter index
  
  letter = text[i]; // get i'th letter of text
  // find index of this letter in the alphabet
  index = -1;  // default value to indicate not found
  for(int j = 0; j<26; j++){
    if(letter == alphabet[j]){
      index = j;
      break;
    }
  }
  if(index != -1){
    // print the letter and its index to make sure this is correct
    Serial.print(letter);
    Serial.print(" ");
    Serial.println(index);
    
    // get the corresponding row [index] from the braille array 
    // and iterate through the columns [k] to set the corresponding pins
    for(int k = 0; k<6; k++){
      digitalWrite(controlPins[k],braille[index][k]); 
    }
  }

  // increment the index for the next letter
  i++;
  if(i >= length) {
    i = 0;  // reset to the beginning of the text string
  }

  // delay before showing the next letter
  delay(1000);
}
