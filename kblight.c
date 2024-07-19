#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SYSPATH "/sys/devices/platform/sony-laptop/kbd_backlight"

static short int opt, mode;
static FILE *fp;

void writing()
{
	if((fp = fopen(SYSPATH,"w")) == NULL) {
		fprintf(stderr, "Error! writing file.\n");
		exit(EXIT_FAILURE);
	}
}

void toggle()
{
	if(mode == 1) fprintf(fp, "%hd\n", 0);
	fprintf(fp, "%hd\n", 1);
	fclose(fp);
}

void estado()
{
	if(mode == 0) printf("Actual active mode is: off\n");
	else if(mode == 1) printf("Actual active mode is: auto\n");
	else if(mode == 2) printf("Actual active mode is: on\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
	if(argc > 2) {
		fprintf(stderr, "Error! too many arguments.\n");
		exit(EXIT_FAILURE);
	}

	if((fp = fopen(SYSPATH,"r")) == NULL) {
		fprintf(stderr, "Error! reading file.\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(fp, "%hd", &mode);
	fclose(fp);

	while ((opt = getopt(argc, argv, "aofs")) != -1) {
	    switch (opt) {
	    case 'a': writing(); toggle(); break;
	    case 'o': writing(); fprintf(fp, "%hd\n", 2); break;
	    case 'f': writing(); fprintf(fp, "%hd\n", 0); break;
	    case 's': estado();
	    }
	}

	writing();
	toggle();
	return 0;
}
