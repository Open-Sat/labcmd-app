/* 
** File:
**   $Id: $
**
** Purpose: Manage receiving commands over a UDP socket and sending them on the SB.
**
** Notes:
**   1. This is non-flight code so an attempt has been made to balance keeping
**      it simple while making it robust. Limiting the number of configuration
**      parameters and integration items (message IDs, perf IDs, etc) was
**      also taken into consideration.
**   2. Event message filters are not used since this is for test environments.
**      This may be reconsidered if event flooding ever becomes a problem.
**   3. Performance traces are not included.
**
** References:
**   1. Core Flight Executive Application Developers Guide.
**   2. GN&C FSW Framework Programmer's Guide
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

/*
** Includes
*/

#include <string.h>
#include "labcmd.h"


/*
** Local Function Prototypes
*/

static int32 InitApp(void);
static void ProcessCommands(void);

/*
** Global Data
*/

LABCMD_Class  LabCmd;

LABCMD_HkPkt        LabCmdHkPkt;


/******************************************************************************
** Function: LABCMD_Main
**
*/
void LABCMD_Main(void)
{

   int32  Status    = CFE_SEVERITY_ERROR;
   uint32 RunStatus = CFE_ES_APP_ERROR;


   Status = CFE_ES_RegisterApp();
   CFE_EVS_Register(NULL,0,0);

   /*
   ** Perform application specific initialization
   */
   if (Status == CFE_SUCCESS)
   {
       Status = InitApp();
   }

   /*
   ** At this point many flight apps use CFE_ES_WaitForStartupSync() to
   ** synchronize their startup timing with other apps. This is not
   ** needed.
   */

   if (Status == CFE_SUCCESS) RunStatus = CFE_ES_APP_RUN;

   /*
   ** Main process loop
   */
   while (CFE_ES_RunLoop(&RunStatus))
   {


      OS_TaskDelay(LABCMD_RUNLOOP_DELAY);

      UPLINK_Read(LABCMD_RUNLOOP_MSG_READ);

      ProcessCommands();

   } /* End CFE_ES_RunLoop */


   /* Write to system log in case events not working */

   CFE_ES_WriteToSysLog("LABCMD App terminating, err = 0x%08X\n", Status);

   CFE_EVS_SendEvent(LABCMD_APP_EXIT_EID, CFE_EVS_CRITICAL, "LABCMD App: terminating, err = 0x%08X", Status);

   CFE_ES_ExitApp(RunStatus);  /* Let cFE kill the task (and any child tasks) */

} /* End of LABCMD_Main() */


/******************************************************************************
** Function: LABCMD_NoOpCmd
**
*/

boolean LABCMD_NoOpCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   CFE_EVS_SendEvent (666,
                      CFE_EVS_INFORMATION,
                      "No operation command received for Scheduler Lab version %d.%d",
                      LABCMD_MAJOR_VERSION,LABCMD_MINOR_VERSION);

   return TRUE;


} /* End LABCMD_NoOpCmd() */


/******************************************************************************
** Function: LABCMD_ResetAppCmd
**
*/

boolean LABCMD_ResetAppCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   UPLINK_ResetStatus();
   CMDMGR_ResetStatus();

   return TRUE;

} /* End LABCMD_ResetAppCmd() */


