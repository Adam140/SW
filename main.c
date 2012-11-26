/******************************************************************************
 *
 * Copyright:
 *    (C) 2000 - 2005 Embedded Artists AB
 *
 * Description:
 *    Sample application that demonstrates how to create processes.
 *
 *****************************************************************************/

#include "pre_emptive_os/api/osapi.h"
#include "pre_emptive_os/api/general.h"
#include <printf_P.h>
#include <ea_init.h>
#include <lpc2xxx.h>
#include <consol.h>

#define PROC1_STACK_SIZE 2048
#define PROC2_STACK_SIZE 2048
#define PROC3_STACK_SIZE 2048
#define PROC4_STACK_SIZE 2048
#define PROC5_STACK_SIZE 2048
#define INIT_STACK_SIZE  400
#define BUZZ_PIN		(1<<21)

static tU8 proc1Stack[PROC1_STACK_SIZE];
static tU8 proc2Stack[PROC2_STACK_SIZE];
static tU8 proc3Stack[PROC3_STACK_SIZE];
static tU8 proc4Stack[PROC4_STACK_SIZE];
static tU8 proc5Stack[PROC5_STACK_SIZE];
static tU8 initStack[INIT_STACK_SIZE];
static tU8 pid1;
static tU8 pid2;
static tU8 pid3;
static tU8 pid4;
static tU8 pid5;

static void proc1(void* arg);
static void proc2(void* arg);
static void proc3(void* arg);
static void proc4(void* arg);
static void proc5(void* arg);
static void initProc(void* arg);

void testLedMatrix(void);
void testLcd(void);
//void testMotor(void);
void testMotor(int);
void testRGB(void);
void testI2C(void);
void testAdc(void);
void testJoy(void);

/*****************************************************************************
 *
 * Description:
 *    The first function to execute 
 *
 ****************************************************************************/
int main(void) {
	tU8 error;
	tU8 pid;

	//immediately turn off buzzer (if connected)
	IODIR0 |= 0x00000080;
	IOSET0 = 0x00000080;

	osInit();
	osCreateProcess(initProc, initStack, INIT_STACK_SIZE, &pid, 1, NULL, &error);
	osStartProcess(pid, &error);

	osStart();
	return 0;
}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void proc1(void* arg) {
	tU8 centerReleased = TRUE;
	tU8 i;
	tU32 pattern;
	tU8 error;

	for (;;) {
		printf(
				"\n\n\n\n\n*******************************************************\n");
		printf("* LPC2148 Education Board...                          *\n");
		printf("*******************************************************\n");

		//
		//Test LEDs
		//
		//    PINSEL0 &= 0x0000ffff;
		//    IODIR0  |= 0x0000ff00;
		//    IOSET0   = 0x0000fb00;
		//    IOCLR0   = 0x00000400;

		//    for(i=0; i<4; i++)
		//    {
		//      pattern = 0x00000100;
		//      while(pattern <= 0x00008000)
		//      {
		//      	IOCLR = pattern;
		//      	osSleep(20);
		//      	IOSET0 = pattern;
		//        IOCLR0 = 0x00000400; //P0.10 must always be low = LED on since motor control else will be enables
		//
		//      	pattern <<= 1;
		//      }
		//    }
		//    //flash with P0.10 (with P0.8 and P0.9 low)
		//    IOCLR0 = 0x00000700;
		//    osSleep(20);
		//    IOSET0 = 0x00000400;
		//   	osSleep(20);
		//    IOCLR0 = 0x00000400;
		//    osSleep(20);
		//    IOSET0 = 0x00000400;
		//   	osSleep(20);
		//    IOCLR0 = 0x00000400;
		//    osSleep(20);
		//    IOSET0 = 0x00000400;
		//
		//
		//    //
		//    //Test EEPROM via I2C
		//    //
		//    testI2C();


		//
		//Start the rest of the processes
		//
		//    osCreateProcess(proc2, proc2Stack, PROC2_STACK_SIZE, &pid2, 3, NULL, &error); // led matrix
		//    osStartProcess(pid2, &error);
		osCreateProcess(proc2, proc2Stack, PROC2_STACK_SIZE, &pid2, 3, NULL,
				&error); // led matrix
		osStartProcess(pid2, &error);

		osCreateProcess(proc3, proc3Stack, PROC3_STACK_SIZE, &pid3, 3, NULL,
				&error); // lcd
		osStartProcess(pid3, &error);
		//    osCreateProcess(proc4, proc4Stack, PROC4_STACK_SIZE, &pid4, 3, NULL, &error); // silnik i rgb
		//    osStartProcess(pid4, &error);
		//    osCreateProcess(proc5, proc5Stack, PROC5_STACK_SIZE, &pid5, 3, NULL, &error); // adc ?
		//    osStartProcess(pid5, &error);


		//wait for a short while
		osSleep(100);

		IOPIN &= ~0x001f0000;
		for (;;) {
			/*
			 if ((IOPIN & 0x00100000) == 0)
			 HID_SendReport(0,0,10);
			 else if ((IOPIN & 0x00080000) == 0)
			 HID_SendReport(0,-10,0);
			 else if ((IOPIN & 0x00040000) == 0)
			 HID_SendReport(0,10,0);
			 else if ((IOPIN & 0x00020000) == 0)
			 HID_SendReport(0,0,-10);
			 */
			if ((IOPIN & 0x00010000) == 0) {
				if (centerReleased == TRUE) {
					//      		HID_SendReport(1,0,0);
					centerReleased = FALSE;
				}
			} else {
				if (centerReleased == FALSE)
					//    	  HID_SendReport(0,0,0);
					centerReleased = TRUE;
			}

			osSleep(2);
		}
	}
}

