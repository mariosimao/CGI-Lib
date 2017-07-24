#include <stdio.h>
#include <stdlib.h>

/* MUST include the library */
#include "cgiLib.h"

int
main (void)
{
	char name [CGI_INPUT_VALUE_MAX_LENGTH + 1];
	int age;
	double height;

	/* The CgiGetFormValue functions and similar MUST be
	 * used before "CgiBeginHttpHeader" function. */
	CgiGetFormValue ("name", name);
	CgiGetFormValueInteger ("age", &age);
	CgiGetFormValueDouble ("height", &height);

	/* This 2 functions are mandatory in your CGI.
	 * As the name tells, they begin and end the
	 * HTTP header.
	 *
	 * If you want to use cookies, the cookie functions
	 * MUST be used between "CgiBeginHttpHeader" and
	 * "CgiEndHttpHeader" functions.*/
	CgiBeginHttpHeader ();
	CgiEndHttpHeader ();

	/* You need to use "printf" in your HTML code
	 * The TABs and line breakers ('\n') inside every
	 * "printf" are optional and only to mantain the
	 * code human readable in the browser.*/
	printf ("<html>\n");
	printf ("	<head>\n");
	printf ("		<title>\n");
	printf ("			Simple Form CGI\n");
	printf ("		</title>\n");
	printf ("	</head>\n");
	printf ("	<body>\n");
	printf ("		<h2>Simple Form CGI</h2>\n");
	printf ("		<p>Name: %s</p>\n", name);
	printf ("		<p>Age: %i</p>\n", age);
	printf ("		<p>Height: %g</p>\n", height);
	printf ("	</body>\n");
	printf ("</html>\n");

	return 0;
}
