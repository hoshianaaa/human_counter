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
int mode = 0;
int Count = 0;
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
  if((digitalRead(buttonPin) == LOW)&&(buttonFlag == 0)){buttonFlag = 1;mode = !mode;}
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
  }
  delay(100);
}
