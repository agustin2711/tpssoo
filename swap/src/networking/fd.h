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
    int fd_kernel_memory;
} t_swap_conexiones;

// Variable global
extern t_swap_conexiones conexiones_swap;
void inicializar_conexiones_swap();
#endif