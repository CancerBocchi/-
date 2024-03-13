#include "debug_tool.h"

float a = 1.3f;
int c = 1923;

static int arg_count;
void debug_tool_init()
{
    //调参命令初始化 获取注册表中的参数个数
    arg_change* p = arg_register;
    while(p->arg!=NULL)
    {
        p++;
        arg_count++;
    }


}

/**
 * @brief 调参命令
 * 
 *      使用方法
 *      将对应参数的相关信息写入注册表
 *      需要满足：
 *      1.名字不能相同
 *      2.类型使用宏定义
 *      3.最后一项 NULL 为计算参数使用，不要更改
 *      setarg show --- 展示所有支持修改的变量
 *      setarg <name> <value> --- 修改对应变量的值
 */

static arg_change* match_arg(char* str)
{
    for(int i = 0;i<arg_count;i++)
    {
        if(!rt_strcmp(arg_register[i].name,str))
        {
            return arg_register+i;
        }
    }
    return NULL;
}

static int arg_count;

//参数注册表
arg_change arg_register[] = {
    {"P",DEBUG_FLOAT,&a},
    {"demo2",DEBUG_INT,&c},
    {NULL,NULL,NULL}
};

static void setarg(int argc, char**argv)
{
    switch (argc)
    {
    case 1:
        goto help;
        break;
    case 2:
        if(!rt_strcmp("show",argv[1]))
        {
            rt_kprintf("|      name      |      value     |\n");
            for(int i = 0;i<arg_count;i++)
            {
                rt_kprintf("|%-16s|",arg_register[i].name);
                
                switch(arg_register[i].conp)
                {
                case DEBUG_FLOAT:
                    rt_kprintf("%-16.6f|\n",*(float*)arg_register[i].arg);
                    
                    break;
                case DEBUG_INT:
                    rt_kprintf("%-16d|\n",*(int*)arg_register[i].arg);
                    
                    break;
                }
            }
        }
        else
            goto help;
        break;

    case 3:
	{
        arg_change* p;
        p = match_arg(argv[1]);
        if(p!=NULL)
        {
            switch (p->conp)
            {
            case DEBUG_FLOAT:
				*(float*)p->arg = atof(argv[2]);
				rt_kprintf("setarg: arg %s have been changed to %f !\n",p->name,*(float*)p->arg);
                break;
            case DEBUG_INT:
                *(int*)p->arg = atoi(argv[2]);
				rt_kprintf("setarg: arg %s have been changed to %d !\n",p->name,*(int*)p->arg);
                break;
            }
            
        }
	}
        break;
    
    default:
        goto help;
        break;
    }
	return;

help:
    rt_kprintf("you can use like this:\n");
    rt_kprintf("setarg show             ----- show the arg in the register \n");
    rt_kprintf("setarg <target> <value> ----- change the value of the target\n");
    rt_kprintf("setarg help             ----- get help information\n");
	return;
}

MSH_CMD_EXPORT(setarg, setarg sample: setarg <_target_> <number>);

