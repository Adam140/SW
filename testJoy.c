/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2005 Embedded Artists AB
 *
 *****************************************************************************/


#include "../pre_emptive_os/api/osapi.h"
#include "../pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <lpc2xxx.h>

/*****************************************************************************
 *
 * Description:
 *    A process entry function
 *
 * Params:
 *    [in] arg - This parameter is not used in this application.
 *
 ****************************************************************************/
static void
testJoy(void)
{
  tU32 oldIOPIN, tmp;

  /* read input from joystick */
  IODIR &= ~0x001f0000;
  messageOnLCD("Joystick dziala! /nWYMIATAM",TRUE);
  /* joystick support */
  for(;;)
  {
    oldIOPIN = IOPIN;
    osSleep(2);

    tmp = (oldIOPIN & ~IOPIN) & 0x001f0000;
    
//    if(tmp != 0x00000000) {
//      if(tmp == 0x00020000) handleCorrectRequest(1);
//      else if(tmp == 0x00040000) handleCorrectRequest(2);
//      else if(tmp == 0x00100000) handleCorrectRequest(3);
//      else if(tmp == 0x00080000) handleCorrectRequest(4);
//      else if(tmp == 0x00010000) handleCorrectRequest(5);
//    }
  }

  osDeleteProcess();
}

//void
//messageOnLCD(char *str, tU8 important)
//{
//  char *ptr;
//  static tU8 initialized;
//
//  if(initialized == 0) {
//    initLCD();
//    initialized = 1;
//  }
//
//	lcdBacklight(TRUE);
//    osSleep(50);
//
//    //function set
//    writeLCD(0, 0x30);
//    osSleep(1);
//    writeLCD(0, 0x30);
//    delay37us();
//    writeLCD(0, 0x30);
//    delay37us();
//
//    //function set
//    writeLCD(0, 0x38);
//    delay37us();
//
//    //display off
//    writeLCD(0, 0x08);
//    delay37us();
//
//    //display clear
//    writeLCD(0, 0x01);
//    osSleep(1); //actually only 1.52 mS needed
//
//    //display control set
//    writeLCD(0, 0x06);
//    osSleep(1);
//
//    //display control set
//    writeLCD(0, 0x0c);
//    delay37us();
//
//    //cursor home
//    writeLCD(0, 0x02);
//	osSleep(1);
//
//  for(ptr = str; *ptr; ptr++)
//  {
//    if(*ptr != '\n')
//    {
//      writeLCD(1, *ptr);
//    }
//    else
//    {
//      writeLCD(0, 0x80 | 0x40); // przejscie do nowej lini
//    }
//    delay37us();
//  }
//
//    osSleep(50);
//	lcdBacklight(important);
//}

