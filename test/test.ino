byte DTMF_data; // holds serial message / DTMF data;

int STQ = 50; // HIGH when a dtmf signal is available

/* parallel data comes in through these pins */
int bitOne = 30;
int bitTwo = 31;
int bitThree = 32;
int bitFour = 33;

void setup()   
{        
  /* set data pins as input */          
  pinMode(bitOne, INPUT);
  pinMode(bitTwo, INPUT);
  pinMode(bitThree, INPUT);
  pinMode(bitFour, INPUT);

  /* wait for serial connection */
  Serial.begin(9600);
}
 
void loop() 
{
  /* initialize DTMF data as 0 */
  DTMF_data = 0;

  /* read parallel input if dtmf tone is present */
  while (digitalRead(STQ) == HIGH){         // tone is present
    if (digitalRead(bitOne) == HIGH){
      DTMF_data += 1;
    }
    if (digitalRead(bitTwo) == HIGH){
      DTMF_data += 2;
    }
    if (digitalRead(bitThree) == HIGH){
      DTMF_data += 4;
    }
    if (digitalRead(bitFour) == HIGH){
      DTMF_data += 8;
    }

    /* send correct character to serial console */
    switch(DTMF_data){
      case 0: // DTMF D
        Serial.println("code detected: D\n");
        delay(300);
        break;
      case 1: // DTMF 1
        Serial.println("code detected: 1\n");
        delay(300);
        break;
      case 2: // DTMF 2
        Serial.println("code detected: 2\n");
        delay(300);
        break;
      case 3: // DTMF 3
        Serial.println("code detected: 3\n");
        delay(300);
        break;
      case 4: // DTMF 4
        Serial.println("code detected: 4\n");
        delay(300);
        break;
      case 5: // DTMF 5
        Serial.println("code detected: 5\n");
        delay(300);
        break;
      case 6: // DTMF 6
        Serial.println("code detected: 6\n");
        delay(300);
        break;
      case 7: // DTMF 7
        Serial.println("code detected: 7\n");
        delay(300);
        break;
      case 8: // DTMF 8
        Serial.println("code detected: 8\n");
        delay(300);
        break;
      case 9: // DTMF 9
        Serial.println("code detected: 9\n");
        delay(300);
        break;
    }
    DTMF_data = 0; // clear the DTMF character
  }
  Serial.flush(); // flush serial buffer
}
