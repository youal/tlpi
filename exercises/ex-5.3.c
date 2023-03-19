/* This exercise is designed to demonstrate why the atomicity guaranteed by
opening a file with the O_APPEND flag is necessary. Write a program that takes
up to three command-line arguments:

$ atomic_append filename num-bytes [x]

This file should open the specified filename (creating it if necessary) and
append num-bytes bytes to the file by using write() to write a byte at a time.
By default, the program should open the file with the O_APPEND flag, but if a
third command-line argument (x) is supplied, then the O_APPEND flag should be
omitted, and instead the program should perform an lseek(fd, 0, SEEK_END) call
before each write(). Run two instances of this program at the same time without
the x argument to write 1 million bytes to the same file:

$ atomic_append f1 1000000 & atomic_append f1 1000000

Repeat the same steps, writing to a different file, but this time specifying the
x argument:

$ atomic_append f2 1000000 x & atomic_append f2 1000000 x

List the sizes of the files f1 and f2 using ls –l and explain the difference.

Result:
f1: 2000000
f2: 1000562

f1 has the expected size while f2 has roughly the same size as if only one
process was executed. This is because having two system calls (lseek and write)
breaks the atomicity of the process. Thus, roughly 50% of the time, one of the
process execute an lseek before the other one is able to write. As a
consequence, when that process writes, it overwrite what was written by the
previous one.
*/

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "tlpi_hdr.h"

#define MIN_ARGC 3
#define MAX_ARGC 4


int
main(int argc, char *argv[])
{
	if (argc < MIN_ARGC || argc > MAX_ARGC || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname num-bytes [x]\n", argv[0]);

	char *f = argv[1];
	mode_t file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int fd;

	int flags = O_RDWR | O_CREAT;
	flags = argc == MAX_ARGC ? flags : flags | O_APPEND;
	fd = open(f, flags, file_perms);
	if (fd == -1)
		errExit("open");

	long num_bytes = strtol(argv[2], NULL, 10);
	for (long i = 0; i < num_bytes; i++) {
		bool use_seek = argc == MAX_ARGC ? true : false;
		if (use_seek)
			if (lseek(fd, 0, SEEK_END) == -1)
				errExit("lseek");

		if (write(fd, "x", 1) == -1)
			errExit("write");
	}

	if (close(fd) == -1)
                errExit("close");


	return 0;
}
