/*  Task_1
 *
 *  This task generates all possible errors for the RTEMS executive.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "system.h"
#include <rtems/rtems/tasksimpl.h>


rtems_task Task_1(
  rtems_task_argument argument
)
{
  uint32_t            notepad_value;
  rtems_id            self_id;
  rtems_task_priority previous_priority;
  rtems_status_code   status;

  /* bad Id */
  status = rtems_task_is_suspended( 100 );
  fatal_directive_status(
    status,
    RTEMS_INVALID_ID,
    "rtems_task_set_priority with illegal id"
  );
  puts( "TA1 - rtems_task_is_suspended - RTEMS_INVALID_ID" );

  /* bad Id */
  status = rtems_task_delete( 100 );
  fatal_directive_status(
    status,
    RTEMS_INVALID_ID,
    "rtems_task_delete with illegal id"
  );
  puts( "TA1 - rtems_task_delete - RTEMS_INVALID_ID" );

  /** START OF NOTEPAD TESTS **/

  /*
   * We know this is deprecated and don't want a warning on every BSP built.
   */
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wdeprecated-declarations"

    /* NULL return */
    status = rtems_task_get_note( RTEMS_SELF, RTEMS_NOTEPAD_FIRST, NULL );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ADDRESS,
      "rtems_task_get_note with NULL param"
    );
    puts( "TA1 - rtems_task_get_note - RTEMS_INVALID_ADDRESS" );

    /* note too high */
    status = rtems_task_get_note( RTEMS_SELF, 100, &notepad_value );
    fatal_directive_status(
      status,
      RTEMS_INVALID_NUMBER,
      "rtems_task_get_note with illegal notepad"
    );
    puts( "TA1 - rtems_task_get_note - RTEMS_INVALID_NUMBER" );

    /* bad Id */
    status = rtems_task_get_note( 100, RTEMS_NOTEPAD_LAST, &notepad_value );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_get_note with illegal id"
    );
    puts( "TA1 - rtems_task_get_note - RTEMS_INVALID_ID" );

    /* unused Id so invalid now */
    status = rtems_task_get_note(
      Task_id[ 0 ],
      RTEMS_NOTEPAD_LAST,
      &notepad_value
    );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_get_note with illegal id"
    );
    puts( "TA1 - rtems_task_get_note - RTEMS_INVALID_ID" );

    status = rtems_task_get_note(
      _RTEMS_tasks_Information.Objects.minimum_id + (3L<<OBJECTS_API_START_BIT),
      RTEMS_NOTEPAD_LAST,
      &notepad_value
    );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_get_note with illegal id"
    );

    status = rtems_task_get_note(
      rtems_build_id( OBJECTS_CLASSIC_API, 2, 1, 1 ),
      RTEMS_NOTEPAD_LAST,
      &notepad_value
    );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_get_note with non-task ID"
    );

    /* NULL param */
    status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, NULL );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ADDRESS,
      "rtems_task_ident NULL param"
    );
    puts( "TA1 - rtems_task_ident - RTEMS_INVALID_ADDRESS" );

    /* OK */
    status = rtems_task_ident( RTEMS_SELF, RTEMS_SEARCH_ALL_NODES, &self_id );
    directive_failed( status, "rtems_task_ident of self" );
    if ( self_id != Task_id[ 1 ] ) {
      puts( "ERROR - rtems_task_ident - incorrect ID returned!" );
    }
    puts( "TA1 - rtems_task_ident - current task RTEMS_SUCCESSFUL" );

    status = rtems_task_ident( 100, RTEMS_SEARCH_ALL_NODES, &Junk_id );
    fatal_directive_status(
      status,
      RTEMS_INVALID_NAME,
      "rtems_task_ident with illegal name (local)"
    );
    puts( "TA1 - rtems_task_ident - global RTEMS_INVALID_NAME" );

    status = rtems_task_ident( 100, 1, &Junk_id );
    fatal_directive_status(
      status,
      RTEMS_INVALID_NAME,
      "rtems_task_ident with illegal name (global)"
    );
    puts( "TA1 - rtems_task_ident - local RTEMS_INVALID_NAME" );

    /*
     *  This one case is different if MP is enabled/disabled.
     */

    status = rtems_task_ident( 100, 2, &Junk_id );
  #if defined(RTEMS_MULTIPROCESSING)
    fatal_directive_status(
      status,
      RTEMS_INVALID_NODE,
      "rtems_task_ident with illegal node"
    );
  #else
    fatal_directive_status(
      status,
      RTEMS_INVALID_NAME,
      "rtems_task_ident with illegal node"
    );
  #endif
    puts( "TA1 - rtems_task_ident - RTEMS_INVALID_NODE" );

    status = rtems_task_restart( 100, 0 );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_restart with illegal id"
    );
    puts( "TA1 - rtems_task_restart - RTEMS_INVALID_ID" );

    status = rtems_task_resume( 100 );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_resume with illegal id"
    );
    puts( "TA1 - rtems_task_resume - RTEMS_INVALID_ID" );

    status = rtems_task_resume( RTEMS_SELF );
    fatal_directive_status(
      status,
      RTEMS_INCORRECT_STATE,
      "rtems_task_resume of ready task"
    );
    puts( "TA1 - rtems_task_resume - RTEMS_INCORRECT_STATE" );

    /* NULL param */
    status = rtems_task_set_priority( RTEMS_SELF, RTEMS_CURRENT_PRIORITY, NULL );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ADDRESS,
      "rtems_task_set_priority with NULL param"
    );
    puts( "TA1 - rtems_task_set_priority - RTEMS_INVALID_ADDRESS" );

    /* bad priority */
    status = rtems_task_set_priority( RTEMS_SELF, 512, &previous_priority );
    fatal_directive_status(
      status,
      RTEMS_INVALID_PRIORITY,
      "rtems_task_set_priority with illegal priority"
    );
    puts( "TA1 - rtems_task_set_priority - RTEMS_INVALID_PRIORITY" );

    /* bad Id */
    status = rtems_task_set_priority( 100, 8, &previous_priority );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_set_priority with illegal id"
    );
    puts( "TA1 - rtems_task_set_priority - RTEMS_INVALID_ID" );

    status = rtems_task_set_note(
      RTEMS_SELF,
      RTEMS_NOTEPAD_LAST+10,
      notepad_value
    );
    fatal_directive_status(
      status,
      RTEMS_INVALID_NUMBER,
      "rtems_task_set_note with illegal notepad"
    );
    puts( "TA1 - rtems_task_set_note - RTEMS_INVALID_NUMBER" );

    status = rtems_task_set_note( 100, RTEMS_NOTEPAD_LAST, notepad_value );
    fatal_directive_status(
      status,
      RTEMS_INVALID_ID,
      "rtems_task_set_note with illegal id"
    );
    puts( "TA1 - rtems_task_set_note - RTEMS_INVALID_ID" );

  #pragma GCC diagnostic pop

  /** END OF NOTEPAD TESTS **/

  status = rtems_task_start( 100, Task_1, 0 );
  fatal_directive_status(
    status,
    RTEMS_INVALID_ID,
    "rtems_task_start with illegal id"
  );
  puts( "TA1 - rtems_task_start - RTEMS_INVALID_ID" );

  /* already started */
  status = rtems_task_start( RTEMS_SELF, Task_1, 0 );
  fatal_directive_status(
    status,
    RTEMS_INCORRECT_STATE,
    "rtems_task_start of ready task"
  );
  puts( "TA1 - rtems_task_start - RTEMS_INCORRECT_STATE" );

  /* bad Id */
  status = rtems_task_suspend( 100 );
  fatal_directive_status(
    status,
    RTEMS_INVALID_ID,
    "rtems_task_suspend with illegal id"
  );
  puts( "TA1 - rtems_task_suspend - RTEMS_INVALID_ID" );

  /* NULL param */
  status = rtems_task_mode( RTEMS_SELF, 0, NULL );
  fatal_directive_status(
    status,
    RTEMS_INVALID_ADDRESS,
    "rtems_task_mode with NULL param"
  );
  puts( "TA1 - rtems_task_mode - RTEMS_INVALID_ADDRESS" );
 
  TEST_END();

  rtems_test_exit( 0 );
}
