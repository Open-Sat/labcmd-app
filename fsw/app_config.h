/*
** $Id: $
** 
** Purpose: Define configurations for the Lab Command Input application
**
** Notes:
**   1. These macros can only be built with the application and can't
**      have a platform scope because the same file name is used for
**      all applications following the object-based application design pattern.
**
** References:
**   1. CFS Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

#ifndef _app_config_
#define _app_config_

/*
** Includes
*/

#include "labcmd_mission_cfg.h"
#include "labcmd_platform_cfg.h"


/******************************************************************************
** Command Input Lab Application Macros
*/

#define  LABCMD_MAJOR_VERSION      1
#define  LABCMD_MINOR_VERSION      0
#define  LABCMD_REVISION           0
#define  LABCMD_MISSION_REV        0

/******************************************************************************
** Command Macros
*/

#define LABCMD_CMD_RESET_FC               0
#define LABCMD_CMD_NOOP_FC                1
#define LABCMD_CMD_CONFIG_MSG_TUNNEL_FC   2
#define LABCMD_CMD_TOTAL_FC               3

#define CMDMGR_CMD_FUNC_TOTAL   10
#define CMDMGR_PIPE_DEPTH       10
#define CMDMGR_PIPE_NAME        "LABCMD_CMD_PIPE"
#define CMDMGR_CMD_MSG_TOTAL    2

/******************************************************************************
** Event Macros
*/

#define LABCMD_BASE_EID   0   /* Used by labcmd.h */
#define CMDMGR_BASE_EID  10   /* Used by cmdmgr.h */
#define UPLINK_BASE_EID  20   /* Used by uplink.h */


/******************************************************************************
** uplink.h Configurations
*/


#endif /* _app_config_ */
