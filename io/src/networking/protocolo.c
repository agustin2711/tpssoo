#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "../../../utils/src/sockets/networking/sockets.h"
void *iniciar_cliente_Io_KernelScheduler(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Kernel Scheduler en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "IO", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Kernel Scheduler completado exitosamente.");
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Kernel Scheduler.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Kernel Scheduler.");
    }

    return NULL;
}

//---------------------------------------------------------------------------------------------------------------
