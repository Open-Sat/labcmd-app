/*
** $Id: $
** 
** Purpose: Define platform configurations for the Lab Command Input application
**
** Notes:
**
** References:
**   1. CFS Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

#ifndef _labcmd_platform_cfg_
#define _labcmd_platform_cfg_

/*
** Includes
*/

/******************************************************************************
** Lab Command Input Application Macros
*/

#define  LABCMD_RUNLOOP_DELAY     500  /* Delay in milliseconds for main loop      */
#define  LABCMD_RUNLOOP_MSG_READ   10  /* Max messages read in main loop iteration */

#define  LABCMD_PORT     1234

#define  LABCMD_CMD_MID           0x1884
#define  LABCMD_SEND_HK_MID       0x1885
#define  LABCMD_TLM_HK_MID        0x0884

/******************************************************************************
** UPLINK Object Macros
**
** - Unused message ID definition is robust. If the cFE highest definition is
**   the maximum for a storage type then adding one will roll over (assuming
**   unsigned).
*/

#define UPLINK_RECV_BUFF_LEN  1024
#define UPLINK_UNUSED_MSG_ID    (CFE_SB_HIGHEST_VALID_MSGID+1)
#define UPLINK_MSG_TUNNEL_CNT  8  /* Number of Message ID tunnels */


#endif /* _labcmd_platform_cfg_ */
