#include <VirtualWire.h>
#include <String.h>

#define NUM_BTN 8
#define btn_UP  2
#define btn_DN  3
#define btn_R   4
#define btn_L   5
#define btn_HM  6

#define btn_A   7
#define btn_B   8
#define btn_C   9
//#define btn_D   10

#define LED     11

#define rf_TX   12

char SW[NUM_BTN] = {btn_UP, btn_DN, btn_R, btn_L, btn_HM, btn_A, btn_B, btn_C};//, btn_D};
bool swFlag[NUM_BTN] = {false,};
char* cmd[NUM_BTN] = {"UP","DN","RI","LE","HM","AA","BB","CC"};//,"DD"};

void setup() {
  for (int i=0 ; i<NUM_BTN ; i++)
  {
    pinMode(SW[i], INPUT_PULLUP);
    swFlag[i] = false;
  }

  vw_set_tx_pin(rf_TX);
  vw_setup(2000);

  pinMode(LED, OUTPUT);
  delay(1000);
  digitalWrite(LED, LOW);
}

void swCheck_cmdSend(char BTN, bool *FLAG, char* CMD)
{
  if(!digitalRead(BTN)) 
  { 
    if(!(*FLAG))
    {
      sendMsg(CMD);
      *FLAG = true;
    } 
  }
  else 
  {
    if(*FLAG) 
    {
      sendMsg("ST"); 
    }
    *FLAG = false;    
  }
}
void loop() {
  for(int i=0 ; i<NUM_BTN ; i++)
    swCheck_cmdSend(SW[i], &swFlag[i], cmd[i]);
}

void sendMsg(char* message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
}
