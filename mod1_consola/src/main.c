#include <valgrind/valgrind.h>
#include <main.h> 

void funcion(char *str, int i) {
    VALGRIND_PRINTF_BACKTRACE("%s: %d\n", str, i);
}

int main(int argc, char* argv[]) { //path = "instrucciones.txt 7";
    t_csl_cfg* my_configuracion;
    u_int32_t* tamanio = argv[2];
    t_config* config;
    t_list* instrucciones;
    t_proceso* proceso;

    //Inicio logger, cargo configuracion y controlo parametros del path
    iniciar_log();
    leer_archivo_de_configuracion_consola(config,my_configuracion);
    control_de_path(argc);

    //Lista con las instrucciones
    instrucciones = list_create();
    leer_archivo_y_cargar_lista(argv[1],instrucciones);

    //Funcion para crear el t_proceso
    proceso = generar_proceso(instrucciones,tamanio);

    //Envio el proceso al kernel
    enviar_proceso_al_kernel(proceso,my_configuracion, logger);

    /*COSAS DE PRUEBA
    list_map(instrucciones, mostrarLista);
    t_instruct *instruccion = list_get(instrucciones,8);
    
    t_one_parms *parametro = instruccion->prm_tipo;
    printf("****** %i \n",parametro->tipo);
    printf("****** %i \n",parametro->arg1);
    //printf("****** %i \n",parametro->arg2);
    
    //PRUEBA
    int fd_kernel=0;  
    mensajePrueba(logger, my_configuracion.ip_kernel, my_configuracion.puerto_kernel, fd_kernel);
    */

    list_destroy(instrucciones);
    terminar_programa(logger, my_configuracion, config);

    return 0;
}

void mensajePrueba(t_log* logger, char *ip, char* puerto, int fd_kernel){
    fd_kernel = crear_conexion(logger, "KERNEL", ip, puerto); //Creamos la conexion con el kernel
    enviar_mensaje("Conexion completada", fd_kernel); //Enviamos mensaje desde consola a kernel
}