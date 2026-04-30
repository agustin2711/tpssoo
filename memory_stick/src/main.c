#include <stdlib.h>
#include <stdio.h>
#include <commons/log.h>
#include <commons/config.h>
#include "config/config_memory_stick.h"
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
    t_log *logger = log_create("memorystick.log", "MEMORY_STICK", 1, LOG_LEVEL_INFO);
    if (argc < 3)
    {
        log_info(logger, "Error: Falta el path del archivo de configuracion.");
        return EXIT_FAILURE;
    }

    // Cargamos la configuración
    t_config_memory_stick *config_memory_stick = iniciar_config_memory_stick(argv[1]);
    // Validamos que el config se cargó correctamente
    if (config_memory_stick == NULL)
    {
        log_error(logger, "Error: No se pudo cargar el archivo de configuración.");
        log_destroy(logger);
        return EXIT_FAILURE;
    }

    // ----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ################## CONEXION DE CLIENTE Y SERVIDOR ####################
    // ######################################################################
    // ----------------------------------------------------------------------------------------------------------------------------------

    // Preparamos argumentos para el SERVIDOR del Cpu
    t_servidor_args *args_servidor = malloc(sizeof(t_servidor_args));
    args_servidor->logger = logger;
    args_servidor->puerto = config_memory_stick->puerto_escucha;
    args_servidor->handler = (void *)atender_cliente_Memory_Stick_Cpu;

    // Preparamos argumentos para el CLIENTE
    t_conexion_cliente_args *args_cliente = malloc(sizeof(t_conexion_cliente_args));
    args_cliente->logger = logger;
    args_cliente->ip = config_memory_stick->ip_memoria;
    args_cliente->puerto = config_memory_stick->puerto_memoria;
    pthread_t th_servidor, th_cliente;

    // Iniciamos el servidor
    pthread_create(&th_servidor, NULL, (void *)servidor_multihilo, (void *)args_servidor);
    log_info(logger, "Hilo Servidor para CPU lanzado...");

    // Iniciamos el cliente de memoria
    pthread_create(&th_cliente, NULL, iniciar_cliente_Memory_Stick_Memory_Kernel, (void *)args_cliente);
    log_info(logger, "Hilo Cliente de Kernel Memory lanzado...");

    //-----------------------------------------------------------------------------------------------------------------------------
    // ######################################################################
    // ######################## LIMPIEZA DE RECURSOS ########################
    // ######################################################################
    // -----------------------------------------------------------------------------------------------------------------------------

    // ESPERAMOS (El join del servidor hará que el main no termine)
    pthread_join(th_servidor, NULL);
    pthread_join(th_cliente, NULL);

    // LIMPIEZA
    free(args_cliente);
    free(args_servidor);
    destruir_config(config_memory_stick);
    log_destroy(logger);
    return 0;
}
