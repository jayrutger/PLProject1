#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("a1","r");
	if(fp == NULL){
		printf("fuck");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line,&len,fp)) != -1) {
		printf("Retrieved line of length %zu:\n", read);
		
		char line2 = line[0];
		//printf("%c",line2);
		for (int i=0;line[i] != '\0';i++)
		{
			printf("%c",line[i]);
		}
		//printf("%s",line);


	}

	fclose(fp);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}
