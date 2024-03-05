#ifndef __MPU6050_Attitude_algorithm__
#define  __MPU6050_Attitude_algorithm__

#include "math.h"
#include "headfile.h"

#define K 0.4f
#define angle_to_rad 0.0174532925f

#ifndef PI
	#define PI 3.1415926f
#endif // !

#define acc_range  16		//g
#define gyro_range 4000		//degree ps
#define resolution 65536 	//2^16


#define imu_get_tick rt_tick_get()

typedef struct state 
{
    float roll;//横滚 x
    float yaw;//俯仰 y
    float pitch;//偏航 z
}State;

typedef struct 
{
	float P;//协方�?
	float Ka;//卡尔曼增�?
	float Qk;//估计噪声的方�?
	float Rk;//观测噪声的方�?
	float H;//测量矩阵
}KalmanInfo;

typedef struct raw_data
{
	float acc_data[3];
	float gyr_data[3];
}raw_data;

extern State Att;
extern KalmanInfo Kal;
extern raw_data raw_imu_data;

void Cancer_GetState_Accel(State*att);
void Cancer_KalmanInit(KalmanInfo* Kal);
void Cancer_Kalman_Algo(KalmanInfo* Kal);

#endif 