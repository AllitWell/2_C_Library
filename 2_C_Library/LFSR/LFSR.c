//Copyright(c)2016,LIN
//License()
//Author: lin
//Email:clandence@gmail.com
//File name: LFSR.C
//Version:0.1.0
//Modify date: 2017.4.11

#include "LFSR.h"

//宏定义表
#define HSB_32 0X80000000  //最高位
//常量介绍：线性移位寄存器的输入干扰多项式
const uint32_t mask = 0X0FC22F87;
/*
*函数介绍：与寄存器值进行异或后进行32位左移
*输入参数：uint32_t reg_val :寄存器初始值
*		  uint32_t add_val: 寄存器输入项
*输出参数：处理后寄存器的值
*返回值：处理后寄存器的值
*/
uint32_t reg_add( uint32_t reg_val, uint32_t add_val ) {
    uint8_t inc = 0;
    uint8_t temp = 0;

    reg_val ^= add_val;//先异或
    for( inc = 0; inc < 32; ++inc ) {
        temp = ( ( reg_val & HSB_32 ) != 0 ) ? 1 : 0;
        reg_val = reg_val << 1;
        if( temp == 1 )
            reg_val ^= mask;
    }

    return reg_val;
}

/*
*函数介绍：post_val右移后与寄存器内的值异或
*输入参数：uint32_t reg_val :寄存器初始值
*		  uint32_t add_val: 寄存器输入项
*输出参数：处理后寄存器的值
*返回值：处理后寄存器的值
*/
uint32_t reg_post( uint32_t reg_val, uint32_t post_val ) {
    uint8_t inc = 0;
    uint8_t temp = 0;

    for( inc = 0; inc < 32; ++inc ) {
        if( ( temp = post_val & 1 ) == 1 )
            post_val ^= mask;
        post_val = post_val >> 1;
        post_val |= ( temp ) ? HSB_32 : 0;
    }
    post_val ^= reg_val;

    return post_val;
}