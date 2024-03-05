#include "Attitude_algorithm.h"
#include "SEEKFREE_ICM20602.h"

/*********鍙橀噺瀹氫�?*********/
State Att;//鏈€缁堢殑瑙掑害
State Att_A;//閫氳繃鍔犻€熷害娴嬬畻鐨勮搴�
State Att_G;//閫氳繃瑙掗€熷害娴嬬畻鐨勮搴�

float D_Gyro[3][3]={0};//瑙掗€熷害鏃嬭浆鐭╅樀

float ICS_Gyro_x;
float ICS_Gyro_y;
float ICS_Gyro_z;//鎯€у弬鑰冪郴涓嬬殑瑙掗€熷�?

int previous_t;//鍗曚綅寰
int current_t;//鍗曚綅寰
float dt;//鍗曚綅绉�?

//鍗″皵鏇兼护娉�?
raw_data raw_imu_data;

KalmanInfo Kal;

void imu_data_convertion(int16 acc_x,int16 acc_y,int16 acc_z,int16 gyro_x,int16 gyro_y,int16 gyro_z)
{
	get_icm20602_accdata_spi();
	get_icm20602_gyro_spi();

	raw_imu_data.acc_data[0] = (float)acc_x*acc_range/resolution;
	raw_imu_data.acc_data[1] = (float)acc_y*acc_range/resolution;
	raw_imu_data.acc_data[2] = (float)acc_z*acc_range/resolution;

	raw_imu_data.gyr_data[0] = (float)gyro_x*gyro_range/resolution*angle_to_rad;
	raw_imu_data.gyr_data[1] = (float)gyro_y*gyro_range/resolution*angle_to_rad;
	raw_imu_data.gyr_data[2] = (float)gyro_z*gyro_range/resolution*angle_to_rad;
}

/*********鍑芥暟缂栧啓*********/

/*
*璁＄畻瑙掗€熷害杞崲鐭╅樀
*/
void Cancer_GetDGyro(float D[3][3])
{
	float tanp=tan(Att.pitch);
	float sinr=sin(Att.roll);
	float cosr=cos(Att.roll);
	float cosp=cos(Att.pitch);
	D[0][0]=1; D[0][1]=tanp*sinr; D[0][2]=tanp*cosr;
	D[1][0]=0; D[1][1]=cosr;      D[1][2]=-sinr;
	D[2][0]=0; D[2][1]=sinr/cosp; D[2][2]=cosr/cosp;

}


/*
*娴嬮噺鍏紡锛�? 
*roll=arctan(ay/az)  pitch=-arctan(ax/sqrt(ay^2+az^2))
*鏍规嵁鍔犻€熷害璁″緱鍒拌娴嬮噺
*/
void Cancer_GetState_Accel(State*att)
{
	imu_data_convertion(icm_acc_x,icm_acc_y,icm_acc_z,icm_gyro_x,icm_gyro_y,icm_gyro_z);

	att->roll=atan2(raw_imu_data.acc_data[1],raw_imu_data.acc_data[2])*180/PI;//娴嬮噺缈绘粴瑙�

	//娴嬮噺淇话瑙�
	float x= raw_imu_data.acc_data[1] * raw_imu_data.acc_data[1] + raw_imu_data.acc_data[2]*raw_imu_data.acc_data[2];
	att->pitch=(-atan2(raw_imu_data.acc_data[0],sqrt(x)))*180/PI;
	
}


/*
*鍗″皵鏇兼护娉�?
*/

void Cancer_KalmanInit(KalmanInfo* Kal)
{
	Kal->Qk=0.0025;//娴嬮噺鏂瑰樊 
	Kal->Rk=0.3;//瑙傛祴鏂瑰樊 
	Kal->H=1;
	Kal->P=1;
	Cancer_GetDGyro(D_Gyro);//鑾峰彇瑙掑害鍙樻崲鐭╅樀
	Cancer_GetState_Accel(&Att);//鑾峰彇璧峰鐘舵€�
}

void Cancer_Kalman_Algo(KalmanInfo* Kal)
{
	
	/******鐘舵€佷及璁�?******/
	imu_data_convertion(icm_acc_x,icm_acc_y,icm_acc_z,icm_gyro_x,icm_gyro_y,icm_gyro_z);
	current_t=imu_get_tick;	//鑾峰彇鏃堕棿
	dt=(float)(current_t-previous_t)/1000;
	previous_t=current_t;//鏇存柊鏃堕棿
	
	//鑾峰彇瑙掗€熷害鐨勪及璁＄粨鏋�
	Att_G.pitch = Att.pitch+(raw_imu_data.gyr_data[0]+D_Gyro[0][1]*raw_imu_data.gyr_data[1]+D_Gyro[0][2]*raw_imu_data.gyr_data[2])*dt;
	Att_G.roll = Att.roll+(D_Gyro[1][1]* raw_imu_data.gyr_data[1] +D_Gyro[1][2]*raw_imu_data.gyr_data[2])*dt;
	
	Att.yaw += raw_imu_data.gyr_data[2]*dt/angle_to_rad ;
	/******鏂瑰樊浼拌******/
	Kal->P+=Kal->Qk;
	
	/******Ka浼拌�?******/
	Kal->Ka=Kal->P/((Kal->P)+(Kal->Rk));
	
	/******淇缁撴灉******/
	Cancer_GetState_Accel(&Att_A);//鑾峰彇娴嬮噺鍊�
	Att.roll=Att.roll+Kal->Ka*(Att_A.roll-Att_G.roll);
	Att.pitch=Att.pitch+Kal->Ka*(Att_A.pitch-Att_G.pitch);


	
	/******鏇存柊鏂瑰樊******/
	Kal->P=(1-Kal->Ka)*Kal->P;
	
}










