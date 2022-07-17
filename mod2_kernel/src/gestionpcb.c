#include <gestionpcb.h>

t_pcb* crear_pcb(char* buffer, t_krl_cfg* my_configuracion, t_log* logger){
    t_pcb* pcb = malloc(sizeof(t_pcb));
    pcb->id = generar_id(); //Remain ver si esta bien generar un id asi
    pcb->tamanio = leer_entero(buffer,0);
    pcb->instrucciones = deserializar_paquete(buffer);
    pcb->program_counter = 0;
    pcb->tabla_paginas = 0;
    pcb->estimacion_rafaga = my_configuracion->estimacion_inicial;
    pcb->estado = NEW;
    return pcb;
}

void deserializar_paquete(char* buffer){
    t_list* lista;
    int cantidad_elementos = leer_entero(buffer, 1);
    
    cantidad_elementos++;
    for(int i = 2; i <= cantidad_elementos; i++){
        int operacion = leer_entero(buffer, i);
        if(operacion == NO_OP){
            list_add(lista, operacion);
        }
        else if(operacion == I_O){
            t_one_parms* parametro = malloc(sizeof(t_one_parms));
            parametro->arg1 = leer_entero(buffer, i+1);
            list_add(lista, parametro);
            i++;
        }
        else if(operacion == WRITE){
            t_two_parms* parametro = malloc(sizeof(t_two_parms));
            parametro->arg1 = leer_entero(buffer, i+1);
            parametro->arg2 = leer_entero(buffer, i+2);
            list_add(lista, parametro);
            i++;
        }
        else if(operacion == COPY){
            t_two_parms* parametro = malloc(sizeof(t_two_parms));
            parametro->arg1 = leer_entero(buffer, i+1);
            parametro->arg2 = leer_entero(buffer, i+2);
            list_add(lista, parametro);
            i++;
        }
        else if(operacion == READ){
            t_one_parms* parametro = malloc(sizeof(t_one_parms));
            parametro->arg1 = leer_entero(buffer, i+1);
            list_add(lista, parametro);
            i++;
        }
        else if(operacion == EXIT){
            list_add(lista, operacion);
        }
        free(i);
        free(operacion);
    }
    return lista;
}