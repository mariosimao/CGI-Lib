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
	cgiGetFormValueGetPostNull,
	cgiGetFormValueQueryInvalidFormat,
	cgiGetFormValueEmpty,
	cgiGetFormValueNameNotFound,
	cgiGetFormValueIntegerInvalid,
	cgiGetFormValueDoubleInvalid,
} cgiError;


/* 01. GET FORM VALUE
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
 * cgiGetFormValueGetPostNull					Did not received any form query data.
 * cgiGetFormValueQueryInvalidFormat			Query in invalid format.
 * cgiGetFormValueEmpty							Input value is empty.
 * cgiGetFormValueNameNotFound					Did not found form input name.
 */
cgiError
CgiGetFormValue (char *name, char* value);

/* 02. GET FORM VALUE INTEGER
 *
 * Description:
 * Gets a doulbe value from a given form input.
 * Suports GET and POST methods.
 * Converts '+' to spaces.
 * Converts hex (e.g. E1) to string.
 *
 * Arguments:
 * char * - input name (same as in HTML form) [I]
 * int *  - integer value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetFormValue errors						All errons in "cgiGetFormValue" function.
 * cgiGetFormValueIntegerInvalid				Value is not an integer.
 */
cgiError
CgiGetFormValueInteger (char *name, int *value);

/* 03. GET FORM VALUE DOUBLE
 *
 * Description:
 * Gets an integer value from a given form input.
 * Suports GET and POST methods.
 * Converts '+' to spaces.
 * Converts hex (e.g. E1) to string.
 * Converts ',' to '.'.
 *
 * Arguments:
 * char *    - input name (same as in HTML form) [I]
 * double *  - double value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetFormValue errors						All errons in "cgiGetFormValue" function.
 * cgiGetFormValueDoubleInvalid					Value is not a double.
 */
cgiError
CgiGetFormValueDouble (char *name, double *value);
