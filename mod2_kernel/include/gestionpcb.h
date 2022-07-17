#ifndef GESTIONPCB_H_
#define GESTIONPCB_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <string.h>
#include <sys/stat.h>
#include <utils/structs.h>
#include <utils/client.h>
#include <utils/server.h>
#include <utils/mySocket.h>
#include <configuracion.h>


t_pcb* procesos_ready;


/**
* @NAME: crear_pcb
* @DESC: Instancia una pcb cargandole la lista de instrucciones y el tamanio de la misma.
*/ 
t_pcb* crear_pcb(char* buffer, t_krl_cfg* my_configuracion, t_log* logger);

#endif /* GESTIONPCB_H_ */
