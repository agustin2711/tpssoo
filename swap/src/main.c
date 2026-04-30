#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config_swap.h"
#include "networking/protocolo.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include <pthread.h>

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------

    // Creamos el Logger
    t_log *logger = log_create("swap.log", "SWAP", 1, LOG_LEVEL_INFO);

    // Validamos el path
    if (argc < 2)
    {
        log_error(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }

    // Cargamos la configuración
    t_config_swap *config = iniciar_config_swap(argv[1]);

    // Validamos que el config se cargó correctamente
    if (config == NULL)
    {
        fprintf(stderr, "Error: No se pudo cargar la configuracion correctamente desde %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ################## CONEXION DE CLIENTE Y SERVIDOR ####################
    // ######################################################################
    // ----------------------------------------------------------------------------------------------------------------------------------
    // --- CONEXIÓN A KERNEL MEMORY ---
    // Creamos los argumentos para
    t_conexion_cliente_args *args_cliente = malloc(sizeof(t_conexion_cliente_args));
    args_cliente->logger = logger;
    args_cliente->ip = config->ip_memoria_swap;
    args_cliente->puerto = config->puerto_memoria_swap;
    pthread_t th_cliente_Swap;

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente_Swap, NULL, iniciar_cliente_Swap_Kernel_Memory, (void *)args_cliente);
    log_info(logger, "Hilo Cliente de Memory Kernel...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------
    pthread_join(th_cliente_Swap, NULL);

    // --- LIMPIEZA FINAL ---
    destruir_config_swap(config);
    log_destroy(logger);
    free(args_cliente);

    return 0;
}
