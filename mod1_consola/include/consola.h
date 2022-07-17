#ifndef CONSOLA_H
#define CONSOLA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utils/helloStatic.h>
#include <utils/structs.h>
#include <utils/client.h>

/**
* @NAME:iniciar_logger
* @DESC:Inicia un logger para posteriormente utilizarlo
*/
t_log* iniciar_logger(void);

/**
* @NAME:iniciar_config
* @DESC:
*/
t_config* iniciar_config(void);

/**
* @NAME:terminar_programa
* @DESC:Se libera la memoria de config, log y my_configuracion
*/
void terminar_programa(t_log*, t_csl_cfg*, t_config*);

/**
* @NAME:leer_archivo
* @DESC:Se abre el archivo de txt pasado por el path del main y se lo guarda en 
        una lista del tipo Instruccion.
*/
void leer_archivo_y_cargar_lista(char*,t_list*);

/**
* @NAME:obtenerInstruccion
* @DESC:Se lee una linea de archivo, y lo fracciona por espacios pasa un parametro,
        del vector dende se guardo la linea de archivo, a la funcion obtenerOperacion.
*/
void obtenerInstruccion(char*,t_list *);

/**
* @NAME:obtenerOperacion
* @DESC:Convierte el string tomado por la fucion leer_archivo que representa la operacion
        y devuelve el enum correspondiente a la operacion.
*/
op_operate obtenerOperacion(char*);

/**
* @NAME:insertar_varias_veces
* @DESC:Funcion creada para el operando especial NO_OP, una instruccion especial que se repite
        a si mismo varias veces.
*/
void insertar_varias_veces(t_list*,op_operate,int);

/**
* @NAME:mostrarLista
* @DESC:Funcion para ver por consola que contiene la lista creada con las fucniones.
*/
void mostrarLista(t_instruct *);

/**
* @NAME:leer_archivo_de_configuracion
* @DESC:Funcion que crea un config de la commons y agrega los datos del archivo de configuracion
        a una variable.
*/
void leer_archivo_de_configuracion_consola(t_config*,t_csl_cfg*);

/**
* @NAME:iniciar_log
* @DESC:iniciar log
*/
void iniciar_log();

/**
* @NAME:control_de_path
* @DESC:Verifica que se recivan los parametros correctos por consola.
*/
int control_de_path(int);

/**
* @NAME:generar_proceso
* @DESC:Genera un proceso que contiene la lista de instruccion y el tamanio pasado por parametro a la consola.
*/
t_proceso* generar_proceso(t_list*,u_int32_t);

/**
* @NAME:mensajePrueba
* @DESC:Envia un mensaje de conexion completada al kernel para verificar conexion.
*/
void mensajePrueba(t_log* logger, char *ip, char* puerto, int fd_kernel);

/**
* @NAME:obtener_no_parametro
* @DESC:crea una estructura para los parametros que no lleva argumentos
*/
t_no_parms* obtener_no_parametro(void);

/**
* @NAME:obtener_one_parametro
* @DESC:crea una estructura para los parametros que lleva un argumento
*/
t_one_parms* obtener_one_parametro(char **);

/**
* @NAME:obtener_two_parametro
* @DESC:crea una estructura para los parametros que lleva dos arguntos
*/
t_two_parms* obtener_two_parametro(char **);

/**
* @NAME:enviar_proceso_al_kernel
* @DESC:Crea el paquete con el proceso, establece conexion con kernel y envia el paquete.
*/
void enviar_proceso_al_kernel(t_proceso*, t_csl_cfg*, t_log*);
#endif