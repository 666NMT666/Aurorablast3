#pragma once
#include <stdio.h>
#include <stdlib.h>

void  my_fopen_in(FILE** fin,char* fname) {
	errno_t error;
	if ((error = fopen_s(fin, fname, "r")) != 0) {
		FILE* fout;
		error = fopen_s(&fout, fname, "w");
		fclose(fout);
		if ((error = fopen_s(fin, fname, "r")) != 0) { exit(0); }
	}
}

void  my_fopen_out(FILE** fout, char* fname) {
	errno_t error;
	if ((error = fopen_s(fout, fname, "w")) != 0) { exit(0); }
}