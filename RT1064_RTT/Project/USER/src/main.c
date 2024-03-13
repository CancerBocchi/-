/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�


//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������

//���ش���ǰ������Լ�ʹ�õ��������ڹ���������������Ϊ�Լ���ʹ�õ�

#include "headfile.h"
#include "isr.h"
#include "Attitude_algorithm.h"
#include "debug_tool.h"

void led_entry()
{
    int tick = rt_tick_get();

    while(1)
    {
            lcd_showstr(5,5,"YSJ");
            lcd_clear(WHITE);       
            //rt_thread_delay(1);

            //rt_kprintf("led:toggle pin B9!\n");
    }
}

void print_entry()
{
	int i;
    while(1)
    {
        //rt_kprintf("print:this thread is running!\n");
        rt_thread_delay(1000);
    }
}

void Attitude_algorithm_entry()
{
    rt_kprintf("attitude_algorithm thread created successfully!\n");
    while(1)
    {
        Cancer_Kalman_Algo(&Kal);
        
        //rt_kprintf("%.3f,%.3f,%.3f,%.3f\n",Att.pitch,Att.roll,Att.yaw,raw_imu_data.gyr_data[2]);
        // rt_kprintf("%.3f,%.3f,%.3f,,%,3f\n",0.1,0.1,0.1);
        rt_thread_delay(1);
    }
}

rt_thread_t led_thread;
rt_thread_t print_thread;
rt_thread_t Attitude_algorithm_thread;

int main()
{
	icm20602_init_spi();
    Cancer_KalmanInit(&Kal);
    lcd_init();
    debug_tool_init();

    gpio_init(B9,GPO,0,GPIO_PIN_CONFIG);
    led_thread = rt_thread_create("led",led_entry,RT_NULL,1024,20,5);

    print_thread = rt_thread_create("print",print_entry,RT_NULL,512,20,5);

    Attitude_algorithm_thread = rt_thread_create("Attitude_algorithm",Attitude_algorithm_entry,RT_NULL,4096,10,20);

    if(led_thread != RT_NULL){
        rt_thread_startup(led_thread);
        // rt_kprintf("led:thread created successful!\n");
    }
    else{
        rt_kprintf("led:thread creation failed!\n");
    }

    if(print_thread != RT_NULL){
        rt_thread_startup(print_thread);
    }
    else{
        rt_kprintf("print_thread creation failed\n");
    }

    if(Attitude_algorithm_thread != RT_NULL)
    {
        rt_thread_startup(Attitude_algorithm_thread);
    }
    else{
        rt_kprintf("Attitude_algorithm_thread creation failed\n");
    }
	
    // pit_init();
    // pit_interrupt(PIT_CH0,75000);



	// while(1)
	// {
    //     if(flag)
    //     {
    //         get_icm20602_accdata_spi();
    //         rt_kprintf("%d\n",icm_acc_z);
    //         flag = 0;
    //     }
	// }
	
	return 0;

}





// #include "display.h"
// #include "timer_pit.h"
// #include "encoder.h"
// #include "buzzer.h"
// #include "button.h"
// #include "motor.h"
// #include "elec.h"
// #include "openart_mini.h"
// #include "smotor.h"
// #include "location.h"
// #include "attitude_solution.h"
// #include "vofa.h"
// #include "flash_param.h"
// #include "imgproc.h"
// #include "carmove.h"
// #include "MahonyAHRS.h"
// #include "sendmsg.h"


// extern image_t img_raw;
// extern image_t img_thres;
// extern image_t img_line;
// rt_sem_t camera_sem;
// void Find_Edge_1(void);

// extern int openartBuffer;

// uint8 uart_test;
// int main(void)
// {
//     ips114_init();
//     ips114_showstr(0,0,"mt9v03x-init...");
//     //mt9v03x_csi_init();
//     ips114_showstr(150,0,"ok");
//	
//     ips114_showstr(0,1,"imu963ra-init...");
// //    imu963ra_init();
// //    imu_offset_init();
    // icm20602_init_spi();
    // gyroOffset_init();
