#ifndef MOTORPARAMS_H
#define MOTORPARAMS_H

#include "main.h"
#include "stdbool.h"
#include "mc_tasks.h"

/**
 *  @file MotorParams.h
 *  @brief Set/Modify Motor Parameters
 *  @author Prajwal Nataraj
 *
 **/

#include "MotorCmds.h"

typedef struct
{
	unsigned long prev_time_send;
}sendSpeed_t;

typedef struct
{
	float distance;
	float speed;
	bool direction;
	float zeroPosition;
}MotorParams;

/* Initialize/Reset Motor Parameters */
bool Motor_Init(void);
/* Set Vertical Distance in mm */
bool Motor_SetDistance(float);
/* Get Vertical Distance in mm */
float Motor_GetDistance(void);
/* Set Vertical Speed in mm/min */
bool Motor_SetSpeed(float);
/* Get Vertical Speed in mm/min */
float Motor_GetSpeed(void);
/* Set Vertical Direction */
bool Motor_SetDirection(bool);
/* Get Vertical Direction */
bool Motor_GetDirection(void);
/* Set Zero Position */
bool Motor_SetZeroPos(float);
/* Get Zero Position */
float Motor_GetZeroPos(void);
/* Reset Motor Parameters to 0 */
bool Motor_ResetParams(void);
/* Resets the Motor's Drive Parameters */
void Motor_ResetDriveParams(void);
/* Turn ON motor and align Axis */
bool Motor_Start(void);
/* Stop Vertical Movement */
bool Motor_Stop(bool);
/* Start the Vertical Movement (post Motor_Start()) */
bool Motor_Run(bool);
/* Set Zero Point */
bool Motor_SetZero(void);
/* Return Motor back to Zero Point */
bool Motor_RTZ(void);

unsigned long Motor_GetRunTick(void);
void Motor_SetRunTick(unsigned long);
/* Send Data to COM Port */
bool sendToPort(UART_HandleTypeDef *, float);

#endif
