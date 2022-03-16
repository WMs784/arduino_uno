#ifndef _LED
#define _LED

void set_led();

#endif

#define RED A0
#define BLUE A1
#define GREEN A2

void set_led(){
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
}