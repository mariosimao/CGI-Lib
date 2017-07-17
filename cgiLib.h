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

#define CGI_QUERY_MAX_LENGTH				1024
#define CGI_INPUT_NAME_MAX_LENGTH			64
#define CGI_INPUT_VALUE_MAX_LENGTH			128

/* Error Type */
typedef enum
{
	cgiOk,
	cgiGetFormStringGetPostNull,
	cgiGetFormStringQueryInvalidFormat,
	cgiGetFormStringNameNotFound,
} cgiError;


/* GET FORM STRING
 *
 * Description:
 * Gets a value from a given form input.
 * Suports GET and POST methods.
 * Converts '+' to spaces.
 * Converts hex (e.g. E1) to string.
 *
 * Arguments:
 * char * - input name (same as in HTML form) [I]
 * char * - input value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetFormStringGetPostNull					Did not received any form query data.
 * cgiGetFormStringQueryInvalidFormat			Query in invalid format.
 * cgiGetFormStringNameNotFound					Did not found form input name.
 */
cgiError
cgiGetFormString (char *name, char* value);
