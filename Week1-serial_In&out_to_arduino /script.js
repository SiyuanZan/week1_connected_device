

let portSelector;
let serial; // variable for the serialport object:

let powerButton;
let lastButtonState=0;

let fanSlider;




function setup(event){
  
  powerButton = document.getElementById('power');
  powerButton.addEventListener('click', setPowerState);

  fanSlider = document.getElementById('fanSpeed');
  fanSlider.addEventListener('change', setFanSpeed);

  serial = new p5.SerialPort(); // new instance of the serialport library
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback function for serialport data event
  serial.list(); // list the serial ports

  setPowerState();
  setFanSpeed();
  // setInterval(changeValue,500);


}
// function changeValue(){

//   serial.write(fanSlider.value);
//   console.log(fanSlider.value);
// }




function setFanSpeed(e) {
  // assume e is a number:
 var currentValue = e;
 // but if it's an object instead, it's because
 // the slider change event called this function. 
 // Extract the number from it:
   if (typeof e == 'object') {
     currentValue = e.target.value;
   } 
   //get the span associated with it and change its text:
   let thisSpan = document.getElementById('fanSpeedVal');
   fanSlider.value=currentValue;
   thisSpan.innerHTML = currentValue;
   serial.write(fanSlider.value);
   
 }

function setPowerState() {
  // change its value, depending on its current value:
  
    if (powerButton.value == 'on') {
      powerButton.value = 'off';
    } else {
      powerButton.value = 'on';
    }

  
  // get the span associated with it and change its text:
  let thisSpan = document.getElementById(powerButton.id + 'Val');
  thisSpan.innerHTML = "Power is " + powerButton.value;


}

function printList(portList) {
  // create a select object:
  portSelector = document.getElementById('portSelector');
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // add this port name to the select object:
    var option = document.createElement("option");
    option.text = portList[i];
    portSelector.add(option);
  }
  // set an event listener for when the port is changed:
  portSelector.addEventListener('change', openPort);
}


function openPort() {
  let item = portSelector.value;
  // if there's a port open, close it:
  if (serial.serialport != null) {
    serial.close();
  }
  // open the new port:
  serial.open(item);
}

function serialEvent() {
  var inData = serial.readLine();
  if(inData){
   var sensors=JSON.parse(inData);
   if(sensors.button !== lastButtonState){
     if(sensors.button===1){
      setPowerState(sensors.button)
     }
     lastButtonState = sensors.button;
   }
   setFanSpeed(sensors.LEDValue);

  }

}



// add a listener for the page to load:
window.addEventListener('DOMContentLoaded', setup);
