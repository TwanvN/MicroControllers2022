/*
 * TMP_TempMeter.h
 *
 * Created: 31-3-2022 09:05:37
 *  Author: Jesse
 */ 

/************************************************************************/
/* Sets all the registers for the tempo meter and ultrasone module      */
/************************************************************************/
void TMP_init_meassure();

/************************************************************************/
/* Sends one measure pulse to the UTS module							*/
/* And measures the current tempo that is playing                       */
/************************************************************************/
void TMP_meassure();

/************************************************************************/
/* Returns if the tempo is correct, the user is playing                 */
/************************************************************************/
int TMP_isPlaying();
