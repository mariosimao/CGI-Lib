/*
 +------------------------------------------+
 |               CGI LIBRARY                |
 +------------------------------------------+
 | Created by: Mario Simao                  |
 |                                          |
 | Universidade Federal do Rio de Janeiro   |
 | Tab size: 4                              |
 +------------------------------------------+
 */

/* Error Type */
typedef enum
{
	cgiOk,
	cgiGetPostNull,
	cgiGetPostBoth,
	cgiNameNotFound,
} cgiError;


/*
 +------------------------------------------+
 |               CGI LIBRARY                |
 +------------------------------------------+
 | Created by: Mario Simao                  |
 |                                          |
 | Universidade Federal do Rio de Janeiro   |
 +------------------------------------------+
 */
cgiError
cgiGetQueryString (char *name, char* value);
