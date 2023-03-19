/* After each of the calls to write() in the following code, explain what the content of
the output file would be, and why:
fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
fd2 = dup(fd1);
fd3 = open(file, O_RDWR);
write(fd1, "Hello,", 6);
write(fd2, "world", 6);
lseek(fd2, 0, SEEK_SET);
write(fd1, "HELLO,", 6);
write(fd3, "Gidday", 6); */

#include <fcntl.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#define ARGC 2


int
main(int argc, char *argv[])
{
	int fd1, fd2, fd3;
	char *file;

	if (argc != ARGC) usageErr("%s file\n", argv[0]);

	file = argv[1];
	fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	fd2 = dup(fd1);
	fd3 = open(file, O_RDWR);

        /* Open a file, create it if it does not exist or truncate it otherwise
         * and write to it the string "Hello," */
        write(fd1, "Hello,", 6);

        /* fd1 and fd2 shares the same file description, thus the same offset.
         * As a result, the string "world" will be appended */
        write(fd2, "world", 6);

        /* fd1 and fd2 shares the same file description, thus the same offset.
         * As a result, the string "Hello" will be replaced by "HELLO" */
	lseek(fd2, 0, SEEK_SET);
	write(fd1, "HELLO,", 6);

        /* fd3 has its own file description. It has not been changed since it
         * has been open and thus has still the value "0". As a result, the
         * first 6 bytes will be replaced by "Gidday". */
        write(fd3, "Gidday", 6);

	if (close(fd1) == -1 || close(fd2) == -1 || close(fd3) == -1)
		errExit("close");


	return 0;
}
