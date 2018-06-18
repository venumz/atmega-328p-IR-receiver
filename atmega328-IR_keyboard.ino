/*
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected in series with a 100Ohm resistor to pin3
 * 
 * Verify UsbKeyboard/usbconfig.h :
 *  #define USB_CFG_IOPORTNAME      D
 *  #define USB_CFG_DMINUS_BIT      4
 *  #define USB_CFG_PULLUP_IOPORTNAME   D 
 *  
 * D+ connects to pin D2
 * D- connects to pin D4
 * 
 * We are going to use the new IRLIB2 library as this one works way better:
 * https://github.com/cyborg5/IRLib2
 */

#include "UsbKeyboard.h" 
#include <IRLibDecodeBase.h>  //We need both the coding and
#include <IRLibSendBase.h>    // sending base classes
#include <IRLib_P01_NEC.h>    //Lowest numbered protocol 1st
#include <IRLib_P02_Sony.h>   // Include only protocols you want
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P07_NECx.h>
#include <IRLibCombo.h>       // After all protocols, include this
// All of the above automatically creates a universal decoder
// class called "IRdecode" and a universal sender class "IRsend"
// containing only the protocols you want.
// Now declare instances of the decoder and the sender.

int RECV_PIN=8;

// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
IRdecode results;
#include <IRLibRecv.h>
IRrecv myReceiver(RECV_PIN); //pin number for the receiver
bool debugSerial=0;
int lastStroke=0;

void setup() {
  if(debugSerial){
  Serial.begin(9600);
  Serial.println("Starting Receiver");
  }
 pinMode(RECV_PIN, INPUT);
 digitalWrite(RECV_PIN, HIGH); 
  
 // Disable timer0 as it can interfere with USB timing 
 // millis and delay won't work with this timer down, but delayMicrosencods() will
TIMSK0 &= !(1<<TOIE0); // Disabling timer0 
// Clear interrupts while performing time-critical operations
cli(); 
// Force re-enumeration so the host will detect us
usbDeviceDisconnect();
delayMs(250);
usbDeviceConnect();
usbInit();
// Set interrupts again
sei();
myReceiver.enableIRIn(); // Start the receiver

}
void loop() {
  // put your main code here, to run repeatedly:
UsbKeyboard.update();
if(myReceiver.getResults()){
  results.decode();
  if(debugSerial)
  Serial.println(results.value);



if(results.value==7525 || results.value==5477) { // Volume up -
    UsbKeyboard.sendKeyStroke(KEY_VOL_UP);
    } else if(results.value==5475 || results.value==7523) { // Volume down -
    UsbKeyboard.sendKeyStroke(KEY_VOL_DOWN);
    } else if(results.value==5454 || results.value==7502) { // arrow left
    if(lastStroke!=results.value) // we don't want for this button to hit twice
    UsbKeyboard.sendKeyStroke(KEY_ARROW_LEFT,MOD_SHIFT_LEFT);
    } else if(results.value==5456 || results.value==7504) { // arrow right
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_RIGHT,MOD_SHIFT_LEFT);
    } else if(results.value==5453 || results.value==7501) { // arrow up
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_UP,MOD_SHIFT_LEFT);
    } else if(results.value==5457 || results.value==7505) { // arrow down
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_ARROW_DOWN,MOD_SHIFT_LEFT);
    } else if(results.value==5464 || results.value==7512) { // mute
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_MUTE);
    } else if(results.value==7503 || results.value==5455 || results.value==7550 || results.value==5502) { // space (OK)
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_SPACE);
    } else if(results.value==7490 || results.value==5442) { // Full screen (f)
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_F);
    } else if(results.value==7547 || results.value==5499) { // Play
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_SPACE);
    } else if(results.value==7548 || results.value==5500) { // Stop
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_STOP);
    } else if(results.value==7526 || results.value==5478 || results.value==7551 || results.value==5503) { // Next
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_NEXT);
    } else if(results.value==7524 || results.value==5476 || results.value==5501 || results.value==7549) { // Prev
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_PREV);
    } else if(results.value==5452 || results.value==7500) { // 0
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_0);
    } else if(results.value==7491 || results.value==5443) { // 1
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_1);
    } else if(results.value==7492 || results.value==5444) { // 2
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_2);
    } else if(results.value==7493 || results.value==5445) { // 3
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_3);
    } else if(results.value==7494 || results.value==5446) { // 4
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_4);
    } else if(results.value==7495 || results.value==5447) { // 5
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_5);
    } else if(results.value==5448 || results.value==7496) { // 6
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_6);
    } else if(results.value==7497 || results.value==5449) { // 7
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_7);
    } else if(results.value==7498 || results.value==5450) { // 8
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_8);
    } else if(results.value==7499 || results.value==5451) { // 9
    if(lastStroke!=results.value)
    UsbKeyboard.sendKeyStroke(KEY_9);
    } 
    lastStroke=results.value;
 
  myReceiver.enableIRIn(); // Re-enable receiver
}
}

void delayMs(unsigned int ms) {
  for( int i=0; i<ms; i++ ) {
    delayMicroseconds(1000);
}
}
