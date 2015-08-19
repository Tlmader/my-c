#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

	struct stat mystat;

	if (argc > 1) {

		if (argv[1][0] == '-' && argc == 3) {

			if (argv[1][1] == 's' && argv[2][0] != '-') {
				int ret = stat(argv[2], &mystat);
				if (ret == -1) {
					perror("stat");
					return 1;
				}
				printf("%llu\n\n", (unsigned long long) mystat.st_size);
				return 0;
			}
			else if (argv[1][1] == 'i' && argv[2][0] != '-') {
				int ret = stat(argv[2], &mystat);
				if (ret == -1) {
					perror("stat");
					return 1;
				}
				printf("%llu\n\n", (unsigned long long) mystat.st_ino);
				return 0;
			}
			else if (argv[1][1] == 'm' && argv[2][0] != '-') {
				int ret = stat(argv[2], &mystat);
				if (ret == -1) {
					perror("stat");
					return 1;
				}
				printf("%04o\n\n", (unsigned int)mystat.st_mode & 07777);
				return 0;
			}
		}
		else if (argv[1][0] != '-' && argc == 2) {
			int ret = stat(argv[1], &mystat);
			if (ret == -1) {
				perror("stat");
				return 1;
			}
			printf("size: %llu\ninode: %04o\nmode: %llu\n\n", (unsigned long long) mystat.st_size, (unsigned int)mystat.st_ino, (unsigned long long) mystat.st_mode);
			return 0;
		}
	}
	printf("usage: ./mystat [options] [filename]\n\n-s   prints: size in bytes\n - i   prints : inode number\n - m   prints : mode\n\n");
	return 0;
}