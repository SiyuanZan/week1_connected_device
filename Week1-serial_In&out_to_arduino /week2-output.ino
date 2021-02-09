
/*week1 class Connected Devices and Networked Interaction
 * reference from https://github.com/tigoe/html-for-conndev/blob/main/serialport/
 * LED connected to A0
 * pushbutton connected to pinD2 and ground
 * Siyuan Zan 07/02/2021
 */

 #include <Arduino_JSON.h>

const int buttonPin=2;
int lastButtonState=HIGH;
int LastLEDValue=0;
int count=0;
int inData=0;

bool inputsChanges=false;

JSONVar outgoing;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(buttonPin,INPUT_PULLUP);
 Serial.setTimeout(10);

outgoing["LEDValue"]=0;
outgoing["button"]=0;
outgoing["count"]=0;





  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the capacity of the memory pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/v6/assistant to compute the capacity.
}

void loop() {
int buttonState = digitalRead(buttonPin);

if(Serial.available()>0){
inData=Serial.parseInt();
if(inData>=0){
   analogWrite(5,inData);
  if(abs(inData-LastLEDValue)>1){
  
   outgoing["LEDValue"]=inData;
   LastLEDValue=inData;
   inputsChanges = true;
  }

} 
}





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
   outgoing["LEDValue"]=0;
  analogWrite(5,0);


}
if(buttonState==1 && count%4==0){
  outgoing["LEDValue"]=255;
  analogWrite(5,255);
  

}

}






}
