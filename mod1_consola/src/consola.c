#include <consola.h> 


t_log* iniciar_logger(void){
	t_log* nuevo_logger;
    if((nuevo_logger = log_create("consola.log","CONSOLA",1,LOG_LEVEL_INFO))==NULL){
        printf("No se creo el log \n");
        exit(1);
    }
    log_info(nuevo_logger,"INICIANDO CONSOLA");    
	return nuevo_logger;
}

t_config* iniciar_config(void){
	t_config* nuevo_config;
    if((nuevo_config=config_create("./consola.config")) == NULL){
        printf("No se creo el config \n");
        exit(2);
    }
	return nuevo_config;
}

void terminar_programa(t_log* logger, t_csl_cfg* my_configuracion, t_config* config){ 
    log_destroy(logger);
    config_destroy(config);
    my_configuracion_free(my_configuracion);
}

void my_configuracion_free(t_csl_cfg* my_configuracion){
    free(my_configuracion->ip_kernel);
    free(my_configuracion->puerto_kernel);
    free(my_configuracion);
}

void leer_archivo_y_cargar_lista(char* path,t_list *instruciones){
    FILE* instrucciones = fopen(path,"r");
    
    if (!instrucciones){
        printf("No se pudo abrir el archivo de instrucciones.\n");
        exit(EXIT_FAILURE);
    }

    char* contents=NULL;
    size_t len =0;
    printf("Leyendo instrucciones del txt:\n");
    while (getline(&contents, &len, instrucciones) != -1){
        printf("%s \n", contents); //Solo para verificar visualmente
        obtenerInstruccion(contents,instruciones);
    }
    printf("\n");
    fclose(instrucciones);
    free(contents);
}

void obtenerInstruccion(char *contents,t_list *instruciones){
    char delimitador[] = " ";
    char **token = string_split(contents,delimitador); //["no op","5",null]
    int can_arg = cantidad_argumentos(token);

    char *operaciones = token[0];
    op_operate op_obtenida = obtenerOperacion(operaciones);

    t_instruct *una_instruccion = malloc(sizeof(t_instruct));
    una_instruccion->operacion=op_obtenida;

    if(op_obtenida == NO_OP){
        int cantidad_de_veces = atoi(token[1]);
        insertar_varias_veces(instruciones,op_obtenida,cantidad_de_veces);
        free(una_instruccion);
    }else if(can_arg==1){ //cantidad de argumentos es 0
        una_instruccion->prm_tipo = obtener_no_parametro();
        list_add(instruciones, una_instruccion);
    }else if(can_arg==2){; //cantidad de argumentos es 1
        una_instruccion->prm_tipo = obtener_one_parametro(token);
        list_add(instruciones, una_instruccion);
    }else if(can_arg==3){ //cantidad de argumentos es 2
        una_instruccion->prm_tipo = obtener_two_parametro(token);
        list_add(instruciones, una_instruccion);
    }else{
        log_error(logger, "Error en la instancia de los tipos de parametros");
    }
}

int cantidad_argumentos(char **token){
    char **ptr;
    int cantidad=0;
    for(ptr = token;*ptr != NULL;ptr++){
        cantidad++;
    }
    return cantidad;
}

t_no_parms* obtener_no_parametro(void){
    t_no_parms* parametro0 = malloc(sizeof(t_no_parms));
    parametro0->tipo=0;
    return parametro0;
}

t_one_parms* obtener_one_parametro(char **token){
    t_one_parms* parametro1 = malloc(sizeof(t_one_parms));
    parametro1->arg1= atoi(token[1]);
    parametro1->tipo=UNO;
    return parametro1;
}

t_two_parms* obtener_two_parametro(char **token){
    t_two_parms* parametro2 = malloc(sizeof(t_two_parms));
    parametro2->arg1= atoi(token[1]);
    parametro2->arg2= atoi(token[2]);
    parametro2->tipo=DOS;
    return parametro2;
}

