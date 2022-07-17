#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_
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

/**
* @NAME:
* @DESC:
*/    
t_log* iniciar_logger(void);

/*
* @NAME:
* @DESC:
*/ 
t_config* iniciar_config(void);


/*
* @NAME:
* @DESC:
*/ 
void iniciar_log();

/*
* @NAME:
* @DESC:
*/ 
void leer_archivo_de_configuracion_kernel(t_config* config, t_krl_cfg* my_configuracion);

/**
* @NAME:
* @DESC:
*/ 
t_pcb* asignar_grado_de_multiprogramacion();

#endif