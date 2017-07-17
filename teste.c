#include "cgiLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (void)
{
	char age [1024 + 1];
	char name [1024 + 1];
	cgiError erro1, erro2;

	erro1 = cgiGetFormString ("name", name);
	erro2 = cgiGetFormString ("age", age);

	printf ("Content-Type: text/html\n\n");

	printf ("<pre>");
	printf ("Name: [%s] - %i\n", name, erro1);
	printf (" Age: [%s] - %i\n", age, erro2);
	printf ("</pre>");

	return 0;
}
