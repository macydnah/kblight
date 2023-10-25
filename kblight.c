#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSPATH "/sys/devices/platform/sony-laptop/kbd_backlight"

int main(int argc, char *argv[])
{

	/* Declarando variables y punteros de fichero. *
	 * Inicializando variables.		       */
	int state, automatic=1, on=1, off=1, check_state=1;
	FILE *fpr, *fpw;

	if(argc == 2) {
	    automatic = strcmp("-auto", argv[1]);
	    on = strcmp("-on", argv[1]);
	    off = strcmp("-off", argv[1]);
	    check_state = strcmp("-s", argv[1]); }
	else if(argc > 2) {
	    printf("Error! too many arguments\n");
	    exit(1); }

	// Inicializando puntero en modo lectura.
	fpr = fopen(SYSPATH, "r");
	if(fpr == NULL) {
	    printf("Error! opening file\n");
	    exit(1); }

	/* Guardando valor de estado en variable state *
	 * antes de abrir fichero en modo escritura    *
	 * para que no se sobreescriba.		       */
	fscanf(fpr, "%d", &state);

	// Inicializando puntero en modo escritura.
	fpw = fopen(SYSPATH, "w");
	if(fpw == NULL) {
	    printf("Error! can't write to file\n");
	    exit(1); }

	// Los meros meros.
	if(argc == 1 || automatic == 0) {
		if(state == 1) { fprintf(fpw, "%d\n", 0); }
	   else if(state == -1 || state == 0 || state == 2) { fprintf(fpw, "%d\n", 1); }
	}

	else if(on == 0)  { fprintf(fpw, "%d\n", 2); }
	else if(off == 0) { fprintf(fpw, "%d\n", 0); }

	else if(check_state == 0) {
		if(state == 0) { printf("Actual state is: off\n");  }
		if(state == 1) { printf("Actual state is: auto\n"); }
		if(state == 2) { printf("Actual state is: on\n");   }
	}

	else { printf("Error! invalid argument\n"); }

	// Cerrando ficheros.
	fclose(fpw);
	fclose(fpr);

	return 0;
}
