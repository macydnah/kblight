
#include <stdio.h>
#include <stdlib.h>

//#define PATH "/sys/devices/platform/sony-laptop/kbd_backlight"
#define PATH "/home/macydnah/aver"

int main()
{

	/* Declarando variables e
	*  indicadores de fichero */
	int state;
	FILE *fpr, *fpw;

	//
	fpr = fopen(PATH, "r");
	if(fpr == NULL) {
	    printf("Error! opening file\n");
	    exit(1);
	}


	//
	fscanf(fpr, "%d", &state);

	fpw = fopen(PATH, "w");
	if(fpw == NULL) {
	    printf("Error! can't write to file\n");
	    exit(1);
	}

	if(state == 0) {
	    state = 1;
	    fprintf(fpw, "%d\n", state);
	}

	else if(state == 1) {
	    state = 0;
	    fprintf(fpw, "%d\n", state);
	}

	printf("%d\n", state);
	//
	//fscanf(path, "%d", &state);

	//printf("Value of n=%d\n", state);
	fclose(fpr);
	fclose(fpw);

	return 0;
}
