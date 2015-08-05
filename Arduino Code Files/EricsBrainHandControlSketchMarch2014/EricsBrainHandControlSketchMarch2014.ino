
/*
This is my development of a DIY prosthetic arm interfaced via a hacked MindFlex headset
The output controls my InMoov robot hand/arm which is also open source and can be printed on any 3D printer
You can find lots of related videos om my channel:
Youtube : http://www.youtube.com/user/Shadow5549
Some of the code below is not applicable unless you would like to control the entire robot- I am only currently using the hand
The code can be adapted to use any variations of the different brainwave values. The information for which can be found on the github link.
You can find all the information on the InMoov robot project at http://www.inmoov.fr


Arduino MindFlex Brain Library and Instruction https://github.com/kitschpatrol/Arduino-Brain-Library

   
*/


#include <Servo.h>
#include <Brain.h>
// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

Servo servothumb;          // Define thumb servo
Servo servoindex;          // Define index servo
Servo servomajeure;
Servo servoringfinger;
Servo servopinky;
Servo servowrist;
Servo servobiceps;
Servo servorotate;
Servo servoshoulder;
Servo servoomoplat;
Servo servoneck;
Servo servorothead;

long attention; // Attention value read

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
  servoneck.attach(12);
  servorothead.attach(13);
  
} 

void loop() {     

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
	  if (attention > 50) {
          pinch();
} 
	  //}	
	else {
        alltorest();
	}

// Loop through motion tests
//alltovirtual();        // Example: alltovirtual
//delay(4000);           // Wait 4000 milliseconds (4 seconds)
//delay(8000); 
//alltorest();           // Uncomment to use this
//delay(1500);           // Uncomment to use this
//alltomax();            // Uncomment to use this
//delay(1500);           // Uncomment to use this
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
// Motion to set the servo into "virtual" 0 position: alltovirtual
void alltovirtual() {         
  servothumb.write(0);
  servoindex.write(0);
  servomajeure.write(0);
  servoringfinger.write(0);
  servopinky.write(0);
  servowrist.write(0);
  servobiceps.write(0);  
  servorotate.write(20);    //Never less then (20 degree)
  servoshoulder.write(30);  //Never less then (30 degree)
  servoomoplat.write(10);   //Never less then (10 degree)
  servoneck.write(0);
  servorothead.write(0);
}
// Motion to set the servo into "rest" position: alltorest
void alltorest() {         
   servothumb.write(0);
  servoindex.write(0);
  servomajeure.write(0);
  servoringfinger.write(0);
  servopinky.write(0);
  servowrist.write(0);
  servobiceps.write(0);     
  servorotate.write(90);    //Never less then (20 degree)
  servoshoulder.write(30);  //Never less then (30 degree)
  servoomoplat.write(10);   //Never less then (10 degree)
  servoneck.write(90);
  servorothead.write(90);
}

// Motion to set the servo into "max" position: alltomax
void alltomax() {
  servothumb.write(90);
  servoindex.write(90);
  servomajeure.write(90);
  servoringfinger.write(90);
  servopinky.write(90);
  servowrist.write(120);
  servobiceps.write(85);      //Never more then (85 or 90degree)
  servorotate.write(110);     //Never more then (110 degree)
  servoshoulder.write(130);   //Never more then (130 degree)
  servoomoplat.write(70);     //Never more then (70 degree)
  servoneck.write(180);
  servorothead.write(180);
 
}
void peace() {
  servothumb.write(90);
  servoindex.write(0);
  servomajeure.write(0);
  servoringfinger.write(90);
  servopinky.write(90);
  servowrist.write(120);
  servobiceps.write(85);      //Never more then (85 or 90degree)
  servorotate.write(110);     //Never more then (110 degree)
  servoshoulder.write(130);   //Never more then (130 degree)
  servoomoplat.write(70);     //Never more then (70 degree)
  servoneck.write(180);
  servorothead.write(180);
 
}

void rock() {
  servothumb.write(90);
  servoindex.write(0);
  servomajeure.write(90);
  servoringfinger.write(90);
  servopinky.write(0);
  servowrist.write(120);
  servobiceps.write(85);      //Never more then (85 or 90degree)
  servorotate.write(110);     //Never more then (110 degree)
  servoshoulder.write(130);   //Never more then (130 degree)
  servoomoplat.write(70);     //Never more then (70 degree)
  servoneck.write(180);
  servorothead.write(180);
 
}

void point() {
  servothumb.write(90);
  servoindex.write(0);
  servomajeure.write(90);
  servoringfinger.write(90);
  servopinky.write(90);
  servowrist.write(120);
  servobiceps.write(85);      //Never more then (85 or 90degree)
  servorotate.write(110);     //Never more then (110 degree)
  servoshoulder.write(130);   //Never more then (130 degree)
  servoomoplat.write(70);     //Never more then (70 degree)
  servoneck.write(180);
  servorothead.write(180);
 
}
void pinch() {
  servothumb.write(90);
  servoindex.write(90);
  servomajeure.write(0);
  servoringfinger.write(0);
  servopinky.write(0);
  servowrist.write(120);
  servobiceps.write(85);      //Never more then (85 or 90degree)
  servorotate.write(110);     //Never more then (110 degree)
  servoshoulder.write(130);   //Never more then (130 degree)
  servoomoplat.write(70);     //Never more then (70 degree)
  servoneck.write(180);
  servorothead.write(180);
 
}
