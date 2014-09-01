/*
 * File:
 *   $Id: $
 *
 * Purpose: This file contains a unit test cases for uplink.c
 *
 * $Date: $
 * $Revision: $
 * $Log: $
 */

/*
 * Includes
 */

#include "common_types.h"
#include "utassert.h"
#include "uttest.h"
#include "uplink.h"

static UPLINK_Class  UtUplink;

/*
** Function Definitions
*/


/* UPLINK_Test01  - Constructor */
void UPLINK_Test01(void)
{

   printf("UPLINK_Test01()\n");
   UPLINK_Constructor (&UtUplink);

} /* End UPLINK_Test01() */


/* UPLINK_Test02  - TBD  */
void UPLINK_Test02(void)
{

   printf("UPLINK_Test02()\n");

} /* End UPLINK_Test02() */

/* UPLINK_Test03  - Functional  */
void UPLINK_Test03(void)
{

   printf("UPLINK_Test03()\n");

   /* TODO - Functional test as used by Scheduler Lab */

} /* End UPLINK_Test03() */

/* Initialize test environment to default state for every test */
void UPLINK_Setup(void)
{

   UPLINK_Constructor (&UtUplink);

}

void UPLINK_TearDown(void)
{
    /* cleanup test environment */
}

void UPLINK_AddTestCase(void)
{
    UtTest_Add(UPLINK_Test01, UPLINK_Setup, UPLINK_TearDown, "UPLINK_Test01 - Constructor");
    UtTest_Add(UPLINK_Test02, UPLINK_Setup, UPLINK_TearDown, "UPLINK_Test02 - TBD");
}
