
/* 
 * This code accepts serail data and encode it into Morse code,
 * light up LED in pin # 13 accordingly and display back to the
 * serial monitor.
 *
 * Author: Sudhir K
 * 09/05/2012
 *
 */


const int led = 13;
const int dd = 50;
const int dotLength = dd;
const int dahLength = 2*dd;
const int baudGap = dd;

char alpha[27][6] = {"01", "1000", "1010", "100", "0", "0010", "110", "0000", "00", "0111", //J
          "101", "0100", "11", "10", "111", "0110", "1101", "010", "000", "1", // T
          "001", "0001", "011", "1001", "1011", "1100"} ;
          
char numer[12][6] = {"01111", "00111", "00011", "00001", "00000", 
          "10000", "11000", "11100", "11110", "11111"};
          
char comma[7] = "110011";
char period[7] = "010101";
char query[7] = "001100";
char space[8] = "0000000";

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void dot() {
  digitalWrite(led, HIGH);
  delay(dotLength);
  digitalWrite(led, LOW);
  delay(baudGap);
}

void dah() {
  digitalWrite(led, HIGH);
  delay(dahLength);
  digitalWrite(led, LOW);
  delay(baudGap);
}

void spacebar1() {
  digitalWrite(led, LOW);
  delay(7*dotLength);
}


void pause() {
  digitalWrite(led, LOW);
  delay(3*dotLength);
}

void show(char* txt, char ch) {
  for (int i=0; i<strlen(txt); i++) {
    if (txt[i] == '0')
      dot();
    else
      dah();
  }
  pause();
  Serial.print(ch);
}

void encode(char ch, int mode) {
  switch(mode) {
    case 1:
    show(numer[int(ch)-48], ch);
    break;
    
    case 2:
    show(alpha[int(ch)-65], ch);
    break;
    
    case 3:
    show(period, ch);
    break;
    
    case 4:
    show(comma, ch);
    break;
    
    case 5:
    show(query, ch);
    break;
    
    case 6:
    show(space, ch);
    break;
  }
}

void loop() {
  while (Serial.available() > 0) {
    char ch = toupper(Serial.read());
    
    if (int(ch) >47 && int(ch) < 58) {
      encode(ch, 1);
    }
    else if (int(ch) > 64 && int(ch) < 91) {
      encode(ch, 2);
    }
    else if (ch == '.') {
      encode(ch, 3);
    }
    else if (ch == ',') {
      encode(ch, 4);
    }
    else if (ch == '?') {
      encode(ch, 5);
    }
    else if (ch == ' ') {
      encode(ch, 6);
    }
    else {
      Serial.print(ch);
      continue;
    }     
  }
}
