#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "../../../utils/src/sockets/networking/sockets.h"
void *iniciar_cliente_Cpu_KernelScheduler(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Kernel Scheduler en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "CPU", args->logger) == 0)
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

void *iniciar_cliente_Cpu_MemoryStick(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Memory Stick en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "CPU", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Memory Stick completado exitosamente.");
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Memory Stick.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Memory Stick.");
    }

    return NULL;
}

//---------------------------------------------------------------------------------------------------------------

void *iniciar_cliente_Cpu_MemoryKernel(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Memory Kernel en %s:%s...",
             args->ip, args->puerto);

    int fd = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd != -1)
    {

        if (realizar_handshake(fd, "CPU", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Memory Kernel completado exitosamente.");
        }
        else
        {
            log_error(args->logger, "Fallo el handshake con Memory Kernel.");
        }
    }
    else
    {
        log_error(args->logger, "No se pudo establecer conexión con Memory Kernel.");
    }

    return NULL;
}
