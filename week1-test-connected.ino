
/*week1 class Connected Devices and Networked Interaction
 * reference from https://github.com/tigoe/html-for-conndev/blob/main/serialport/
 * LED connected to A0
 * pushbutton connected to pinD2 and ground
 * Siyuan Zan 07/02/2021
 */

 #include <Arduino_JSON.h>

const int buttonPin=2;
int lastButtonState=HIGH;
int lastLEDValue=0;
int count=0;

bool inputsChanges=false;

JSONVar outgoing;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(buttonPin,INPUT_PULLUP);

outgoing["LEDValue"]=0;
outgoing["button"]=0;
outgoing["count"]=0;
}

void loop() {
int buttonState = digitalRead(buttonPin);

if(buttonState!=lastButtonState){
  outgoing["button"]=buttonState;
 
  lastButtonState=buttonState;
  inputsChanges = true;
  count++;
  outgoing["count"]=count;
}



if(inputsChanges){

Serial.println(outgoing);
inputsChanges=false; 

if(buttonState==1 && count%2==0){
   outgoing["LEDValue"]=255;
  analogWrite(A0,0);


}
if(buttonState==1 && count%4==0){
  outgoing["LEDValue"]=0;
  analogWrite(A0,255);
  

}

}






}