/******************************************************************************
** Function: LABCMD_SendHousekeepingPkt
**
*/
void LABCMD_SendHousekeepingPkt(void)
{

   /*
   ** TOLAB Data
   */

   LabCmdHkPkt.ValidCmdCnt   = LabCmd.CmdMgr.ValidCmdCnt;
   LabCmdHkPkt.InvalidCmdCnt = LabCmd.CmdMgr.InvalidCmdCnt;

   /*
   ** Uplink Data
   */

   LabCmdHkPkt.SocketConnected      = LabCmd.Uplink.Connected;
   LabCmdHkPkt.MsgTunnelEnabled     = LabCmd.Uplink.MsgTunnel.Enabled;
   LabCmdHkPkt.SocketId             = LabCmd.Uplink.SocketId;
   LabCmdHkPkt.RecvMsgCnt           = LabCmd.Uplink.RecvMsgCnt;
   LabCmdHkPkt.RecvMsgErrCnt        = LabCmd.Uplink.RecvMsgErrCnt;

   LabCmdHkPkt.MappingsPerformed    = LabCmd.Uplink.MsgTunnel.MappingsPerformed;
   LabCmdHkPkt.LastMapping.Index    = LabCmd.Uplink.MsgTunnel.LastMapping.Index;
   LabCmdHkPkt.LastMapping.OrgMsgId = LabCmd.Uplink.MsgTunnel.LastMapping.OrgMsgId;
   LabCmdHkPkt.LastMapping.NewMsgId = LabCmd.Uplink.MsgTunnel.LastMapping.NewMsgId;

   CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &LabCmdHkPkt);
   CFE_SB_SendMsg((CFE_SB_Msg_t *) &LabCmdHkPkt);

} /* End LABCMD_SendHousekeepingPkt() */


/******************************************************************************
** Function: InitApp
**
*/
static int32 InitApp(void)
{
    int32 Status = CFE_SUCCESS;

    /*
    ** Initialize 'entity' objects
    */

    UPLINK_Constructor(&LabCmd.Uplink);

    /*
    ** Initialize application managers
    */

    CFE_SB_CreatePipe(&LabCmd.CmdPipe, CMDMGR_PIPE_DEPTH, CMDMGR_PIPE_NAME);
    CFE_SB_Subscribe(LABCMD_CMD_MID, LabCmd.CmdPipe);
    CFE_SB_Subscribe(LABCMD_SEND_HK_MID, LabCmd.CmdPipe);

    CMDMGR_Constructor(&LabCmd.CmdMgr);
    CMDMGR_RegisterFunc(LABCMD_CMD_RESET_FC,             LABCMD_ResetAppCmd,        0);
    CMDMGR_RegisterFunc(LABCMD_CMD_NOOP_FC,              LABCMD_NoOpCmd,            0);
    CMDMGR_RegisterFunc(LABCMD_CMD_CONFIG_MSG_TUNNEL_FC, UPLINK_ConfigMsgTunnelCmd, UPLINK_CONFIG_MSG_TUNNEL_CMD_DATA_LEN);

    CFE_SB_InitMsg(&LabCmdHkPkt, LABCMD_TLM_HK_MID, LABCMD_TLM_HK_LEN, TRUE);

    /*
    ** Application startup event message
    */
    Status = CFE_EVS_SendEvent(LABCMD_INITSTATS_INF_EID,
                               CFE_EVS_INFORMATION,
                               "LABCMD Initialized. Version %d.%d.%d.%d",
                               LABCMD_MAJOR_VERSION,
                               LABCMD_MINOR_VERSION,
                               LABCMD_REVISION,
                               LABCMD_MISSION_REV);

    return(Status);

} /* End of InitApp() */


/******************************************************************************
** Function: ProcessCommands
**
*/
static void ProcessCommands(void)
{

   int32           Status = CFE_SEVERITY_ERROR;
   CFE_SB_Msg_t*   CmdMsgPtr;
   CFE_SB_MsgId_t  MsgId;

   Status = CFE_SB_RcvMsg(&CmdMsgPtr, LabCmd.CmdPipe, CFE_SB_POLL);

   if (Status == CFE_SUCCESS)
   {

      MsgId = CFE_SB_GetMsgId(CmdMsgPtr);

      switch (MsgId)
      {
         case LABCMD_CMD_MID:
            CMDMGR_DispatchFunc(CmdMsgPtr);
            break;

         case LABCMD_SEND_HK_MID:
            LABCMD_SendHousekeepingPkt();
            break;

         default:
            CFE_EVS_SendEvent(LABCMD_APP_INVALID_MID_ERR_EID, CFE_EVS_ERROR,
                              "Received invalid command packet,MID = 0x%4X",MsgId);

            break;

      } /* End Msgid switch */

   } /* End if SB received a packet */

} /* End ProcessCommands() */


/* end of file */





