#include <VirtualWire.h>

#define NUM_BTN 8
#define rf_RX   2
#define STOP    83

//char* cmd[NUM_BTN] = {"UP","DN","RI","LE","HM","AA","BB","CC"};//,"DD"};
uint8_t cmd[NUM_BTN] = {85,68,82,76,72,65,66,67};//,"DD"};

void setup()
{
    Serial.begin(9600);  // Debugging only
    Serial.println("Receiver");

    vw_set_rx_pin(rf_RX);
    vw_setup(2000);  // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  uint8_t *rcvMsg;
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    rcvMsg = buf; 
    Serial.print("rcvMsg : ");
    Serial.println(*rcvMsg);

    if(*rcvMsg == cmd[0]) // up button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [UP] received"); 
        //INPUT CODE TO MOVE FORWARD
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }      
    }
    else if(*rcvMsg == cmd[1]) // down button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [DOWN] received"); 
        //INPUT CODE TO MOVE BAKCWARD
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      } 
    } 
    else if(*rcvMsg == cmd[2]) // right button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [RIGHT] received"); 
        //INPUT CODE TO MOVE RIGHT
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    } 
    else if(*rcvMsg == cmd[3]) // left button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [LEFT] received"); 
        //INPUT CODE TO MOVE LEFT
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    }
    else if(*rcvMsg == cmd[4]) // home button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [HOME] received"); 
        //INPUT CODE HOME ACTION
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    }
    else if(*rcvMsg == cmd[5]) // A button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [A Button] received"); 
        //INPUT CODE FIRST SPECIAL ACTION
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    }
    else if(*rcvMsg == cmd[6]) // B button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [B Button] received"); 
        //INPUT CODE SECOND SPECIAL ACTION
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    }
    else if(*rcvMsg == cmd[7]) // C button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [C Button] received"); 
        //INPUT CODE THIRD SPECIAL ACTION
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
      }
    }
  }  
}
