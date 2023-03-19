/* Implement writev() and writev() using write(), write(), and suitable functions from the
malloc package (Section 7.1.2). */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "tlpi_hdr.h"

#define ARGC 2
#define IOV_SIZE 2


ssize_t
my_writev(int fd, const struct iovec *iov, int iovcnt);


/* IMPROVEMENT:
 * This implementation assumes that *iov.iov_base is of type "char *" while it is of "void *". */
ssize_t
my_writev(int fd, const struct iovec *iov, int iovcnt)
{
	ssize_t bytes_written;

	bytes_written = 0;
	for (int i = 0; i < IOV_SIZE; i++) {
		ssize_t tmp;
		tmp = write(fd, iov[i].iov_base, iov[i].iov_len);
		if (tmp == -1) errExit("my_writev");

		bytes_written += tmp;
	}

	return bytes_written;
}


int
main(int argc, char *argv[])
{
	char *file;
	int fd0;
	struct iovec iov[IOV_SIZE];

	char *v0 = "foo";
	char *v1 = "bar";

	if (argc != ARGC) usageErr("%s file\n", argv[0]);

	file = argv[1];
	fd0 = open(file, O_RDWR | O_CREAT);
	if (fd0 == -1) errExit("open");

	iov[0].iov_base = v0;
	iov[0].iov_len = strlen(v0);
	iov[1].iov_base =  v1;
	iov[1].iov_len = strlen(v1);

	my_writev(fd0, iov, IOV_SIZE);

	if (close(fd0) == -1) errExit("close");


	return 0;
}
