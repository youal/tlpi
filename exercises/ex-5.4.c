/* Implement dup() and dup2() using fcntl() and, where necessary, close(). (You may
ignore the fact that dup2() and fcntl() return different errno values for some error
cases.) For dup2(), remember to handle the special case where oldfd equals newfd. In
this case, you should check whether oldfd is valid, which can be done by, for example,
checking if fcntl(oldfd, F_GETFL) succeeds. If oldfd is not valid, then the function
should return –1 with errno set to EBADF. */

#include <fcntl.h>
#include <stdio.h>

#include "tlpi_hdr.h"

#define ARGC 2
#define BUF_SIZE 1024

int
main(int argc, char *argv[])
{
	char *f;
	int fd0, fd1;
	char buf[BUF_SIZE];
	ssize_t bytes_read;

	if (argc != ARGC) usageErr("%s file\n", argv[0]);

	f = argv[1];
	fd0 = open(f, O_RDONLY);
	if (fd0 == -1) errExit("open");

	fd1 = fcntl(fd0, F_DUPFD, 0);
	if (fd1 == -1) errExit("fcntl");

	bytes_read = read(fd1, buf, BUF_SIZE);
	if (bytes_read == -1) errExit("read");
	printf("%s\n", buf);

	if (close(fd0) == -1 || close(fd1) == -1)
		errExit("close");

	return 0;
}
