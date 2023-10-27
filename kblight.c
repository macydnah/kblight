#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSPATH "/sys/devices/platform/sony-laptop/kbd_backlight"

int main(int argc, char *argv[])
{

	// Declarando e inicializando variables.
	unsigned short int state, automatic=1, on=1, off=1, check_state=1;
	FILE *fp;

	if(argc == 2) {
	    automatic = strcmp("-auto", argv[1]);
	    on = strcmp("-on", argv[1]);
	    off = strcmp("-off", argv[1]);
	    check_state = strcmp("-s", argv[1]); }
	else if(argc > 2) { printf("Error! too many arguments\n"); exit(1); }

	// Declarando e inicializando puntero de fichero.
	if((fp = fopen(SYSPATH,"r")) == NULL) { printf("Error! reading file\n"); exit(1); }

	// Inicializando variable state con valor de estado.
	fscanf(fp, "%hu", &state); fclose(fp);

	// Revisando estado.
	if(check_state == 0) {
		if(state == 0) { printf("Actual state is: off\n");  }
		if(state == 1) { printf("Actual state is: auto\n"); }
		if(state == 2) { printf("Actual state is: on\n");   }
		exit(EXIT_SUCCESS);
	}

	// Inicializando puntero en modo escritura.
	if((fp = fopen(SYSPATH,"w")) == NULL) { printf("Error! writing file\n"); exit(1); }

	// Los meros meros.
	if(argc == 1 || automatic == 0) {
		if(state == 1) { fprintf(fp, "%hu\n", 0); }
	   else if(state == -1 || state == 0 || state == 2) { fprintf(fp, "%hu\n", 1); }
	}

	else if(on == 0)  { fprintf(fp, "%hu\n", 2); }
	else if(off == 0) { fprintf(fp, "%hu\n", 0); }

	else { printf("Error! invalid argument\n"); }

	// Cerrando fichero.
	fclose(fp);

	return 0;
}
