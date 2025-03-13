/**
 *  @file MotorParams.c
 *  @brief Set/Modify Motor Parameters
 *  @author Prajwal Nataraj
 *
 **/

#include "math.h"
#include "MotorParams.h"

#define GEAR_RATIO		6.0f
#define MM_PER_THREAD	5.08f

MotorParams Motor;
sendSpeed_t sendSpeed;

static void Update_ZeroPos(void)
{
	Motor.zeroPosition -= Motor.distance * ((Motor.direction) ? 1 : -1);
}

/* Initialize/Reset Motor Parameters */
bool Motor_Init(void)
{
	return Motor_ResetParams();
}

/* Set Vertical Distance in mm */
bool Motor_SetDistance(float distance)
{
	Motor.distance = distance;
	return true;
}
/* Get Vertical Distance in mm */
float Motor_GetDistance(void)
{
	return Motor.distance;
}

/* Set Vertical Speed in mm/min */
bool Motor_SetSpeed(float speed)
{
	Motor.speed = speed;
	return true;
}
/* Get Vertical Speed in mm/min */
float Motor_GetSpeed(void)
{
	return Motor.speed;
}

/* Set Vertical Direction */
bool Motor_SetDirection(bool dir)
{
	/* 1: UP
	 * 0: DOWN
	 */
	Motor.direction = dir;
	return true;
}
/* Get Vertical Direction */
bool Motor_GetDirection(void)
{
	return Motor.direction;
}

/* Set Zero Position */
bool Motor_SetZeroPos(float dist)
{
	Motor.zeroPosition = dist;
	return true;
}
/* Get Zero Position */
float Motor_GetZeroPos(void)
{
	return Motor.zeroPosition;
}

/* Reset Motor Parameters to 0 */
bool Motor_ResetParams(void)
{
	if(!Motor_Stop(false))
		return false;

	Motor.distance = 0;
	Motor.speed = 0;
	Motor.direction = 0;
	Motor.zeroPosition = 0;

	return true;
}

void Motor_ResetDriveParams(void)
{
	FOC_Init();
}

/* Turn ON motor and align Axis */
bool Motor_Start(void)
{
	MC_StartMotor1();
	HAL_Delay(1500);
//	while(MC_GetAlignmentStatusMotor1() != TC_ALIGNMENT_COMPLETED){}

	return true;
}

/* Stop Vertical Movement */
bool Motor_Stop(bool ready)
{
	MC_StopMotor1();
	HAL_Delay(1000);

	if(ready)
		Motor_Start();

	return true;
}

/* Start the Vertical Movement (post Motor_Start()) */
bool Motor_Run(bool updateZeroPos)
{
//	float rot = 0, set_rot = 0;
	float speed = 0, time = 0;

//	rot = (Motor.distance) * (GEAR_RATIO / MM_PER_THREAD);
//	set_rot = (rot + 0.058) / 1.5001;
//	pos = (set_rot * 2 * M_PI) * ((Motor.direction) ? 1 : -1);
	speed = (float)(Motor.speed * ((Motor.direction) ? 1 :-1)) * (float)(6.0 / 5.08);
	time = 60.0 * (Motor.distance / Motor.speed);

	HAL_Delay(500);

//	MC_ProgramPositionCommandMotor1(pos, time);
	MC_ProgramSpeedRampMotor1(speed, time);
	sendSpeed.prev_time_send = HAL_GetTick();

	if(updateZeroPos)
		Update_ZeroPos();

	return true;
}

bool Motor_SetZero(void)
{
	Motor.zeroPosition = 0;
	return true;
}

bool Motor_RTZ(void)
{
	bool prevDir = 0;
	float prevDist = 0;
	float prevSpeed = 0;

	prevDir = Motor.direction;
	prevDist = Motor.distance;
	prevSpeed = Motor.speed;

	Motor.distance = fabs(Motor.zeroPosition);
	Motor.direction = (Motor.zeroPosition < 0) ? 0 : 1;
	Motor.speed = 1000.0;

	if(Motor_Run(true))
	{
		Motor.direction = prevDir;
		Motor.distance = prevDist;
		Motor.speed = prevSpeed;
	}

	return true;
}

unsigned long Motor_GetRunTick(void)
{
	return sendSpeed.prev_time_send;
}

void Motor_SetRunTick(unsigned long val)
{
	sendSpeed.prev_time_send = val;
}

bool sendToPort(UART_HandleTypeDef *phuart_MD, float sendData)
{
	char sendBuf[15];
	HAL_StatusTypeDef retVal;

	sprintf(sendBuf, "%.2f\r\n", sendData);
	retVal = HAL_UART_Transmit(phuart_MD, (uint8_t *)sendBuf, 15, 100);

	if(HAL_OK == retVal)
		return true;

	return false;
}

//bool Motor_RTZ(void)
//{
//	float prevSpeed = 0;
//
//	prevSpeed = Motor.speed;
//
//	Motor.direction = !Motor.direction;
//	Motor.speed = 1000.0;
//
//	if(Motor_Run())
//	{
//		Motor.direction = !Motor.direction;
//		Motor.speed = prevSpeed;
//	}
//
//	return true;
//}
