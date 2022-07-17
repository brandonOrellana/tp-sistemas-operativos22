#ifndef KERNEL_H_
#define KERNEL_H_

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
//#include <protocolo.h>

u_int32_t ID;
t_list *procesos_nuevos;
t_list *procesos_finalizados;
t_list *procesos_listos;
t_list *procesos;

int grado_multiprogramacion;

/**
* @NAME:
* @DESC:
*/ 
void iterator(char*);

/*
* @NAME:
* @DESC:
*/ 
void mostrarLista(t_proceso*);

/*
* @NAME:
* @DESC:
*/ 
void lista_falsa_para_pruebas(t_list*);//elimar cuando se implemente las conexiones

/*
* @NAME:
* @DESC:
*/ 
u_int32_t generar_id(void);
    
void iterator(char* value);

/**
* @NAME:
* @DESC:
*/ 
void cerrar_programa(t_log* logger);

/**
* @NAME:
* @DESC:
*/ 
t_pcb* asignar_grado_de_multiprogramacion();


void mover_a_ready(t_pcb*,t_list*,t_list*);

int espacio_libre_proceso(t_pcb**);

bool encontrar_id(t_pcb*,int);

void iniciar_kernel();

/**
* @NAME: crear_colas()
* @DESC: Instancia las colas de procesos (new, ready, exec, blocked).
*/
t_colas* crear_colas();

/**
* @NAME: liberar_memoria()
* @DESC: Destrye el logger y config, hace free de my_configuracion y cierra conexion.
*/
void liberar_memoria(t_log*, t_config*, t_krl_cfg*, int);

/**
* @NAME: my_configuracion_free()
* @DESC: Hace free de cada campo de my_configuracion del kernel.
*/
void my_configuracion_free(t_krl_cfg*);

#endif