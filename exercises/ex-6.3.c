/* Implement setenv() and unsetenv() using getenv(), putenv(), and, where necessary,
code that directly modifies environ. Your version of unsetenv() should check to see
whether there are multiple definitions of an environment variable, and remove
them all (which is what the glibc version of unsetenv() does). */


#include "tlpi_hdr.h"


/* return zero on success, or -1 on error, */
int
my_setenv(const char *name, const char *value, int overwrite);

int
my_unsetenv(const char *name);


int
my_setenv(const char *name, const char *value, int overwrite)
{
	char *cv;
	char *v = malloc(strlen(name) + strlen("=") + strlen(value) + 1);

	cv = getenv(name);
	if (cv ==  NULL || overwrite == 1) {
		strcpy(v, name);
		strcat(v, "=");
		strcat(v, value);

		return putenv(v) == 0 ? 0 : -1;
	}

	return 0;
}


int
my_unsetenv(const char *name)
{
	return putenv(name) == 0 ? 0 : -1;
}


int
main(int argc, char *argv[])
{
	const char *v = "x";
	char *x;

	if (my_unsetenv(v) == -1) errExit("my_unsetenv");
	if (my_setenv(v, "foo", 0) == -1) errExit("my_setenv");

	x = getenv(v);
	if (x != NULL) printf("%s\n", x);
	else puts("NULL value");

	if (my_setenv(v, "bar", 1) == -1) errExit("my_setenv overwrite");
	x = getenv(v);
	if (x != NULL) printf("%s\n", x);
	else puts("NULL value");

	if (my_setenv(v, "bam", 0) == -1) errExit("my_setenv overwrite");
	x = getenv(v);
	if (x != NULL) printf("%s\n", x);
	else puts("NULL value");

	if (my_unsetenv(v) == -1) errExit("my_unsetenv");
	if (my_setenv(v, "baz", 0) == -1) errExit("my_setenv overwrite");
	x = getenv(v);
	if (x != NULL) printf("%s\n", x);
	else puts("NULL value");


	return 0;
}
