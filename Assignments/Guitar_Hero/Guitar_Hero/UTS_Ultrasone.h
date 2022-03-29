/*
 * UTS_UltrasoneSensor_Component.h
 *
 * Created: 29-3-2022 09:12:59
 * Author: Jesse
 */ 
#ifndef UTS_ULTRASONE_H
#define UTS_ULTRASONE_H

/************************************************************************/
/* CurrentDistance is defined in UTS_Ultrasoon.c, gives the				*/
/* current distance from the sensor										*/
/************************************************************************/
extern int currentDistance;

/************************************************************************/
/* Inits the ultrasone sensor											*/
/************************************************************************/
void UTS_Init( void );

/************************************************************************/
/* Triggers the ultrasone sensor for update								*/
/************************************************************************/
void UTS_Trigger( void );

#endif