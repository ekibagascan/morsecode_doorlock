#include <Servo.h>
const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
                          'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
                          'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
                          'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
                          '4', '\0','3', '\0','\0','\0','2', '\0',
                          '\0','+', '\0','\0','\0','\0','1', '6',
                          '=', '/', '\0','\0','\0','(', '\0','7',
                          '\0','\0','\0','8', '\0','9', '0', '\0',
                          '\0','\0','\0','\0','\0','\0','\0','\0',
                          '\0','\0','\0','?', '_', '\0','\0','\0',
                          '\0','"', '\0','\0','.', '\0','\0','\0',
                          '\0','@', '\0','\0','\0','\0','\0','\0',
                          '-', '\0','\0','\0','\0','\0','\0','\0',
                          '\0',';', '!', '\0',')', '\0','\0','\0',
                          '\0','\0',',', '\0','\0','\0','\0',':',
                          '\0','\0','\0','\0','\0','\0','\0'
                         };


int val = 0; // A Variable to Store the Light Value from the LDR
int ctrHigh = 0;
int ctrLow = 0;
int codePtr = 0;
int dotLen;
bool Bflag;
int wpm;
 static unsigned long thisMicros = 0;
 static unsigned long lastMicros = 0;

const char passwd[] = {'A','R','D','U','I','N','O'};
Servo myservo;


void setup()
{

  myservo.attach(9);
  myservo.write(30);
  Serial.begin(9600);// Start a Serial Connection
 //Serial.print(codePtr);
  pinMode(8, OUTPUT);
}

void(* resetFunc) (void) = 0; //declare reset function at address 0

void loop()
{  
   getMorse();
   if(MorseTree[codePtr] == passwd[0]){
   getMorse();}
   if(MorseTree[codePtr] == passwd[1]){
   getMorse();}
    if(MorseTree[codePtr] == passwd[2]){
   getMorse();}
    if(MorseTree[codePtr] == passwd[3]){
   getMorse();}
    if(MorseTree[codePtr] == passwd[4]){
   getMorse();}
    if(MorseTree[codePtr] == passwd[5]){
   getMorse();}
   if(MorseTree[codePtr] == passwd[5]){
   getMorse();}
   if(MorseTree[codePtr] == passwd[6]){
  // getMorse();
   Serial.print("\n");
   Serial.print("Acces Granted");
   myservo.write(100);
   delay(4000);
  resetFunc(); //call reset
   }

}


void dis(){
 lastMicros = thisMicros;
 thisMicros = micros();
}



void getMorse(){
    wpm = (analogRead(2)*10)/1023 ;
    val = analogRead(3);
    ///////////////////
    if (wpm == 1){
      dotLen = 63;
    }
    if (wpm == 2){
      dotLen = 125;
    }
    if (wpm == 3){
      dotLen = 187;
    }
    if (wpm == 4){
      dotLen = 250;
    }
    if (wpm == 5){
      dotLen = 312;
    }
   if (wpm == 6){
      dotLen = 375;
    }
    if (wpm == 7){
      dotLen = 737;
    }

        if (wpm == 8){
      dotLen = 500;
    }
        if (wpm == 9){
      dotLen = 562;
    }
        if (wpm == 10){
      dotLen = 625;
    }
    ////////////////////
    
//  Serial.println(wpm);
  if (val >= 300)
  {
    ctrHigh++;
    ctrLow = 0;
    digitalWrite(8, HIGH);
    tone(10, 1000);
  } else {
    ctrLow++;
    if ((ctrHigh >= dotLen) && (ctrHigh < dotLen*2)) {
    //  Serial.print(".");
    Bflag =true;
      codePtr = (2*codePtr) + 1;
    } else if (ctrHigh >= dotLen * 2) {
      Bflag =true;
    //  Serial.print("-");
      codePtr = (2*codePtr) + 2;
    } else {
      if(ctrLow >= dotLen*6 && Bflag == true){
         Serial.print(" ");
     //     display.print(" ");
          Bflag = false;
      }
       if(ctrLow >= dotLen*14){
//           display.clearDisplay();
 //          display.setCursor(0,0);
      }
      if(ctrLow == dotLen*2){
        
      Serial.print(MorseTree[codePtr]);
      // display.print(MorseTree[codePtr]);
    dis();
        codePtr = 0;
      }
    }

    ctrHigh = 0;
    digitalWrite(8, LOW);
    noTone(10);
  }
  

  
}
