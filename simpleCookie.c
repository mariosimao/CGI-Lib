#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MUST include the library */
#include "cgiLib.h"

int
main (void)
{
	char value [CGI_INPUT_VALUE_MAX_LENGTH + 1];
	char action [CGI_INPUT_VALUE_MAX_LENGTH + 1];
	cgiError erro = cgiOk;

	CgiGetFormValue ("action", action);

	if (strcmp (action, "get") == 0)
		erro = CgiGetCookie ("id", value);

	/* This 2 functions are mandatory in your CGI.
	 * As the name tells, they begin and end the
	 * HTTP header.
	 *
	 * If you want to use cookies, the cookie functions
	 * MUST be used between "CgiBeginHttpHeader" and
	 * "CgiEndHttpHeader" functions.*/
	CgiBeginHttpHeader ();

	/* Deletes cookie */
	if (strcmp (action, "delete") == 0)
	{
		CgiDeleteCookie ("id", "/");
	}

	/* Sets cookie */
	if (strcmp (action, "set") == 0)
	{
		CgiSetCookie ("id", "12345abcde", 24*3600, "/");
	}

	CgiEndHttpHeader ();

	/* You need to use "printf" in your HTML code
	 * The TABs and line breakers ('\n') inside every
	 * "printf" are only for maintain the code human
	 * readable in the browser.*/
	printf ("<html>\n");
	printf ("	<head>\n");
	printf ("		<title>\n");
	printf ("			Simple Cookie\n");
	printf ("		</title>\n");
	printf ("	</head>\n");
	printf ("	<body>\n");
	printf ("		<h2>Simple Cookie</h2>\n");
	printf ("		<p>Use <b>Get</b> to see the test cookie.</p>\n");
	printf ("		<p>Use <b>Set</b> to create the test cookie.</p>\n");
	printf ("		<p>Use <b>Delete</b> to delete the test cookie.</p>\n");
	printf ("		<form action=simpleCookie.cgi>\n");
	printf ("			<input type=hidden name=action value=get>\n");
	printf ("			<input type=submit value=Get>\n");
	printf ("		</form>\n");
	printf ("		<form action=simpleCookie.cgi>\n");
	printf ("			<input type=hidden name=action value=set>\n");
	printf ("			<input type=submit value=Set>\n");
	printf ("		</form>\n");
	printf ("		<form action=simpleCookie.cgi>\n");
	printf ("			<input type=hidden name=action value=delete>\n");
	printf ("			<input type=submit value=Delete>\n");
	printf ("		</form>\n");

	/* GET */
	if (strcmp (action, "get") == 0)
	{
		if (erro == cgiOk)
			printf ("Cookie Value: [%s]\n", value);
		else
			printf ("Cookie not found.\n");
	}

	/* SET */
	if (strcmp (action, "set") == 0)
	{
		printf ("Cookie set!\n");
	}

	/* DELETE */
	if (strcmp (action, "delete") == 0)
	{
		printf ("Cookie deleted!\n");
	}

	printf ("	</body>\n");
	printf ("</html>\n");

	return 0;
}
