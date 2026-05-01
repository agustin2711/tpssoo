#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "../../../utils/src/sockets/networking/sockets.h"
#include "fd.h"
void *iniciar_cliente_Swap_Kernel_Memory(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Kernel Memory en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "Swap", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Kernel Memory completado exitosamente.");
            conexiones_swap.fd_kernel_memory = fd;
            log_info(args->logger, "Conexión con Kernel Memory establecida en el fd %d.", fd);
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Kernel Memory.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Kernel Memory.");
    }

    return NULL;
}