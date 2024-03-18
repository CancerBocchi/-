#include "headfile.h"
#include "isr.h"
#include "Attitude_algorithm.h"
#include "debug_tool.h"

rt_thread_t motor_thread; 

void motor_entry()
{
    while(1)
    {
        gpio_toggle(B9);
        encoder_getvalue();
        Motor_Pwm_cb();
        gpio_toggle(B9);
        rt_thread_delay(1);
    }
}

int main()
{
    motor_thread = rt_thread_create("motor",motor_entry,NULL,4096,1,1000);
    
    if(motor_thread!=NULL)
    {
        rt_thread_startup(motor_thread);
    }
    

    gpio_init(B25,GPO,1,GPIO_OPENDRAW);
    gpio_init(B9,GPO,1,GPIO_PIN_CONFIG);

    rt_thread_delay(1000);

    gpio_set(B25,0);

    Motor_init();

    while(1)
    {


    }
        
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
//     //???????��flash?????????????????��?????????????debug?????
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
//     uart_init (USART_8, 115200,UART8_TX_D16,UART8_RX_D17); //?????????
//     // VOFA+
// //    VOFA* VOFA_pt = vofa_create();       //????VOFA????
// //    vofa_init(VOFA_pt
// //		,                   //??????????vofa????
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
// //    while(1){//??????????????
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

// 			//??????????????
//         //rt_thread_mdelay(10);
//         //???????????????

//         //img_raw.data = mt9v03x_csi_image[0];
//         //adaptive_threshold(&img_raw, &img_thres, block_size, clip_value, 0, 255);//???????????
//         //Find_Edge_1();


//         if(Car.Position_Pointer<locate_sz){//locate_sz => true_sz??
//             //car_noheadmove();
//             car_omnimove();//��???????????????????
//         }else if(Car.Position_Pointer>=locate_sz){
//             car_return();
//         }



//         rt_thread_delay(1);//????????????????????��???
//         //vofa_Send();
//         //rt_mb_send(buzzer_mailbox,23);

//         //??��?????????
// //        openartMode=get_picture;
// //        Car.Speed_X=picture_xerror_pid(picture_location[0],154);
// //        Car.Speed_Y=picture_yerror_pid(picture_location[1],156);
//				
//     }
// }

//  

 //��????????��?????????????????????��????????????