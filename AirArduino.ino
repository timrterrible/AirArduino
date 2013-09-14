String inputString = "";
boolean stringComplete = false;
int chState[] = {0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  int i = 0;
  inputString.reserve(200);
  Serial.begin(115200);
  while (i<8) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); //Initialise everything off/closed.
    i++;
  }
  Serial.println("00000000"); //Let modconsole know we're closed and ready.
}

void loop(){
  int i = 0;
  boolean validInput = false;

  if (stringComplete) {  

    inputString.trim();
    inputString = inputString.substring(0,8);    

    while (i<8) {
      char temp;
      temp = inputString.charAt(i);
      if (temp == '1') {
        validInput = true;  
        Serial.print("1");
        digitalWrite(i, HIGH);
        chState[i] = 1;
      } 
      else if (temp == '0'){
        validInput = true;
        Serial.print("0");
        digitalWrite(i, LOW);
        chState[i] = 0;
      }
      i++;
    }  
    if (validInput)
      Serial.println();

    inputString = "";
    stringComplete = false;
    while (i<8) {
      chState[i] = 0;
      i++;
    }

  }    

}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

