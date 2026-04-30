#include <commons/log.h>
#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>
#include "config/config_kernel_memory.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include "../../utils/src/sockets/networking/hilos.h"
#include "networking/protocolo.h"
#include <pthread.h>

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ############### CONFIGURACION Y PROCESOS INICIALES ###################
    // ######################################################################
    //-----------------------------------------------------------------------------------------------------------------------------
    // Crear Logger
    t_log *logger = log_create("kernel_memory.log", "Kernel Memory", 1, LOG_LEVEL_INFO);
    // Validamos los argumentos del path
    if (argc < 2)
    {
        log_error(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }
    // Cargamos la configuración
    t_kernel_memory *config = iniciar_config_kernel_memory(argv[1]);
    // Validamos que el config se cargó correctamente
    if (config == NULL)
    {
        log_error(logger, "Error: No se pudo cargar la configuracion correctamente desde %s", argv[1]);
        return EXIT_FAILURE;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ################## CONEXION DE CLIENTE Y SERVIDOR ####################
    // ######################################################################
    // ----------------------------------------------------------------------------------------------------------------------------------

    // Preparamos argumentos para el SERVIDOR
    t_servidor_args *args_servidor = malloc(sizeof(t_servidor_args));
    args_servidor->logger = logger;
    args_servidor->puerto = config->puerto_escucha;
    args_servidor->handler = (void *)atender_cliente_kernel_memory;
    pthread_t th_servidor;

    // Iniciamos el servidor
    pthread_create(&th_servidor, NULL, (void *)servidor_multihilo, (void *)args_servidor);
    log_info(logger, "Hilo Servidor Kernel lanzado...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------

        pthread_join(th_servidor, NULL);

    // LIMPIEZA
    destruir_config(config);
    log_destroy(logger);

    return 0;
}
