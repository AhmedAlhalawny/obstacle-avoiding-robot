/*
 * STD_types.h
 *
 * Created: 10/20/2021 1:00:57 AM
 *  Author: Ahmed ALhalawany
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

//unsigned data types 
 
typedef unsigned char        uint8;
typedef unsigned int         uint16;
typedef unsigned long long   uint32;

//signed data types
typedef signed char       int8;
typedef signed int        int16;
typedef signed long long  int32;


typedef enum
{
STD_low=0,
STD_high=!STD_low	

	}STD_leveltype; 

#endif /* STD_TYPES_H_ */