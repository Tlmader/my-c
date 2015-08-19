#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("try: ./mycp <infile> <outfile>\n");
		return 1;
	}

	int in, out;

	in = open(argv[1], O_RDONLY);
	if (in == -1) {
		perror("failed to open input file");
		return 1;
	}

	out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (out == -1) {
		perror("failed to open output file");
		return 1;
	}

	char *buf = malloc(BUFSIZE);
	if (buf == NULL) {
		perror("malloc failed");
		return 1;
	}

	ssize_t rcount, wcount, wtemp;
	while ((rcount = read(in, buf, BUFSIZE))) {
		if (rcount == -1) {
			perror("read failed");
			return -1;
		}

		wcount = 0;
		do {
			wtemp = write(out, buf + wcount, rcount - wcount);
			if (wtemp == -1) {
				perror("write failed");
				return -1;
			}
			wcount += wtemp;
		} while (wcount < rcount);
	}

	int ret;
	ret = close(in);
	if (ret == -1) {
		perror("failed to close input file");
		return 1;
	}

	ret = close(out);
	if (ret == -1) {
		perror("failed to close output file");
		return 1;
	}

	free(buf);
	return 0;
}