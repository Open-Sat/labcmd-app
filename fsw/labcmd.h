/*
** $Id: $
** 
** Purpose: Define the lab command ingest application.
**
** Notes:
**   None
**
** References:
**   1. Core Flight Executive Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/
#ifndef _labcmd_
#define _labcmd_

/*
** Includes
*/

#include "app_config.h"
#include "cmdmgr.h"
#include "uplink.h"


/*
** Macro Definitions
*/

#define LABCMD_INITSTATS_INF_EID       (LABCMD_BASE_EID + 0)
#define LABCMD_APP_INVALID_MID_ERR_EID (LABCMD_BASE_EID + 1)
#define LABCMD_APP_EXIT_EID            (LABCMD_BASE_EID + 2)
#define LABCMD_TOTAL_EID  3


/*
** Type Definitions
*/

typedef struct
{

   CMDMGR_Class CmdMgr;
   UPLINK_Class Uplink;

   CFE_SB_PipeId_t CmdPipe;

} LABCMD_Class;

typedef struct
{

   uint8    Header[CFE_SB_TLM_HDR_SIZE];

   /*
   ** CMDMGR Data
   */
   uint16   ValidCmdCnt;
   uint16   InvalidCmdCnt;

   /*
   ** UPLINK Data
   */

   boolean  SocketConnected;
   boolean  MsgTunnelEnabled;
   uint16   SocketId;
   uint32   RecvMsgCnt;
   uint32   RecvMsgErrCnt;

   uint16   MappingsPerformed;
   UPLINK_LastMapping  LastMapping;

} OS_PACK LABCMD_HkPkt;

#define LABCMD_TLM_HK_LEN sizeof (LABCMD_HkPkt)


/*
** Exported Data
*/

extern LABCMD_Class  LabCmd;


/*
** Exported Functions
*/

/******************************************************************************
** Function: LABCMD_Main
**
*/
void LABCMD_Main(void);


/******************************************************************************
** Function: LABCMD_NoOpCmd
**
*/
boolean LABCMD_NoOpCmd(const CFE_SB_MsgPtr_t MsgPtr);


/******************************************************************************
** Function: LABCMD_ResetAppCmd
**
*/
boolean LABCMD_ResetAppCmd(const CFE_SB_MsgPtr_t MsgPtr);


#endif /* _labcmd_ */
