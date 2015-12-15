#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO.h"
using namespace exploringBB;
using namespace std;

GPIO *outGPIO, *inGPIO;           //global pointers

int activateLED(int var){
   outGPIO->streamWrite(HIGH);    //turn on the LED
   cout << "Button Pressed" << endl;
   return 0;
}

int main(){
   if(getuid()!=0){
      cout << "You must run this program as root. Exiting." << endl;
      return -1;
   }
   inGPIO = new GPIO(115);        //button
   outGPIO = new GPIO(49);        //LED
   inGPIO->setDirection(INPUT);   //button is an input
   outGPIO->setDirection(OUTPUT); //LED is an output
   outGPIO->streamOpen();         //fast write to LED
   outGPIO->streamWrite(LOW);     //turn the LED off
   inGPIO->setEdgeType(RISING);   //wait for rising edge
   cout << "You have 10 seconds to press the button:" << endl;
   inGPIO->waitForEdge(&activateLED); //pass the function
   cout << "Listening, but also doing something else..." << endl;
   usleep(10000000);              //allow 10 seconds
   outGPIO->streamWrite(LOW);     //turn off the LED after 10 seconds
   outGPIO->streamClose();        //sutdown
   return 0;
}
