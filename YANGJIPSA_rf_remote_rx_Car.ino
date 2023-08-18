#include <VirtualWire.h>
#include <AccelStepper.h>

#define NUM_BTN 8
#define rf_RX   7
#define STOP    83
#define dirR 5
#define stpR 4
#define dirL 3
#define stpL 2

AccelStepper motR = AccelStepper(1, stpR, dirR);
AccelStepper motL = AccelStepper(1, stpL, dirL);
//char* cmd[NUM_BTN] = {"UP","DN","RI","LE","HM","AA","BB","CC"};//,"DD"};
uint8_t cmd[NUM_BTN] = {85,68,82,76,72,65,66,67};//,"DD"};

const int MAX_SPD = 2000;
const int MAX_ACC = 50;
void setup()
{
    //Serial.begin(9600);  // Debugging only
    //Serial.println("Receiver");
  pinMode(dirR,OUTPUT);
  pinMode(stpR,OUTPUT);
  pinMode(dirL,OUTPUT);
  pinMode(stpL,OUTPUT);

  motR.setMaxSpeed(MAX_SPD); //얘는 200이 적절한값!
  motR.setAcceleration(MAX_ACC); //50~300사이 정도로 적당한값 찾기!
  motL.setMaxSpeed(MAX_SPD); //얘는 200이 적절한값!
  motL.setAcceleration(MAX_ACC); //50~300사이 정도로 적당한값 찾기!

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
        motR.setSpeed(MAX_SPD); 
        motR.runSpeed(); 
        motL.setSpeed(MAX_SPD); 
        motL.runSpeed(); 
        //Serial.println("Enter the code when [UP] received"); 
        //INPUT CODE TO MOVE FORWARD
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
        for(int i = MAX_SPD; i>=0; i=i-5)
        { 
          motR.setSpeed(i); //스탭모터의 방향과 속도를 설정
          motR.runSpeed(); //스탭모터 작동(고정속도) 
          motL.setSpeed(i); //스탭모터의 방향과 속도를 설정
          motL.runSpeed(); //스탭모터 작동(고정속도) 
        }
        motR.stop();
        motL.stop();
      }      
    }
    else if(*rcvMsg == cmd[1]) // down button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        motR.setSpeed(-1*MAX_SPD); 
        motR.runSpeed(); 
        motL.setSpeed(-1*MAX_SPD); 
        motL.runSpeed(); 
        //Serial.println("Enter the code when [DOWN] received"); 
        //INPUT CODE TO MOVE BAKCWARD
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
        for(int i = MAX_SPD; i>=0; i=i-5)
        { 
          motR.setSpeed(-1*i); //스탭모터의 방향과 속도를 설정
          motR.runSpeed(); //스탭모터 작동(고정속도) 
          motL.setSpeed(-1*i); //스탭모터의 방향과 속도를 설정
          motL.runSpeed(); //스탭모터 작동(고정속도) 
        }
        motR.stop();
        motL.stop();
      } 
    } 
    else if(*rcvMsg == cmd[2]) // right button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        motR.setSpeed(MAX_SPD/2); 
        motR.runSpeed(); 
        motL.setSpeed(MAX_SPD); 
        motL.runSpeed(); 
        //Serial.println("Enter the code when [RIGHT] received"); 
        //INPUT CODE TO MOVE RIGHT
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
        for(int i = MAX_SPD; i>=0; i=i-5)
        { 
          motR.setSpeed(i/2); //스탭모터의 방향과 속도를 설정
          motR.runSpeed(); //스탭모터 작동(고정속도) 
          motL.setSpeed(i); //스탭모터의 방향과 속도를 설정
          motL.runSpeed(); //스탭모터 작동(고정속도) 
        }
        motR.stop();
        motL.stop();
      }
    } 
    else if(*rcvMsg == cmd[3]) // left button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        motR.setSpeed(MAX_SPD); 
        motR.runSpeed(); 
        motL.setSpeed(MAX_SPD/2); 
        motL.runSpeed(); 
        //Serial.println("Enter the code when [LEFT] received"); 
        //INPUT CODE TO MOVE LEFT
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
        for(int i = MAX_SPD; i>=0; i=i-5)
        { 
          motR.setSpeed(i); //스탭모터의 방향과 속도를 설정
          motR.runSpeed(); //스탭모터 작동(고정속도) 
          motL.setSpeed(i/2); //스탭모터의 방향과 속도를 설정
          motL.runSpeed(); //스탭모터 작동(고정속도) 
        }
        motR.stop();
        motL.stop();
      }
    }
    else if(*rcvMsg == cmd[4]) // home button received
    {
      while(!vw_get_message(buf,&buflen))
      {
        rcvMsg = buf;
        //Serial.println("Enter the code when [HOME] received"); 
        //INPUT CODE HOME ACTION
        motR.setSpeed(-1*MAX_SPD); 
        motR.runSpeed(); 
        motL.setSpeed(MAX_SPD); 
        motL.runSpeed(); 
      }
      if(*rcvMsg == STOP)
      {
        //Serial.println("Enter the code when [STOP] received"); 
        //INPUT CODE TO STOP(IDLE)
        for(int i = MAX_SPD; i>=0; i=i-5)
        { 
          motR.setSpeed(-1*i); //스탭모터의 방향과 속도를 설정
          motR.runSpeed(); //스탭모터 작동(고정속도) 
          motL.setSpeed(i); //스탭모터의 방향과 속도를 설정
          motL.runSpeed(); //스탭모터 작동(고정속도) 
        }
        motR.stop();
        motL.stop();
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
