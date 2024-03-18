#ifndef _VOFA_H
#define _VOFA_H

#include "headfile.h"

typedef struct _DATA_S
{
	float data0;
	float data1;
	float data2;
	float data3;
	float data4;
	float data5;
	float data6;
	float data7;
	float data8;
	float data9;
}DATA_S;


extern DATA_S DATA_Space_0;

void vofa_send_data(DATA_S *DATA);



#endif