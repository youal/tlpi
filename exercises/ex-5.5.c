/* Write a program to verify that duplicated file descriptors share a file
offset value and open file status flags.

We can see that the offset has been set also for the copied file descriptor by
checking the written file.
*/

#include <fcntl.h>
#include <stdio.h>

#include "tlpi_hdr.h"

#define ARGC 2

int
main(int argc, char *argv[])
{
	char *f;
	int fd0, fd1;
	off_t bytes_shift, new_offset;
	ssize_t written;

	if (argc != ARGC) usageErr("%s file\n", argv[0]);

	f = argv[1];
	fd0 = open(f, O_RDWR);
	if (fd0 == -1) errExit("open");

	fd1 = dup(fd0);
	if (fd1 == -1) errExit("fcntl");

	bytes_shift = 3;
	new_offset = lseek(fd0, bytes_shift, SEEK_SET);
	if (new_offset == -1) errExit("lseek");

	written = write(fd1, "x", 1);
	if (written == -1) errExit("write");

	if (close(fd0) == -1 || close(fd1) == -1)
		errExit("close");

	return 0;
}
