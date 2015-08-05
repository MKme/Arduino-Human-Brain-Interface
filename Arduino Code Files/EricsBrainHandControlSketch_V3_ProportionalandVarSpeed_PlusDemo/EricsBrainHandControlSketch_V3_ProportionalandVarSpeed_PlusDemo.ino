
/*
This is my development of a DIY prosthetic arm interfaced via a hacked MindFlex headset
The output controls my InMoov robot hand/arm which is also open source and can be printed on any 3D printer
You can find the details of this project on the website or forum at:
http://www.mkme.org/
Please register and comment in the Forum for any help needed.

You can find lots of related videos om my YouTube channel:
Youtube : http://www.youtube.com/user/Shadow5549

Some of the code below is not applicable unless you would like to control the entire robot- I am only currently using the hand
The code can be adapted to use any variations of the different brainwave values. The information for which can be found on the github link.
You can find all the information on the InMoov robot project at http://www.inmoov.fr
Arduino MindFlex Brain Library and Instruction https://github.com/kitschpatrol/Arduino-Brain-Library
-------------------------------------------------------------------------

V2 April 27 2014- Added varSpeed and proportional Output for pinch motion only as a test 
Should allow pinch motion to be directly proportional to attention value

V3 April 28 2014- Added Toggle Demo Mode (aka Roam) which will cycle through a demo when the button is toggled
Then return to brain interface when toggled again.
*/


//#include <Servo.h>
#include <Brain.h>
// Set up the brain parser, pass it the hardware serial object you want to listen on.
#include <VarSpeedServo.h>
Brain brain(Serial);

VarSpeedServo servothumb;          // Define thumb servo
VarSpeedServo servoindex;          // Define index servo
VarSpeedServo servomajeure;
VarSpeedServo servoringfinger;
VarSpeedServo servopinky;
VarSpeedServo servowrist;
VarSpeedServo servobiceps;
VarSpeedServo servorotate;
VarSpeedServo servoshoulder;
VarSpeedServo servoomoplat;
VarSpeedServo servoneck;
VarSpeedServo servorothead;
#define LED 13 //Will show the state of the demo mode
const int buttonPin = 12; //button for toggling demo mode

long attention; // Attention value read
 long val;
  long val2;
 int roam = 0;
 int buttonState = 0; 
