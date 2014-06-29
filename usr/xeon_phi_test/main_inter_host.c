/*
 * Copyright (c) 2007-12 ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <barrelfish/barrelfish.h>
#include <barrelfish/ump_chan.h>
#include <bench/bench.h>
#include <barrelfish/sys_debug.h>

#include <xeon_phi/xeon_phi_messaging.h>
#include <xeon_phi/xeon_phi_messaging_client.h>


int main(int argc,
         char **argv)
{
    errval_t err;

    debug_printf("Inter Card Transfer Test started.\n");

    coreid_t core = 2;
    char *name = "k1om/sbin/xeon_phi_inter";

    err = xeon_phi_messaging_spawn(0, core, name);
    if (err_is_fail(err)) {
        USER_PANIC_ERR(err, "could not send the spawn message");
    }

    err = xeon_phi_messaging_spawn(1, core, name);
    if (err_is_fail(err)) {
        USER_PANIC_ERR(err, "could not send the spawn message");
    }

    debug_printf("Inter Card Transfer Test: Main Loop\n");

    messages_handler_loop();

    debug_printf("Terminated.\n");

}

