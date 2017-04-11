//Copyright(c)2016,LIN
//License()
//Author: lin
//Email:clandence@gmail.com
//File name: LFSR.C
//Version:0.1.0
//Modify date: 2017.4.11

#include "LFSR.h"

//�궨���
#define HSB_32 0X80000000  //���λ
//�������ܣ�������λ�Ĵ�����������Ŷ���ʽ
const uint32_t mask = 0X0FC22F87;
/*
*�������ܣ���Ĵ���ֵ�����������32λ����
*���������uint32_t reg_val :�Ĵ�����ʼֵ
*		  uint32_t add_val: �Ĵ���������
*��������������Ĵ�����ֵ
*����ֵ�������Ĵ�����ֵ
*/
uint32_t reg_add( uint32_t reg_val, uint32_t add_val ) {
    uint8_t inc = 0;
    uint8_t temp = 0;

    reg_val ^= add_val;//�����
    for( inc = 0; inc < 32; ++inc ) {
        temp = ( ( reg_val & HSB_32 ) != 0 ) ? 1 : 0;
        reg_val = reg_val << 1;
        if( temp == 1 )
            reg_val ^= mask;
    }

    return reg_val;
}

/*
*�������ܣ�post_val���ƺ���Ĵ����ڵ�ֵ���
*���������uint32_t reg_val :�Ĵ�����ʼֵ
*		  uint32_t add_val: �Ĵ���������
*��������������Ĵ�����ֵ
*����ֵ�������Ĵ�����ֵ
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