/**
 *  @file MotorCmds.h
 *  @brief Motor Controller Commands
 *  @author Prajwal Nataraj
 *
 **/

#ifndef MOTORCMDS_H
#define MOTORCMDS_H

#include "main.h"
#include "string.h"
#include "stdio.h"

#include "MotorParams.h"

#define CMDBYTE_DEVADDR     (CmdBuf[0])
#define CMDBYTE_FUNCCODE    (CmdBuf[1])
#define CMDBYTE_DATALEN     (CmdBuf[2])
#define CMDBYTE_DATA0       (CmdBuf[3])

#define CMD_RET_SUCCESS     (0x00) // Success
#define CMD_RET_UNKNOWNCMD  (0x01) // Unknown Command
#define CMD_RET_NOIMPL      (0x02) // Command Not Implemented
#define CMD_RET_WRONGARGS   (0x03) // Wrong Arguments
#define CMD_RET_NOPERM      (0x04) // No Permissions
#define CMD_RET_IMPROPERENV (0x05) // Improper Conditions
#define CMD_RET_GENERROR    (0x06) // General Error
#define CMD_RET_CRCERROR    (0x07) // Command CRC Error
#define CMD_RET_FACCESSERR  (0x08) // File access error

#define CRC_POL				(0xDB)

#define DEVADDR				(0x01)

#define CMD_GET				(0x01)
#define CMD_SET				(0x02)

#define CMD_INIT			(0x00)
#define CMD_DIST			(0x01)
#define CMD_SPEED			(0x02)
#define CMD_DIR				(0x03)
#define CMD_RESETPRM		(0x04)
#define CMD_START			(0x05)
#define CMD_RUN				(0x06)
#define CMD_STOP			(0x07)
#define CMD_SETZERO			(0x08)
#define CMD_RTZ				(0x09)

#define CMD_EXC_CMDS    	((uint8_t)243)

#define GetCRC(x, y)		checkCRC(x, y)

typedef float float32_t;

/* Standard Return Type */
typedef enum {
    RET_OK = 0,     // Success
    RET_NOK,        // General failure
    RET_HW_NOK,     // Bad hardware / not responding
    RET_ARGS_NOK,   // Improper arguments
    RET_ENV_NOK,    // Improper conditions
    RET_TIMEDOUT,   // Timed out
    RET_NO_IMPL,    // Not implemented
    RET_BUF_FULL,   // Buffer is full
    RET_BUF_EMPTY,  // Buffer is empty
    RET_PROCESSING, // Processing
	RET_CRC_NOK,	// CRC failed
	RET_COM_NOK,	// Communication failed
	RET_DEVADDR_NOK,// Invalid Device Address
} StdReturn_t;

typedef const struct {
    uint8_t FuncCode;   // Function Code
    void (*FuncHandler)(uint8_t *, uint32_t, uint8_t *, uint32_t *);  // Function Handler
} CmdHandler_t;

StdReturn_t Cmd_Process(uint8_t *, uint8_t *, uint32_t *);
uint8_t checkCRC(uint8_t *, uint8_t);

/* Motor Initialization */
void CmdProc_Init(uint8_t *, uint32_t , uint8_t *, uint32_t *);
/* Set/Get Distance in mm */
void CmdProc_Distance(uint8_t *, uint32_t , uint8_t *, uint32_t *);

void CmdProc_Speed(uint8_t *, uint32_t , uint8_t *, uint32_t *);

void CmdProc_Direction(uint8_t *, uint32_t , uint8_t *, uint32_t *);

void CmdProc_CongifAPIs(uint8_t *, uint32_t , uint8_t *, uint32_t *);

void CmdProc_ResetParams(uint8_t *, uint32_t , uint8_t *, uint32_t *);

/* Send Error Message */
void Send_ErrorMsg(uint8_t);

#endif
