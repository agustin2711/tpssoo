#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include "../../utils/src/sockets/networking/hilos.h"
#include "networking/protocolo.h"
#include <pthread.h>
#include "networking/fd.h"

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ############### CONFIGURACION Y PROCESOS INICIALES ###################
    // ######################################################################
    //-----------------------------------------------------------------------------------------------------------------------------

    // Cargamos el logger
    t_log *logger = log_create("kernel_scheduler.log", "KERNEL", true, LOG_LEVEL_INFO);

    // Validamos que existan los argumentos del path
    if (argc < 2)
    {
        log_error(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }

    // Cargamos la configuración
    t_kernel_config *config = iniciar_config_kernel_scheduler(argv[1]);

    // Validamos que el config se cargó correctamente
    if (config == NULL)
    {
        log_error(logger, "Error: No se pudo cargar la configuracion correctamente desde %s", argv[1]);
        return EXIT_FAILURE;
    }

    // Inicializamos las conexiones en -1 o NULL
    inicializar_conexiones_kernel_scheduler();

    // ----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ################## CONEXION DE CLIENTE Y SERVIDOR ####################
    // ######################################################################
    // ----------------------------------------------------------------------------------------------------------------------------------

    // Preparamos argumentos para el SERVIDOR
    t_servidor_args *args_servidor = malloc(sizeof(t_servidor_args));
    args_servidor->logger = logger;
    args_servidor->puerto = config->puerto_escucha;
    args_servidor->handler = (void *)atender_cliente_kernel_scheduler;

    // Preparamos argumentos para el CLIENTE
    t_conexion_cliente_args *args_cliente = malloc(sizeof(t_conexion_cliente_args));
    args_cliente->logger = logger;
    args_cliente->ip = config->ip_memoria;
    args_cliente->puerto = config->puerto_memoria;

    // Iniciamos el servidor
    pthread_t th_servidor;
    pthread_create(&th_servidor, NULL, (void *)servidor_multihilo, (void *)args_servidor);
    log_info(logger, "Hilo Servidor Kernel lanzado...");

    // Iniciamos el cliente de memoria
    pthread_t th_cliente;
    pthread_create(&th_cliente, NULL, iniciar_cliente_KernelScheduler, (void *)args_cliente);
    log_info(logger, "Hilo Cliente Memoria lanzado...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------
    pthread_join(th_servidor, NULL);
    pthread_join(th_cliente, NULL);

    // LIMPIEZA
    free(args_cliente);
    free(args_servidor);
    destruir_config(config);
    log_destroy(logger);
    return 0;
}
