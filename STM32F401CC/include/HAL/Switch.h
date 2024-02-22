#ifndef SWITCH_H
#define SWICH_H

#include "STD_TYPES.h"
#include "Errors.h"
#include "Switch_cfg.h"

#define PULL_DOWN	2
#define PULL_UP 1

typedef struct{
	void* switch_Port;
	u8 switch_Pin;
	u8 switch_Connection;
}Switch_cfg_t;

ErrorStatus_t Switch_init(void);
#endif
