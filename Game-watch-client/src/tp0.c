/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void){
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	logger = iniciar_logger();
	config = leer_config();

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	//antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, "Lei la IP %s y puerto %s\n", ip, puerto);

	conexion = crear_conexion(ip, puerto);
	log_info(logger, "Se realizo la conexion");

	char * mensaje = "mensaje de prueba";
	enviar_mensaje(mensaje, conexion);
	log_info(logger, "Se envio un mensaje");

	char * mensajeDevuelto = recibir_mensaje(conexion);
	log_info(logger, mensajeDevuelto);
	free(mensajeDevuelto);

	log_info(logger, "Se termino el programa");

	terminar_programa(conexion, logger, config);
}

/* CREAMOS LA FUNCION INICIAR_LOGGER QUE RECIBE: PATH, NOMBRE DEL ARCHIVO A CREAR, 1 (guardar en archivo e
imprimir por consola o 0 (guardar en archivo), LOG_LEVEL_INFO*/

t_log* iniciar_logger(void){
	t_log* logger;
	logger = log_create("/home/utnso/workspace/tp0-2020-1c-UTNSO/Game-watch-client/tp0.log", "tp0", 1, LOG_LEVEL_INFO);
	if(logger == NULL){
		printf("No pude iniciar el logger\n");
		exit(1);
	}
	log_info(logger, "Inicio log");
	return logger;
}

t_config * leer_config(void){
	t_config * config;
	config = config_create("/home/utnso/workspace/tp0-2020-1c-UTNSO/Game-watch-client/tp0.config");
	if(config== NULL){
		printf("No pude leer la config\n");
		exit(2);
	}
	return config;

}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config){
	if(logger != NULL){
		log_destroy(logger);
	}

	if(config != NULL){
		config_destroy(config);
		}

	liberar_conexion(conexion);
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}

//free NO asigna el valor NULL a los punteros que libera, pero es buena practica asignarselo a tenerlo apuntando a basura
