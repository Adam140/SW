/******************************************************************************
 *
 * Copyright:
 *    (C) 2006 Embedded Artists AB
 *
 * File:
 *    key.h
 *
 * Description:
 *    Expose public functions and defines related to joystick key.
 *
 *****************************************************************************/
#ifndef _KEY_H_
#define _KEY_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "../pre_emptive_os/api/general.h"


/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/
#define KEY_NOTHING 0x00
#define KEY_UP      0x01
#define KEY_RIGHT   0x02
#define KEY_DOWN    0x04
#define KEY_LEFT    0x08
#define KEY_CENTER  0x10

#define KEYPIN_CENTER 0x00000100
#define KEYPIN_UP     0x00000400
#define KEYPIN_DOWN   0x00001000
#define KEYPIN_LEFT   0x00000200
#define KEYPIN_RIGHT  0x00000800


tU8 checkKey(void);
tU8 checkKey2(void);

void initKeyProc(void);
tU8 getKeys(void);

#endif