void setup() { 
  // Start the hardware serial.
  Serial.begin(9600);
  servothumb.attach(2);  // Set thumb servo to digital pin 2
  servoindex.attach(3);  // Set index servo to digital pin 3
  servomajeure.attach(4);
  servoringfinger.attach(5);
  servopinky.attach(6);
  servowrist.attach(7);
  servobiceps.attach(8);
  servorotate.attach(9);
  servoshoulder.attach(10);
  servoomoplat.attach(11);
  //servoneck.attach(12);
  //servorothead.attach(13);
  pinMode(LED, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  long val;
  long val2;
} 

void loop() {   

buttonState = digitalRead(buttonPin);
if (buttonState == HIGH) {     
   toggleRoam(); 
  } 

if(roam == 0) {
    digitalWrite(LED, LOW);
     // Expect packets about once per second.
        // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
        // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"   
        if (brain.update()) {
        //Commented out the serial output for hraphing untill troubleshooting complete
        Serial.println(brain.readCSV());
                
                
	attention = brain.readAttention();// Retrieve Attention Value 0 - 100
        }

// Make sure we have a signal.
	//if(brain.readSignalQuality() == 0) {

// Close hand if attention value high enough
	  if (attention > 1) {
          pinch();
//} 
	  }	
	else {
        alltorest();
	}
  }
  else if(roam == 1){
    digitalWrite(LED, HIGH);
    DEMO();
  }  



}
void DEMO() {
// Loop through motion tests
//alltovirtual();        // Example: alltovirtual
//delay(4000);           // Wait 4000 milliseconds (4 seconds)
//delay(8000); 
alltorest();           // Uncomment to use this
delay(1500);           // Uncomment to use this
alltomax();            // Uncomment to use this
delay(1500);           // Uncomment to use this
//peace();           // Uncomment to use this
//delay(1500);
//alltorest();
//delay(2000);// Uncomment to use this
//rock();           // Uncomment to use this
//delay(1500); 
//alltorest();
//delay(1000);// Uncomment to use this
//point();           // Uncomment to use this
//delay(1500);  
//alltorest();
//delay(1500);// Uncomment to use this
//pinch();           // Uncomment to use this
//delay(1500);// Uncomment to use this 
}
void toggleRoam(){
  if(roam == 0){
    roam = 1;
  }
  else{
    roam = 0;
  }
}

// Motion to set the servo into "virtual" 0 position: alltovirtual
void alltovirtual() {         
  servothumb.slowmove(0,75);
  servoindex.slowmove(0,75);
  servomajeure.slowmove(0,60);
  servoringfinger.slowmove(0,75);
  servopinky.slowmove(0,75);
  servowrist.slowmove(0,75);
  servobiceps.slowmove(0,75);  
  servorotate.slowmove(20,75);    //Never less then (20 degree)
  servoshoulder.slowmove(30,75);  //Never less then (30 degree)
  servoomoplat.slowmove(10,75);   //Never less then (10 degree)
  servoneck.slowmove(0,75);
  servorothead.slowmove(0,75);
}
// Motion to set the servo into "rest" position: alltorest
void alltorest() {         
  servothumb.slowmove(15,80);//Thumb binds dont go to zero
  servoindex.slowmove(0,75);
  servomajeure.slowmove(0,75);
  servoringfinger.slowmove(0,75);
  servopinky.slowmove(0,75);
  servowrist.slowmove(0,75);
  servobiceps.slowmove(0,75);     
  servorotate.slowmove(90,75);    //Never less then (20 degree)
  servoshoulder.slowmove(30,75);  //Never less then (30 degree)
  servoomoplat.slowmove(10,75);   //Never less then (10 degree)
  servoneck.slowmove(90,75);
  servorothead.slowmove(90,75);
}



// Motion to set the servo into "max" position: alltomax
void alltomax() {
  servothumb.slowmove(95,50);
  servoindex.slowmove(90,75);
  servomajeure.slowmove(90,75);
  servoringfinger.slowmove(90,75);
  servopinky.slowmove(90,75);
  servowrist.slowmove(120,75);
  servobiceps.slowmove(85,75);      //Never more then (85 or 90degree)
  servorotate.slowmove(110,75);     //Never more then (110 degree)
  servoshoulder.slowmove(130,75);   //Never more then (130 degree)
  servoomoplat.slowmove(70,75);     //Never more then (70 degree)
  servoneck.slowmove(180,75);
  servorothead.slowmove(180,75);
 
}
void peace() {
  servothumb.slowmove(95,50);
  servoindex.slowmove(0,75);
  servomajeure.slowmove(0,60);
  servoringfinger.slowmove(90,75);
  servopinky.slowmove(90,75);
  servowrist.slowmove(120,75);
  servobiceps.slowmove(85,75);      //Never more then (85 or 90degree)
  servorotate.slowmove(110,75);     //Never more then (110 degree)
  servoshoulder.slowmove(130,75);   //Never more then (130 degree)
  servoomoplat.slowmove(70,75);     //Never more then (70 degree)
  servoneck.slowmove(180,75);
  servorothead.slowmove(180,75);
 
}

void rock() {
  servothumb.slowmove(95,50);
  servoindex.slowmove(0,75);
  servomajeure.slowmove(80,75);
  servoringfinger.slowmove(90,75);
  servopinky.slowmove(0,75);
  servowrist.slowmove(120,75);
  servobiceps.slowmove(85,75);      //Never more then (85 or 90degree)
  servorotate.slowmove(110,75);     //Never more then (110 degree)
  servoshoulder.slowmove(130,75);   //Never more then (130 degree)
  servoomoplat.slowmove(70,75);     //Never more then (70 degree)
  servoneck.slowmove(180,75);
  servorothead.slowmove(180,75);
 
}

void point() {
  servothumb.slowmove(95,75);
  servoindex.slowmove(0,75);
  servomajeure.slowmove(80,75);
  servoringfinger.slowmove(90,75);
  servopinky.slowmove(90,75);
  servowrist.slowmove(120,75);
  servobiceps.slowmove(85,75);      //Never more then (85 or 90degree)
  servorotate.slowmove(110,75);     //Never more then (110 degree)
  servoshoulder.slowmove(130,75);   //Never more then (130 degree)
  servoomoplat.slowmove(70,75);     //Never more then (70 degree)
  servoneck.slowmove(180,75);
  servorothead.slowmove(180,75);
 
}
//Slowed down pinch a bit compared to others for testing
void pinch() {
  val=attention;
  val2=attention;
  val = map(val, 0, 100, 0, 95);
  servothumb.slowmove(val,50);
  //servothumb.slowmove(95,50);
  val2 = map(val2, 0, 100, 0, 90);
  servoindex.slowmove(val2,70);
  //servoindex.slowmove(90,70);
  servomajeure.slowmove(0,70);
  servoringfinger.slowmove(0,70);
  servopinky.slowmove(0,70);
  servowrist.slowmove(120,70);
  servobiceps.slowmove(85,70);      //Never more then (85 or 90degree)
  servorotate.slowmove(110,70);     //Never more then (110 degree)
  servoshoulder.slowmove(130,70);   //Never more then (130 degree)
  servoomoplat.slowmove(70,70);     //Never more then (70 degree)
  servoneck.slowmove(180,70);
  servorothead.slowmove(180,70);
 
}
