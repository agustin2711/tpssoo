#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config_cpu.h"
#include "networking/protocolo.h"
#include "../../utils/src/sockets/networking/protocolo.h"
#include "../../utils/src/sockets/networking/hilos.h"
#include "../../cpu/src/logger/logger.h"
#include "../../cpu/src/registros/registros.h"
int main(int argc, char *argv[])
{
    char* IDCPU = argv[1];
    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ############### CONFIGURACION Y PROCESOS INICIALES ###################
    // ######################################################################
    //-----------------------------------------------------------------------------------------------------------------------------
    // Creamos el Logger

    t_log *logger = CrearLogger(IDCPU);
    if (argc < 2)
    {
        log_info(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }
        log_info(logger,"hola soy el CPU Numero: %s", argv[1]);
    // Cargamos la configuración
    
    t_config_cpu *config_cpu = iniciar_config_cpu(IDCPU);

    // Validamos la configuración
    if (config_cpu == NULL)
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
    // Creamos y cargamos los argumentos
    t_conexion_cliente_args *args_cliente = malloc(sizeof(t_conexion_cliente_args));
    args_cliente->logger = logger;
    args_cliente->ip = config_cpu->ip_kernel_scheduler;
    args_cliente->puerto = config_cpu->puerto_kernel_scheduler;
    pthread_t th_cliente_Kernel_Scheduler;

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente_Kernel_Scheduler, NULL, iniciar_cliente_Cpu_KernelScheduler, (void *)args_cliente);
    log_info(logger, "Hilo Cliente Scheduler Kerel...");

    // --- CONEXIÓN A MEMORY STICK ---
    // Creamos y cargamos los argumentos
    args_cliente->ip = config_cpu->ip_memorystick;
    args_cliente->puerto = config_cpu->puerto_memorystick;
    pthread_t th_cliente_Memory_Stick;

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente_Memory_Stick, NULL, iniciar_cliente_Cpu_MemoryStick, (void *)args_cliente);
    log_info(logger, "Hilo Cliente Memory Stick...");

    // --- CONEXIÓN A KERNEL MEMORY ---
    // Creamos y cargamos los argumentos
    args_cliente->ip = config_cpu->ip_kernel_memory;
    args_cliente->puerto = config_cpu->puerto_kernel_memory;
    pthread_t th_cliente_Memory_Kernel;

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente_Memory_Kernel, NULL, iniciar_cliente_Cpu_MemoryKernel, (void *)args_cliente);
    log_info(logger, "Hilo Cliente Memory Kernel...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------
    pthread_join(th_cliente_Kernel_Scheduler, NULL);
    pthread_join(th_cliente_Memory_Stick, NULL);
    pthread_join(th_cliente_Memory_Kernel, NULL);

    // --- LIMPIEZA FINAL ---
    destruir_config_cpu(config_cpu);
    log_destroy(logger);
    free(args_cliente);

    while(true){};

    return 0;
}