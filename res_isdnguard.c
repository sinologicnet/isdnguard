/*
 * Copyright (C) 2013 Sinologic as
 * Elio Rojano <erojano@sinologic.net>
 *
 * This program is free software, distributed under the terms of
 * the GNU General Public License Version 2. See the LICENSE file
 * at the top of the source tree.
 */

/*! \file
 *
 * \brief ISDNGuard support for Asterisk 1.6, 1.8, 11
 *
 * \author Elio Rojano <erojano@sinologic.net>
 *
 */

/*** MODULEINFO
	<support_level>extended</support_level>
 ***/

#include "asterisk.h"

ASTERISK_FILE_VERSION(__FILE__, "$Revision: 328259 $")

#include "asterisk/channel.h"
#include "asterisk/module.h"

#include <stdio.h>   /* Standard input/output definitions */ 
#include <string.h>  /* String function definitions */ 
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#define	MODULE_DESCRIPTION	"Sinologic ISDNGuard"

#define ISDNGUARDINTERFACE "/dev/ttyUSB0"
#define ISDNGUARDTIMMING 500

static int sinoISDNGuardRun = 0;
static pthread_t thread = AST_PTHREADT_NULL;
static int fd;

static void *isdnguard_thread(void *args){
  if (sinoISDNGuardRun){
    if (write(fd,"START\n",6) < 0){
      ast_log(LOG_ERROR,"Unable to write in %s\n",ISDNGUARDINTERFACE);
      sinoISDNGuardRun=0;
    }
  }
  while (sinoISDNGuardRun){
    if (write(fd,"PING\n",5) < 0){
      ast_log(LOG_ERROR, "Unable to write in %s\n",ISDNGUARDINTERFACE);
    }else{
      ast_log(LOG_DEBUG, "ISDNGuard PING\n");
    }
    usleep(ISDNGUARDTIMMING*1000);
  }
  return 0;
}

static int load_module(void)
{
    sinoISDNGuardRun=1;
    fd=open(ISDNGUARDINTERFACE, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0){
      ast_log(LOG_ERROR,"Unable to open %s\n",ISDNGUARDINTERFACE);
      return -1;
    }else{
      ast_verb(1, "Loading ISDNGuard Module\n");
      return ast_pthread_create_background(&thread, NULL, isdnguard_thread, NULL);
    }
}

static int unload_module(void)
{
    sinoISDNGuardRun=0;
    if (fd < 0){
      ast_log(LOG_ERROR,"Unable to close %s\n",ISDNGUARDINTERFACE);
      return -1;
    }else{
      ast_verb(1, "Unloading ISDNGuard Module\n");
      close(fd);
      return ((thread != AST_PTHREADT_NULL) ? pthread_join(thread, NULL) : 0);
    }
}

AST_MODULE_INFO(ASTERISK_GPL_KEY, AST_MODFLAG_DEFAULT, "ISDNGuard support for Asterisk 1.8",
    .load = load_module,
    .unload = unload_module,
);