//     ips114_showstr(150,1,"ok");
//	
//     ips114_showstr(0,2,"encoder-init...");
//     encoder_init();
//     ips114_showstr(150,2,"ok");

//     ips114_showstr(0,3,"buzzer-init...");
//      buzzer_init();
//     ips114_showstr(150,3,"ok");

//     ips114_showstr(0,4,"button-init...");
//     button_init();
//     ips114_showstr(150,4,"ok");

//     ips114_showstr(0,5,"motor-init...");
//     motor_init();
//     ips114_showstr(150,5,"ok");

//     ips114_showstr(0,6,"flash-init...");
//     flash_param_init();
//     //��һ����дflash����ʱ��Ҫ���������仰�������ã�����debug�����
//     //flash_param_write();
//     flash_param_load();
//     ips114_showstr(150,6,"ok");
//    
//      elec_init();

//     ips114_showstr(0,7,"smotor-init...");
//     smotor_init();
//     ips114_showstr(150,7,"ok");
//		
//     ips114_showstr(0,8,"timer_pit...");
//     timer_pit_init();
//     ips114_showstr(150,8,"ok");

//     //location_thres_init();

//     ips114_showstr(0,9,"uart-init...");
//     uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17); //��ʼ������
//     // VOFA+
// //    VOFA* VOFA_pt = vofa_create();       //����VOFA����
// //    vofa_init(VOFA_pt
// //		,                   //��ʼ����ǰ��vofa����
// //              vofa_ch_data,ch_sz,
// //              vofa_image,image_sz,
// //              custom_buf,custom_sz,
// //              cmd_rxbuf,cmd_sz,
// //              USART_8,USART_8,USART_8);
//     ips114_showstr(150,9,"ok");

//     ips114_showstr(0,10,"openart_mini...");
//     openart_mini();
//     ips114_showstr(150,10,"ok");

//     EnableGlobalIRQ(0);
//     Car.Angel_Target=0;

//     display_init();
//     rt_thread_delay(1000);

//     rt_mb_send(buzzer_mailbox,1000);

//     Gui_Page_Active=true;
//     Page_Number=TargetPointPage;
//     reset_mileage();
// //    while(1){//���Ա���������ֵ
// //        carmove_mileage(500,0);
// //        rt_thread_delay(10000);
// //        carmove_mileage(-500,0);
// //        carmove_mileage(0,400);
// //        rt_thread_delay(10000);
// //        carmove_mileage(0,-400);
// //        break;
// //    }   

//     while(1){
//         uart_putstr(USART_4,"1\n");
//         rt_thread_delay(2);
//         if(openartMode==get_picture){
//             rt_thread_delay(1500);
//             speed_tar=20;
//             Page_Number=InfoPage;
//             Gui_Page_Active=true;
//             break;
//         }
//     }

//     carlocation_init();
//     while (1)
//     {

// 			//�ȴ�����ͷ�ɼ����
//         //rt_thread_mdelay(10);
//         //��ʼ��������ͷͼ��

//         //img_raw.data = mt9v03x_csi_image[0];
//         //adaptive_threshold(&img_raw, &img_thres, block_size, clip_value, 0, 255);//�Զ���ֵ��ֵ��
//         //Find_Edge_1();


//         if(Car.Position_Pointer<locate_sz){//locate_sz => true_sz��
//             //car_noheadmove();
//             car_omnimove();//С����ͷ��Զ��ǰ���˶���ʽ
//         }else if(Car.Position_Pointer>=locate_sz){
//             car_return();
//         }



//         rt_thread_delay(1);//�����յĻ��������߳����в���
//         //vofa_Send();
//         //rt_mb_send(buzzer_mailbox,23);

//         //ͼƬλ�þ�������
// //        openartMode=get_picture;
// //        Car.Speed_X=picture_xerror_pid(picture_location[0],154);
// //        Car.Speed_Y=picture_yerror_pid(picture_location[1],156);
//				
//     }
// }

//  

 //дһ�������λ�Ƶ��ƶ����������ƺ����ܺúܶࣿҪ��Ȼ���Ƚϴ