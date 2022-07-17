#include <valgrind/valgrind.h>
#include <main.h>
#include <signal.h>

void funcion(char *str, int i) {
    VALGRIND_PRINTF_BACKTRACE("%s: %d\n", str, i);
}

void sighandler(int s) {
    cerrar_programa(logger);
    exit(0);
}

int main(int argc, char* argv[]) {
	u_int32_t ID=0;
	iniciar_log(); //Inicio logger

    config = iniciar_config(); //Inicio config
    t_krl_cfg* my_configuracion;
	leer_archivo_de_configuracion_kernel(config, my_configuracion); //Cargo config en my_configuracion
	
	//Instanciar colas de procesos usando struct de t_colas y una funcion de crear_colas
	t_colas* cola_de_procesos = crear_colas();

	t_pcb* procesos_ejecutando;
	procesos_ejecutando = asignar_grado_de_multiprogramacion();
	
	/*
	//Lista para simular
	
	t_list* l_process;
	t_list* pcbs;
	l_process = list_create();
	lista_falsa_para_pruebas(l_process);

	list_map(l_process, mostrarLista);
	pcbs = list_map(l_process, crear_pcb);
	t_proceso *proceso = list_get(l_process,0);
	t_instruct *instruccion = list_get(proceso->instrucciones,2);
	t_pcb *un_pcb = list_get(pcbs,1); 
	printf("** %i \n",un_pcb->id);
	*/

	//trigger kernel
	//iniciar_kernel();


	signal(SIGINT, sighandler);
	//Inicia servidor para futuros clientes
    int fd_kernel = iniciar_servidor(logger, "KERNEL", my_configuracion->puerto_memoria, my_configuracion->puerto_escucha); //fd = file descriptor
	
	manejo_de_conexiones(fd_kernel, colas->cola_new, my_configuracion, logger);

	liberar_memoria(logger, config, my_configuracion, fd_kernel);
	free(colas);
	
	return 0;	
}


