#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {

	char *filename = "/home/c2467/passwd";

	if (argc != 2) {
		perror("usage: ./myid <username>");
		return 1;
	}
	FILE *file;
	int line = 0;
	char str[BUFSIZE];

	file = fopen(filename, "r");
	if (file == NULL) {
		perror("error opening passwd");
		return 1;
	}
	while (fgets(str, BUFSIZE, file) != NULL) {
		if (strstr(str, argv[1]) != NULL) {

			char *array[7];
			char *token;
			int i = 0;

			token = strtok(str, ":");
			while (token != NULL) {
				array[i] = token;
				token = strtok(NULL, ":");
				i++;
			}
			if (i > 3) {
				char *ptr1, *ptr2, *ptr3;

				strtoul(array[2], &ptr1, 10);
				strtoul(array[3], &ptr2, 10);
				strtoul("123", &ptr3, 10);

				if (strcmp(array[0], argv[1]) == 0 && strcmp(ptr1, ptr3) == 0 && strcmp(ptr2, ptr3) == 0) {
					printf("uid=%s gid=%s\n", array[2], array[3]);
					break;
				}
			}
		}
		line++;
	}

	if (file) {
		fclose(file);
	}

	return 0;
}