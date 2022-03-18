/*
 * bit_math.h
 *
 * Created: 10/20/2021 1:17:54 AM
 *  Author: Ahmed ALhalawany
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_
#include "STD_types.h"
uint8 port,pin;

#define set_bit(port,pin)      (port|=(1<<pin))
#define clear_bit(port,pin)    (port&=~(1<<pin))
#define get_bit(port,pin)      (port&=(1<<pin))
#define toggel_bit(port,pin)   (port^=(1<<pin))


#endif /* BIT_MATH_H_ */