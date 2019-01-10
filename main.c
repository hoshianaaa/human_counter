

#include <I2CLiquidCrystal.h>

#include <mglcd.h>

I2CLiquidCrystal lcd(63, (bool)true);





#define echoPin 2 // Echo Pin

#define trigPin 3 // Trigger Pin



const int buttonPin = 9;

const int sensorLED = 5;

const int mode1LED = 12;

const int mode0LED = 11;



int sensorFlag = 0;

int buttonFlag = 0;

int mojiFlag = 0;

int mode = 0;

int Count =0;

long int PRESENT_SECOND  = 0;

long int NOW_SECOND = 0;

 

double Duration = 0; //受信した間隔

double Distance = 0; //距離

void setup() {

Serial.begin( 9600 );

pinMode( echoPin, INPUT );

pinMode( trigPin, OUTPUT );

pinMode( sensorLED, OUTPUT);

pinMode( mode0LED, OUTPUT);

pinMode( mode1LED, OUTPUT);



lcd.begin(16, 2);

pinMode(buttonPin, INPUT_PULLUP);//Inputモードでプルアップ

}

void loop() {


  

  NOW_SECOND = millis();


  if((digitalRead(buttonPin) == LOW)&&(buttonFlag == 0)&&(mode == 0)){buttonFlag = 1;mode = 1;}
  if((digitalRead(buttonPin) == LOW)&&(buttonFlag == 0)&&(mode == 1)){buttonFlag = 1;mode = 2;}
  if((digitalRead(buttonPin) == LOW)&&(buttonFlag == 0)&&(mode == 2)){buttonFlag = 1;mode = 0;}

  if((digitalRead(buttonPin) == HIGH)&&(buttonFlag == 1))buttonFlag = 0;

  

  digitalWrite(trigPin, LOW); 

  delayMicroseconds(2); 

  digitalWrite( trigPin, HIGH ); //超音波を出力

  delayMicroseconds( 10 ); //

  digitalWrite( trigPin, LOW );

  Duration = pulseIn( echoPin, HIGH ); //センサからの入力

  if ((Duration > 0)&& ((NOW_SECOND - PRESENT_SECOND)>500)) {

    Duration = Duration/2; //往復距離を半分にする

    Distance = Duration*340*100/1000000; // 音速を340m/sに設定

    Serial.print("Distance:");

    Serial.print(Distance);

    Serial.println(" cm");

    PRESENT_SECOND = millis();
  }


    if((Distance < 50) && (sensorFlag == 0)){sensorFlag = 1;Count++;digitalWrite(sensorLED,HIGH);}

    if((Distance >= 50) && (sensorFlag == 1)){sensorFlag = 0;digitalWrite(sensorLED,LOW);}



    if(mode == 0){

      digitalWrite(mode0LED,HIGH);

      digitalWrite(mode1LED,LOW);

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("Distance:");

      //delay(50);

      lcd.setCursor(4, 1);

      lcd.print(Distance);

      lcd.print(" cm");

      delay(100);

      //lcd.clear();

      //delay(100);

    }

    if(mode == 1){

      digitalWrite(mode0LED,LOW);

      digitalWrite(mode1LED,HIGH);

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("Count:");

      lcd.setCursor(4, 1);

      lcd.print(Count);

      delay(50);

    }
    if(mode == 2){

      digitalWrite(mode0LED,HIGH);

      digitalWrite(mode1LED,HIGH);

      lcd.clear();

      lcd.setCursor(0, 0);

      if(Count<30)lcd.print("()");
      
      else if((Count < 60)&&(mojiFlag == 0)){lcd.print(" () ");mojiFlag = !mojiFlag;}
      else if((Count < 60)&&(mojiFlag == 1)){lcd.print("() ");mojiFlag = !mojiFlag;}
      
      else if((Count < 90)&&(mojiFlag == 0)){lcd.print("  (--)");mojiFlag = 1;}
      else if((Count < 90)&&(mojiFlag == 1)){lcd.print(" z(--)");mojiFlag = 2;}
      else if((Count < 90)&&(mojiFlag == 2)){lcd.print("Zz(--)");mojiFlag = 0;}
      
      else if((Count < 120)&&(mojiFlag == 0)){lcd.print(" ('')****");mojiFlag = 1;}
      else if((Count < 120)&&(mojiFlag == 1)){lcd.print("('')****");mojiFlag = 2;}
      else if((Count < 120)&&(mojiFlag == 2)){lcd.print("'')****");mojiFlag = 3;}
      else if((Count < 120)&&(mojiFlag == 3)){lcd.print("')****");mojiFlag = 4;}
      else if((Count < 120)&&(mojiFlag == 4)){lcd.print(")****");mojiFlag = 5;}
      else if((Count < 120)&&(mojiFlag == 5)){lcd.print("****");mojiFlag = 6;}  
      else if((Count < 120)&&(mojiFlag == 6)){lcd.print("***");mojiFlag = 7;}
      else if((Count < 120)&&(mojiFlag == 7)){lcd.print("**");mojiFlag = 8;}
      else if((Count < 120)&&(mojiFlag == 8)){lcd.print("*");mojiFlag = 9;} 
      else if((Count < 120)&&(mojiFlag == 9)){lcd.print("");mojiFlag = 10;}
      else if((Count < 120)&&(mojiFlag == 10)){lcd.print("");mojiFlag = 11;}
      else if((Count < 120)&&(mojiFlag == 11)){lcd.print("            (");mojiFlag = 12;}  
      else if((Count < 120)&&(mojiFlag == 12)){lcd.print("           ('");mojiFlag = 13;}
      else if((Count < 120)&&(mojiFlag == 13)){lcd.print("          (''");mojiFlag = 14;}
      else if((Count < 120)&&(mojiFlag == 14)){lcd.print("         ('')");mojiFlag = 15;}  
      else if((Count < 120)&&(mojiFlag == 15)){lcd.print("        ('')*");mojiFlag = 16;}
      else if((Count < 120)&&(mojiFlag == 16)){lcd.print("       ('')**");mojiFlag = 17;}
      else if((Count < 120)&&(mojiFlag == 17)){lcd.print("      ('')***");mojiFlag = 18;}    
      else if((Count < 120)&&(mojiFlag == 18)){lcd.print("     ('')****");mojiFlag = 19;}
      else if((Count < 120)&&(mojiFlag == 19)){lcd.print("    ('')**** ");mojiFlag = 20;}
      else if((Count < 120)&&(mojiFlag == 20)){lcd.print("   ('')****  ");mojiFlag = 0;}   
      
      else {lcd.print("   (**)XXX  ");lcd.setCursor(4, 1);lcd.print("  dead ");}
      
  

      lcd.setCursor(4, 1);


      delay(50);

    }


  delay(100);

}

