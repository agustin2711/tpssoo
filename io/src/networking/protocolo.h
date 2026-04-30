#ifndef PROTOCOLOS_H_
#define PROTOCOLOS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <commons/log.h>

#include "../../../utils/src/sockets/networking/protocolo.h"

void *iniciar_cliente_Io_KernelScheduler(void *void_args);

#endif