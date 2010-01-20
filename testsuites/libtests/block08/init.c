/*  Init
 *
 *  This routine is the initialization task for this test program.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 * Copyright (C) 2010 OKTET Labs, St.-Petersburg, Russia
 * Author: Oleg Kravtsov <Oleg.Kravtsov@oktetlabs.ru>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#define CONFIGURE_INIT
#include "system.h"

#include "bdbuf_tests.h"

rtems_task Init(rtems_task_argument argument)
{
  rtems_status_code status;

  puts( "\n\n*** TEST BLOCK 8 ***" );
  run_bdbuf_tests();
  puts( "*** END OF TEST BLOCK 8 ***" );
  exit(0);
}