static void led(int i) {
	tU32 pattern;
	//
	//Test LEDs
	//
	printf("h = %d", i);
	if (i > 8 || i < 0)
		i = 0;
	PINSEL0 &= 0x0000ffff;
	IODIR0 |= 0x0000ff00;
	IOSET0 = 0x0000fb00;
	IOCLR0 = 0x00000400;
	pattern = 256;
	int j;
	for (j = 0; j < 8; j++) {
		printf("pattern = %d", pattern);
		IOCLR = pattern;
		//      	osSleep(100);
		//          	IOSET0 = pattern;
		//            IOCLR0 = 0x00000400; //P0.10 must always be low = LED on since motor control else will be enables
		pattern <<= 1;
	}
	pattern = 256;
	for (j = 0; j < i; j++) {
		//      	IOCLR = pattern;
		//      	osSleep(100);
		IOSET0 = pattern;
		//        IOCLR0 = 0x00000400; //P0.10 must always be low = LED on since motor control else will be enables
		pattern <<= 1;
	}
	//    //flash with P0.10 (with P0.8 and P0.9 low)
	//    IOCLR0 = 0x00000700;
	//    osSleep(20);
	//    IOSET0 = 0x00000400;
	//   	osSleep(20);
	//    IOCLR0 = 0x00000400;
	//    osSleep(20);
	//    IOSET0 = 0x00000400;
	//   	osSleep(20);
	//    IOCLR0 = 0x00000400;
	//    osSleep(20);
	//    IOSET0 = 0x00000400;

}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void proc2(void* arg) {
	//	testJoy();

	tU32 oldIOPIN, tmp;

	/* read input from joystick */
	IODIR &= ~0x001f0000;
	messageOnLCD("Joystick works!", TRUE);
	/* joystick support */
	tU32 oldMove;
	int i = 0, j = 0, h = 0;
	for (;;) {
		//		printf("IOPIN = %d",(IOPIN));
		//		printf("\t");
		oldIOPIN = IOPIN;
		osSleep(10);
		if (IOPIN == 1589624063) {
			printf("work");

		}
		tmp = (oldIOPIN & ~IOPIN);// & 0x001f0000;
		printf("tmp = %d", tmp);
		printf("\n");
		//	    if( oldMove != tmp)
		//	    	oldMove = tmp;`
		//	    if(tmp != 0x00000000) {
		//	      if(tmp == 0x00020000) {
		//	    	  messageOnLCD("Gora",TRUE);
		//	      }
		//	      else if(tmp == 0x00040000) messageOnLCD("Prawo",TRUE);
		//	      else if(tmp == 0x00100000)
		//	    	  {
		//	    	  messageOnLCD("Dol",TRUE);
		//	    	  }
		//	      else if(tmp == 0x00080000) messageOnLCD("Lewo",TRUE);
		//	      else if(tmp == 0x00010000) messageOnLCD("Center",TRUE);
		//	    }
		//	    if(tmp != 0) {
		if (tmp == 131072)
		{
			messageOnLCD("up", TRUE);

			IODIR0	|=	BUZZ_PIN;		//Select the Buzzer pin as Output
			IOPIN0	&= ~(BUZZ_PIN);		//Clear the Buzzer pin

		    while(1)
			{
				IOPIN0 |= BUZZ_PIN;		//Set the Buzzer pin High
				osSleep(25);
				//_DelayMs(250);	  		//A Delay
				IOPIN0 &= ~BUZZ_PIN;	//Set the Buzzer pin Low
				//_DelayMs(250);	       	//A Delay
				osSleep(25);
		    }
		}

		else if (tmp == 262144) {
			messageOnLCD("right", TRUE);
			h--;
			led(h);
		} else if (tmp == 16384) {
			messageOnLCD("button", TRUE);

		} else if (tmp == 524288) {
			messageOnLCD("left", TRUE);
			h++;
			led(h);
		} else if (tmp == 65536) {
			messageOnLCD("Center", TRUE);
			testMotor(0);

		} else if (tmp == 1048576)
			messageOnLCD("down", TRUE);
		//	  }
		//	  else
		//	  {
		//		  messageOnLCD("NIC",TRUE);
		//	  }
	}
	osDeleteProcess();

}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void proc3(void* arg) {
	//testLcd();
	testLedMatrix();

}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void proc4(void* arg) {
	for (;;) {
		testRGB();
		//		testMotor();
	}
}

/*****************************************************************************
 *
 * Description:
 *    A process entry function 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void proc5(void* arg) {
	testAdc();
}

/*****************************************************************************
 *
 * Description:
 *    The entry function for the initialization process. 
 *
 * Params:
 *    [in] arg - This parameter is not used in this application. 
 *
 ****************************************************************************/
static void initProc(void* arg) {
	tU8 error;

	eaInit();
	osCreateProcess(proc1, proc1Stack, PROC1_STACK_SIZE, &pid1, 3, NULL, &error);
	osStartProcess(pid1, &error);

	osDeleteProcess();
}

/*****************************************************************************
 *
 * Description:
 *    The timer tick entry function that is called once every timer tick
 *    interrupt in the RTOS. Observe that any processing in this
 *    function must be kept as short as possible since this function
 *    execute in interrupt context.
 *
 * Params:
 *    [in] elapsedTime - The number of elapsed milliseconds since last call.
 *
 ****************************************************************************/
void appTick(tU32 elapsedTime) {
}
