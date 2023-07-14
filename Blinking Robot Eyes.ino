#include "LedControl.h"

//pin 2 = DataIn
//pin 4 = CLK 
//pin 3 = CS

LedControl display=LedControl(12,10,11,1);

void setup() {
  display.shutdown(0,false); //Wakes up
  display.setIntensity(0,15); //Sets brightness
  display.clearDisplay(0);} //Clear display}

byte images[2][8] = {
                    {0x3c,0x7e,0xff,0xff,0xff,0xff,0x7e,0x3c},  //Base image
                    {0x3c,0x7e,0xff,0xff,0xff,0xff,0x7e,0x3c}}; //Configurable

//Prints image onto matrix
void printImage(void){
  for(int i=0 ; i<8 ; i++){
    display.setColumn(0,i,images[1][7-i]);}}

//Moves iris around eye
char eye_movement(char vertical, char horizontal){
  for(int i=0 ; i<8 ; i++){
    images[1][i]=images[0][i];}  
    bitWrite(images[1][4+vertical],3+horizontal,0);
    bitWrite(images[1][4+vertical],4+horizontal,0);
    bitWrite(images[1][5+vertical],3+horizontal,0);
    bitWrite(images[1][5+vertical],4+horizontal,0);
    printImage();}

//Animates blink
void eye_blink(){
  for(int i=0 ; i<4 ; i++){
    display.setColumn(0,7-i,0x00);
    display.setColumn(0,i,0x00);
    delay(20);}
  for(int i=3 ; i>=0 ; i--){
    display.setColumn(0,7-i,images[1][i]);
    display.setColumn(0,i,images[1][7-i]);
    delay(20);}}

//Squint
void eye_squint(){
  eye_movement(1,0);
}

void loop(){
eye_movement(0,0);

for(int i=0 ; i<4 ; i++){
  eye_movement(0,i);
  delay(20);
 }

eye_blink();

for(int i=3 ; i>=0 ; i--){
  eye_movement(0,i);
  delay(20);
 }

delay(1000);

eye_blink();

delay(2000);

eye_blink();

delay(1000);
}
