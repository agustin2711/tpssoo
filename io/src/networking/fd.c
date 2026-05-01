#include "fd.h"

t_io_conexiones conexiones_io;

void inicializar_conexiones_io()
{
    conexiones_io.fd_kernel_scheduler = -1;
}