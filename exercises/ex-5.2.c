/* Write a program that opens an existing file for writing with the O_APPEND
flag, and then seeks to the beginning of the file before writing some data.
Where does the data appear in the file? Why?

Data will be written at the end since  "O_APPEND" means that "Writes are always
appended to end of file" */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "tlpi_hdr.h"
#define WRITE_SIZE 4


int
main(int argc, char *argv[])
{
	int fd;
	char * f;
	char s[] = "bar";
	off_t offset;
	ssize_t written;

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname\n", argv[0]);

	f = argv[1];
	fd = open(f, O_RDWR | O_APPEND);
	if (fd == -1)
		errExit("open");

	offset = 0;
	if (lseek(fd, offset, SEEK_SET) == -1)
                errExit("lseek");

	written = write(fd, s, WRITE_SIZE);
	if (written != WRITE_SIZE)
		errExit("Wrote %ld bytes", (long) written);

	if (close(fd) == -1)
                errExit("close");

	return 0;
}
