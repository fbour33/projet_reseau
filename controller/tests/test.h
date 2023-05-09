#ifndef __TEST__
#define __TEST__

#include <assert.h>
#include "../components/server/server_handler.h"

FILE* init_log_f(char* log_dir) {
	FILE *fp;

	strcat(log_dir, "/log.txt");
    fp = fopen(log_dir, "w"); // ouvrir le fichier en mode écriture pour l'effacer
    fclose(fp);

    fp = fopen(log_dir, "a"); // ouvrir le fichier en mode ajout
    if (fp == NULL) {
        perror("fopen() failled");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "------ LOGS ------ \n");
	fflush(fp);

    return fp;
}

#endif //__TEST__