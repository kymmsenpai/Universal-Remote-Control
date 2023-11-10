// Library
#include <IRremote.h>
#include <Keypad.h>
#include <ArduinoJson.h>

// I/O digital
#define LED 12
#define SET_BUTTON 11
#define ONOF_BUTTON 10

// Keypad
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(SET_BUTTON, INPUT);
  pinMode(ONOF_BUTTON, INPUT);

  // Buka file
  // File file = SD.open("data.json");
  // if (file) {
  //   // Deserialisasi data JSON
  //   DynamicJsonDocument doc(4096);
  //   deserializeJson(doc, file);
  // }
}

void loop() {
  
  // get code
  String codeDevice = getDevice();
  // String protokol = doc[codeDevice]["protokol"];

  Serial.println(codeDevice);
  // Serial.println(protokol);

  char key = keypad.getKey();
  if (key != NO_KEY){
    if (!isAlpha(key)){
      Serial.println(key);
      // int irCode = whatInput(key);
      // Serial.println(key);
      // switch (protokol) {
      //   case "NEC":
      //     irsend.sendNEC(irCode, 32);

      //   case "Sony":
      //     irsend.sendSONY(irCode, 16);

      //   case "RC6":
      //     irsend.sendRC6(irCode, 32);

      //   case "RC5":
      //     irsend.sendRC5(irCode, 16);
        
      //   default:
      //     // kode yang akan dijalankan jika x tidak sama dengan 1, 2, atau 3
      //     break;
      // }
    }
  }
}

String getDevice(){

  int stateSet = digitalRead(SET_BUTTON);
  String codeDevice = "";

  if  (stateSet == HIGH){

    for (int i = 0; i < 4; i++) {
      bool getChar = false;
      digitalWrite(LED, HIGH);

      while (getChar == false){
        char key = keypad.getKey();
        if (key != NO_KEY){
          if (isAlpha(key)){
            codeDevice += key;
            getChar = true;
          }
        }
        
        delay(200);
      }

      digitalWrite(LED, LOW);
      delay(200);
    }

    return codeDevice;
  }

  delay(200);
}

// void whatInput(String input){
//   Serial.println(input);
// }
