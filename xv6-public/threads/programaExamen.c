/******** mish.c **********/
// gcc -o mish mish.c
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


//Librerias necesarias para que las nuevas implementaciones funcionen
#include <sys/types.h>
#include <sys/wait.h>

 
#define MAX_LINE 80
#define MAX_NUM_ARGS 10
size_t string_parser(char *input, char *word_array[]) {
size_t n = 0;
while (*input) {
while (isspace((unsigned char)*input))
++input;
if (*input) {
word_array[n++] = (char *)input;
while (*input && !isspace((unsigned char)*input))
++input;
*(input) = '\0';
++input;
}
}
word_array[n] = NULL;
return n;
}
 
int main(void) {
  char *args[MAX_NUM_ARGS + 1]; /* command line (of 80) has max of 5 arguments */
  char line[MAX_LINE + 1];
  int should_run = 1;
 
  int i;
 
  while (should_run) {
    printf("mish> ");
    fgets(line,MAX_LINE,stdin);
    line[strcspn(line, "\n")] = '\0';
	// Separamos la línea en palabras separadas por espacio
	// y las guardamos en args
	i = string_parser(line,args); // i contiene el número de argumentos
	  
	  
	//NUESTROS CAMBIOS
	
	/**
	(1) Crear un proceso hijo
	(2) El hijo debe ejecutar execvp para ejecutar al comando tecleado
	(3) Si el programa no existe debe imprimir programa no encontrado
	(4) El proceso padre debe esperar a que el hijo termine, checar función wait
	(5) Debe ejecutar comandos como ls , ps
	(6) Cuando se teclee exit deberá terminar
	**/
	  
	 
	 //Salir cuando se teclee exit (6)
	 if(strcmp(args[0], "exit") ==0){
		 return 1;
	 }
	  
	  int status = 0;
	  
	  //Crear porceso hijo (1)
	  int pid = fork(); 
	  
	  //Esperar a que nuestro hijo acabe, usando funcion wait (4)
	  if(pid){
		waitpid(-1, &status, 0);   
	  }else{
		  //Esto ejecuta execvp  es decir agarramos el comando en la posicion 0 de los argumentos, o sea esto agarra el ls y ps (2)(5)
		  int r = execvp(args[0], &args[0]);
		  
		  
		  //Si el comando a ejecutar no se encuentra lo impirmimos
		  printf("Command not found\n"); 
	  }
	  

    fflush(stdout);
    fflush(stdin);
    line[0] = '\0';
  }
 
  return 0;
}
