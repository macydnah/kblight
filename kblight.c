#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SYSPATH "/sys/devices/platform/sony-laptop/kbd_backlight"

static short int opt, state;
static FILE *fp;

void writing() { if((fp = fopen(SYSPATH,"w")) == NULL) { printf("Error! writing file\n"); exit(1); } }

void toggle() {
	if(state == 1) { fprintf(fp, "%hd\n", 0); }
	else if(state == -1 || state == 0 || state == 2) { fprintf(fp, "%hd\n", 1); }
	fclose(fp); }

void estado() {
	if(state == 0) { printf("Actual state is: off\n"); }
	else if(state == 1) { printf("Actual state is: auto\n"); }
	else if(state == 2) { printf("Actual state is: on\n"); }
	exit(EXIT_SUCCESS); }

int main(int argc, char *argv[])
{
	if(argc > 2) { printf("Error! too many arguments\n"); exit(1); }

	if((fp = fopen(SYSPATH,"r")) == NULL) { printf("Error! reading file\n"); exit(1); }
	fscanf(fp, "%hd", &state); fclose(fp);

	while ((opt = getopt(argc, argv, "aofs")) != -1) {
	    switch (opt) {
	    case 'a': writing(); toggle(); break;
	    case 'o': writing(); fprintf(fp, "%hd\n", 2); break;
	    case 'f': writing(); fprintf(fp, "%hd\n", 0); break;
	    case 's': estado(); } }

	writing(); toggle(); return 0;
}
