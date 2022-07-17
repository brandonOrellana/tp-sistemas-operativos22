#include <kernel.h>

void iterator(char* value) {
	log_info(logger,"%s", value);
}

void cerrar_programa(t_log* logger) {
	log_destroy(logger);
}

void lista_falsa_para_pruebas(t_list* lista){
    
    t_proceso* proceso_uno = malloc(sizeof(t_proceso));
    t_list* instrucciones_test;
    instrucciones_test = list_create();
    u_int32_t tamnio = 7;

    t_instruct *uno_instruccion = malloc(sizeof(t_instruct));
    t_instruct *dos_instruccion = malloc(sizeof(t_instruct));
    t_instruct *tres_instruccion = malloc(sizeof(t_instruct));
    t_no_parms *cero_parametro_a = malloc(sizeof(t_no_parms));
    t_no_parms *cero_parametro_b = malloc(sizeof(t_no_parms));
    t_one_parms *uno_parametro = malloc(sizeof(t_one_parms));
    
    uno_instruccion->operacion=NO_OP;
    uno_instruccion->prm_tipo = cero_parametro_a;
    list_add(instrucciones_test, uno_instruccion);

    dos_instruccion->operacion=I_O;
    uno_parametro->arg1 = 3000;
    dos_instruccion->prm_tipo = uno_parametro;

    list_add(instrucciones_test, dos_instruccion);

    tres_instruccion->operacion=EXIT;
    tres_instruccion->prm_tipo = cero_parametro_b;
    list_add(instrucciones_test, tres_instruccion);

    proceso_uno->tamanio = tamnio;
    proceso_uno->instrucciones = instrucciones_test;
    list_add(lista, proceso_uno);

    //Proceso 2
    t_proceso* proceso_dos =  malloc(sizeof(t_proceso));
    t_list* instrucciones_test_b;
    instrucciones_test_b = list_create();
    u_int32_t tamnio_b = 9;

    t_instruct *uno_instruccion_b = malloc(sizeof(t_instruct));
    t_instruct *dos_instruccion_b = malloc(sizeof(t_instruct));
    t_instruct *tres_instruccion_b = malloc(sizeof(t_instruct));
    t_no_parms *cero_parametro_a_b = malloc(sizeof(t_no_parms));
    t_no_parms *cero_parametro_b_b = malloc(sizeof(t_no_parms));
    t_one_parms *uno_parametro_b = malloc(sizeof(t_one_parms));
    
    uno_instruccion_b->operacion=NO_OP;
    uno_instruccion_b->prm_tipo = cero_parametro_a_b;
    list_add(instrucciones_test_b, uno_instruccion_b);

    dos_instruccion_b->operacion=I_O;
    uno_parametro->arg1 = 3000;
    dos_instruccion_b->prm_tipo = uno_parametro_b;
    list_add(instrucciones_test_b, dos_instruccion_b);

    tres_instruccion_b->operacion=EXIT;
    tres_instruccion_b->prm_tipo = cero_parametro_b_b;
    list_add(instrucciones_test_b, tres_instruccion_b);

    proceso_dos->tamanio = tamnio_b;
    proceso_dos->instrucciones = instrucciones_test_b;
    list_add(lista, proceso_dos);

}

void mostrarLista(t_proceso *proceso){
    printf("lista: %i \n",proceso->tamanio);
}

u_int32_t generar_id(){
    ID++;
    return ID;
}

int espacio_libre_p_proceso(int* grado){
    int tamanio = my_configuracion->grado_multiprogramacion;
    for(int i=0;i<tamanio;i++){
        if(grado[i]==0){
            return i;
        }
    }
    log_error(logger,"No hay espacio de multiprogreamacion para el proceso");
    return -1;
}

void mover_a_ready(t_pcb* un_pcb,t_list* new,t_list* ready){
    //list_remove_by_condition(new, encontrar_id(4)); //Preguntar como funciona
}

int espacio_libre_proceso(t_pcb** grado){
    int n = my_configuracion->grado_multiprogramacion;
    for(int i=0;i<n;i++){
        if(grado[i]==NULL){
            return i;
        }
    }
    return -1;
}

bool encontrar_id(t_pcb* un_pcb,int id){
    return un_pcb->id ==  id? true:false;
}

void iniciar_kernel(){
    int grado_m = my_configuracion->grado_multiprogramacion;
    procesos = list_create();
    procesos_listos = list_create();
}

t_colas* crear_colas(){
    t_colas* colas = malloc(sizeof(t_colas));

    t_queue* cola_new = queue_create();
    t_queue* cola_ready = queue_create();
    t_queue* cola_exec = queue_create();
    t_queue* cola_blocked = queue_create();

    colas->new = cola_new;
    colas->ready = cola_ready;
    colas->exec = cola_exec;
    colas->blocked = cola_blocked;

    return colas;
}

void liberar_memoria(t_log* logger,t_config* config, t_krl_cfg* my_configuracion, int fd_kernel){
    log_destroy(logger);
    config_destroy(config);
    my_configuracion_free(my_configuracion);
    close(fd_kernel);
}	

void my_configuracion_free(t_krl_cfg* my_configuracion){
    free(my_configuracion->ip_cpu);
    free(my_configuracion->puerto_cpu_dispatch);
    free(my_configuracion->puerto_cpu_interrupt);
    free(my_configuracion->puerto_escucha);
    free(my_configuracion->algoritmo_planificacion);
    free(my_configuracion->estimacion_inicial);
    free(my_configuracion->alfa);
    free(my_configuracion->grado_multiprogramacion);
    free(my_configuracion->tiempo_maximo_bloqueado);
    free(my_configuracion);
}