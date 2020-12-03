#ifndef WiringPrivate_h
#define WiringPrivate_h

#include <stdint.h>
#include <stdio.h>
#include "include/ch554.h"
#include "include/ch554_usb.h"

#include "Arduino.h"


typedef void (*voidFuncPtr)(void);

#define EXTERNAL_INT_0 0
#define EXTERNAL_INT_1 1

#define EXTERNAL_NUM_INTERRUPTS 2

#endif