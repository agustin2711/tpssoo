#include "protocolo.h"
#include "../../../utils/src/sockets/networking/protocolo.h"
#include "fd.h"
#include <commons/collections/dictionary.h>

// Funcion de conexion del cliente del Kernel Scheduler a Kernel Memory
void *iniciar_cliente_KernelScheduler(void *void_args)
{
    t_conexion_cliente_args *args = (t_conexion_cliente_args *)void_args;

    log_info(args->logger, "Intentando conectar con Memoria en %s:%s...",
             args->ip, args->puerto);

    int fd_memoria = crear_conexion(args->logger, args->ip, args->puerto);

    if (fd_memoria != -1)
    {

        if (realizar_handshake(fd_memoria, "Kernel Scheduler", args->logger) == 0)
        {
            log_info(args->logger, "Handshake con Kernel Memory completado exitosamente.");
            conexiones_kernel_scheduler.fd_kernel_memory = fd_memoria;
            log_info(args->logger, "Se guardo el fd: %d del cliente Kernel Memory", conexiones_kernel_scheduler.fd_kernel_memory);
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
    conexiones_kernel_scheduler.fd_kernel_memory = -1; // Indicamos que se va a cerrar la conexión o que no se pudo establecer
    return NULL;
}

//---------------------------------------------------------------------------------------------------------------

// Funcion para atender a los clientes que se conecten al servidor del Kernel Scheduler
void *atender_cliente_kernel_scheduler(void *void_args)
{
    t_atender_cliente_args *args = (t_atender_cliente_args *)void_args;
    int cliente_fd = args->fd;
    t_log *logger = args->logger;

    while (1)
    {
        int cod_op = recibir_operacion(cliente_fd);
        switch (cod_op)
        {
        case HANDSHAKE:
            uint32_t size;
            char *nombre_cliente = (char *)recibir_buffer(&size, cliente_fd);

            log_info(logger, "Se conectó el módulo: %s", nombre_cliente);

            // Guardamos el socket del cliente que se conectó, dependiendo de su nombre
            guardar_fd_cliente(nombre_cliente, cliente_fd, logger);
            responder_handshake(cliente_fd);

            free(nombre_cliente);
            break;

        case -1:
            log_error(logger, "El cliente se desconectó.");
            free(args);
            return NULL;

        default:
            log_warning(logger, "Operación desconocida.");
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------
void guardar_fd_cliente(char *nombre_cliente, int fd, t_log *logger)
{
    // Ver como agregar CPUs
    if (strncmp(nombre_cliente, "CPU", 3) == 0)
    {
        dictionary_put(conexiones_kernel_scheduler.lista_cpu, nombre_cliente, &fd);
        int stored_fd = *(int *)dictionary_get(conexiones_kernel_scheduler.lista_cpu, nombre_cliente);
        log_info(logger, "Se guardo el fd: %d del cliente %s", stored_fd, nombre_cliente);
    }
    else if (strcmp(nombre_cliente, "IO_STDIN") == 0)
    {
        conexiones_kernel_scheduler.fd_IO_STDIN = fd;
        log_info(logger, "Se guardo el fd: %d del cliente IO_STDIN", conexiones_kernel_scheduler.fd_IO_STDIN);
    }
    else if (strcmp(nombre_cliente, "IO_STDOUT") == 0)
    {
        conexiones_kernel_scheduler.fd_IO_STDOUT = fd;
        log_info(logger, "Se guardo el fd: %d del cliente IO_STDOUT", conexiones_kernel_scheduler.fd_IO_STDOUT);
    }
    else if (strcmp(nombre_cliente, "IO_SLEEP") == 0)
    {
        conexiones_kernel_scheduler.fd_IO_SLEEP = fd;
        log_info(logger, "Se guardo el fd: %d del cliente IO_SLEEP", conexiones_kernel_scheduler.fd_IO_SLEEP);
    }
    if (strcmp(nombre_cliente, "KERNEL MEMORY") == 0)
    {
        conexiones_kernel_scheduler.fd_kernel_memory = fd;
        log_info(logger, "Se guardo el fd: %d del cliente KERNEL MEMORY", conexiones_kernel_scheduler.fd_kernel_memory);
    }
    else
    {
        log_warning(logger, "Cliente desconocido: %s. No se guardó su fd.", nombre_cliente);
    }
}