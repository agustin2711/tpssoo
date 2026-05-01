#include "fd.h"

t_kernel_scheduler_conexiones conexiones_kernel_scheduler;

void inicializar_conexiones_kernel_scheduler()
{
    conexiones_kernel_scheduler.fd_kernel_memory = -1;
    conexiones_kernel_scheduler.fd_IO_STDIN = -1;
    conexiones_kernel_scheduler.fd_IO_STDOUT = -1;
    conexiones_kernel_scheduler.fd_IO_SLEEP = -1;
    conexiones_kernel_scheduler.lista_cpu = dictionary_create();
}