op_operate obtenerOperacion(char *token){

    if(strcmp(token,"NO_OP")==0){
        return NO_OP;
    }else if(strcmp(token,"I/O")==0){
        return I_O;
    }else if(strcmp(token,"READ")==0){
        return READ;
    }else if(strcmp(token,"WRITE")==0){
        return WRITE;
    }else if(strcmp(token,"COPY")==0){
        return COPY;
    }else if(strcmp(token,"EXIT")==0){
        return EXIT;
    }else{
        printf("booooom \n");
        return EXIT;
    }   
}

void insertar_varias_veces(t_list* instruciones,op_operate op_obtenida,int n){
    for(int i=0;i<n;i++){
        t_instruct *una_instruccion = malloc(sizeof(t_instruct));
        una_instruccion->operacion=op_obtenida;
        una_instruccion->prm_tipo = obtener_no_parametro();
        list_add(instruciones, una_instruccion);
    }
}

void mostrarLista(t_instruct *una_instruccion){
    printf("lista: %i \n",una_instruccion->operacion);
}

void leer_archivo_de_configuracion_consola(t_config* config,t_csl_cfg* my_configuracion){
    config = iniciar_config();
    my_configuracion->ip_kernel = config_get_string_value(config,"IP_KERNEL");
    my_configuracion->puerto_kernel = config_get_string_value(config,"PUERTO_KERNEL");
    if(my_configuracion->ip_kernel!=NULL && my_configuracion->puerto_kernel!=NULL){
        log_info(logger, "CONFIGURACION CARGADA");
    } else
        log_error(logger, "Error leyendo configuracion del kernel para la consola.");
}

void iniciar_log(){
    logger = iniciar_logger();
}

int control_de_path(int argc){
     if(argc != 3){
        printf("Se esperan 2 parametros por consola \n");
        exit(-1);
    }
}

t_proceso* generar_proceso(t_list* instrucciones,u_int32_t tamanio){
    t_proceso* un_proceso=malloc(sizeof(t_proceso));
    un_proceso->instrucciones=instrucciones;
    un_proceso->tamanio = tamanio;
}

void enviar_proceso_al_kernel(t_proceso* proceso, t_csl_cfg* my_configuracion, t_log* logger){
    t_paquete* paquete = crear_paquete();

    paquete->codigo_operacion = INICIAR PROCESO;

    printf("El tamanio del proceso es de: %i \n",proceso->tamanio);

    agregar_entero_a_paquete(paquete,proceso->tamanio);
    int cantidad_de_elementos = list_size(proceso->instrucciones);
    printf("La cantidad de elementos en lista son: %i \n",cantidad_de_elementos);
    agregar_entero_a_paquete(paquete,cantidad_de_elementos);

    t_list_iterator* iterator = list_iterator_create(proceso->instrucciones);
    while(list_iterator_has_next(iterator){
        t_instruct* una_instruccion = list_iterator_next(iterator);
        printf("La instruccion es: %i \n",una_instruccion->operacion);
        agregar_entero_a_paquete(paquete,una_instruccion->operacion);
        printf("El tipo de parametro es: %i \n",una_instruccion->prm_tipo->tipo);
        agregar_entero_a_paquete(paquete,una_instruccion->prm_tipo->tipo);
        if(una_instruccion->prm_tipo->tipo==UNO){
            printf("El primer parametro es: %i \n",una_instruccion->prm_tipo->arg1);
            agregar_entero_a_paquete(paquete,una_instruccion->prm_tipo->arg1);
        }else if(una_instruccion->prm_tipo->tipo==DOS){
            printf("El primer parametro es: %i \n",una_instruccion->prm_tipo->arg1);
            agregar_entero_a_paquete(paquete,una_instruccion->prm_tipo->arg1);
            printf("El segundo parametro es: %i \n",una_instruccion->prm_tipo->arg2);
            agregar_entero_a_paquete(paquete,una_instruccion->prm_tipo->arg2);
        }
    }

    list_iterator_destroy(iterator);

    int conexion = crear_conexion(logger, "Estableciendo conexion con kernel", my_configuracion->ip_kernel, my_configuracion->puerto_kernel);
    enviar_paquete(paquete,conexion);

    eliminar_paquete(paquete);
    close(conexion);
}
