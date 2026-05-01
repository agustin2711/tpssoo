#ifndef FD_H_
#define FD_H_
#include <commons/collections/dictionary.h>

typedef struct
{
    int ID;
    int socket;
} t_CPU;

typedef struct
{
    int fd_kernel_scheduler;
    int fd_kernel_memory;
    t_dictionary *lista_memory_stick;
} t_cpu_conexiones;

// Variable global
extern t_cpu_conexiones conexiones_cpu;
void inicializar_conexiones_cpu();
#endif