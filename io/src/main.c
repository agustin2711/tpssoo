#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config_io.h"
#include "networking/protocolo.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include "../../utils/src/sockets/networking/hilos.h"

int main(int argc, char *argv[])
{
    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ############### CONFIGURACION Y PROCESOS INICIALES ###################
    // ######################################################################
    //-----------------------------------------------------------------------------------------------------------------------------
    // Creamos el Logger
    t_log *logger = log_create("io.log", "IO", 1, LOG_LEVEL_INFO);
    // Validamos el path
    if (argc < 3)
    {
        log_error(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }

    // Cargamos la configuración
    t_config_io *config_io = iniciar_config_io(argv[1]);
    // Validamos que el config se cargó correctamente
    if (config_io == NULL)
    {
        log_error(logger, "Error: No se pudo cargar la configuracion correctamente desde %s", argv[1]);
        return EXIT_FAILURE;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ################## CONEXION DE CLIENTE Y SERVIDOR ####################
    // ######################################################################
    // ----------------------------------------------------------------------------------------------------------------------------------
    // --- CONEXIÓN A KERNEL SCHEDULER ---
    // Creamos argumentos
    t_conexion_cliente_args *args_cliente = malloc(sizeof(t_conexion_cliente_args));
    args_cliente->logger = logger;
    args_cliente->ip = config_io->ip_kernel_scheduler;
    args_cliente->puerto = config_io->puerto_kernel_scheduler;
    pthread_t th_cliente_Kernel_Scheduler;

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente_Kernel_Scheduler, NULL, iniciar_cliente_Io_KernelScheduler, (void *)args_cliente);
    log_info(logger, "Hilo Cliente Scheduler lanzado...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------
    pthread_join(th_cliente_Kernel_Scheduler, NULL);

    // Si todo sale bien se hace destroy ya que el anterior era en caso de error
    log_destroy(logger);
    destruir_config_io(config_io);
    free(args_cliente);
    return 0;
}
