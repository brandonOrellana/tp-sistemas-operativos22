#include <configuracion.h>

t_log* iniciar_logger(void){
	t_log* nuevo_logger;
    if((nuevo_logger = log_create("kernel.log","KERNEL",1,LOG_LEVEL_INFO))==NULL){
        printf("No se creo el log \n");
        exit(1);
    }
	return nuevo_logger;
}

t_config* iniciar_config(void){
	t_config* nuevo_config;
    if((nuevo_config=config_create("./kernel.config")) == NULL){
        printf("No se creo el config \n");
        exit(2);
    }
	return nuevo_config;
}

void iniciar_log(){
    logger = iniciar_logger();
}

void leer_archivo_de_configuracion_kernel(t_config* config,t_krl_cfg* my_configuracion){
    my_configuracion->ip_memoria = config_get_string_value(config,"IP_MEMORIA");
    my_configuracion->puerto_memoria = config_get_int_value(config,"PUERTO_MEMORIA");
    my_configuracion->ip_cpu = config_get_string_value(config,"IP_CPU");
    my_configuracion->puerto_cpu_dispatch = config_get_int_value(config,"PUERTO_CPU_DISPATCH");
    my_configuracion->puerto_cpu_interrupt = config_get_int_value(config,"PUERTO_CPU_INTERRUPT");
    my_configuracion->puerto_escucha = config_get_int_value(config,"PUERTO_ESCUCHA");
    my_configuracion->algoritmo_planificacion = config_get_string_value(config,"ALGORITMO_PLANIFICACION");
    my_configuracion->estimacion_inicial = config_get_int_value(config,"ESTIMACION_INICIAL");
    my_configuracion->alfa = config_get_double_value(config,"ALFA");
    my_configuracion->grado_multiprogramacion = config_get_int_value(config,"GRADO_MULTIPROGRAMACION");
    my_configuracion->tiempo_maximo_bloqueado = config_get_int_value(config,"TIEMPO_MAXIMO_BLOQUEADO");

    log_info(logger,"INICIANDO KERNEL");
    log_info(logger,"En IP memoria: %s \n\t\t\t\t\tPuerto memoria: %i \n\t\t\t\t\tIp cpu: %s \n\t\t\t\t\tPuerto dispatch: %i \n\t\t\t\t\tPuerto interrupt: %i \n\t\t\t\t\tPuerto escucha: %i \n\t\t\t\t\tCon algoritmo: %s \n\t\t\t\t\tEstimacion: %i \n\t\t\t\t\tAlfa: %.2f \n\t\t\t\t\tGrado programacion: %i \n\t\t\t\t\tTiempo max loqueo: %i\n",my_configuracion->ip_memoria,
                                                    my_configuracion->puerto_memoria,
                                                    my_configuracion->ip_cpu,
                                                    my_configuracion->puerto_cpu_dispatch,
                                                    my_configuracion->puerto_cpu_interrupt,
                                                    my_configuracion->puerto_escucha,
                                                    my_configuracion->algoritmo_planificacion,
                                                    my_configuracion->estimacion_inicial,
                                                    my_configuracion->alfa,
                                                    my_configuracion->grado_multiprogramacion,
                                                    my_configuracion->tiempo_maximo_bloqueado);
}

t_pcb* asignar_grado_de_multiprogramacion(){
    int tamanio = my_configuracion->grado_multiprogramacion;
    t_pcb* grado[tamanio];
    return grado;
}