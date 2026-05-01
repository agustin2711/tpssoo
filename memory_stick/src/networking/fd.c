#include "fd.h"

t_memory_stick_conexiones conexiones_memory_stick;

void inicializar_conexiones_memory_stick()
{
    conexiones_memory_stick.fd_kernel_memory = -1;
    conexiones_memory_stick.lista_cpu = dictionary_create();
}