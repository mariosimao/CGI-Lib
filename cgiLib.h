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
	cgiGetFormValueInvalidMethod,
	cgiGetFormValueQueryInvalidFormat,
	cgiGetFormValueEmpty,
	cgiGetFormValueNameNotFound,
	cgiGetFormValueIntegerInvalid,
	cgiGetFormValueDoubleInvalid,
	cgiSetCookieNameNull,
	cgiSetCookieNameEmpty,
	cgiSetCookieValueNull,
	cgiSetCookieValueEmpty,
	cgiGetFormValuePostNull,
} cgiError;


/* 01. GET FORM VALUE
 *
 * Description:
 * Gets a value from a given form input.
 * Supports GET and POST methods.
 * Converts '+' to spaces.
 * Converts hex (e.g. E1) to string.
 *
 * Arguments:
 * char * - input name (same as in HTML form) [I]
 * char * - input value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetFormValueInvalidMethod					Did not received any form query data.
 * cgiGetFormValueQueryInvalidFormat			Query in invalid format.
 * cgiGetFormValueEmpty							Input value is empty.
 * cgiGetFormValueNameNotFound					Did not found form input name.
 */
cgiError
CgiGetFormValue (char *name, char* value);

/* 02. GET FORM VALUE INTEGER
 *
 * Description:
 * Gets a integer value from a given form input.
 * Supports GET and POST methods.
 * Converts '+' to spaces.
 * Converts hex (e.g. E1) to string.
 *
 * Arguments:
 * char * - input name (same as in HTML form) [I]
 * int *  - integer value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetFormValue errors						All erros in "cgiGetFormValue" function.
 * cgiGetFormValueIntegerInvalid				Value is not an integer.
 */
cgiError
CgiGetFormValueInteger (char *name, int *value);

/* 03. GET FORM VALUE DOUBLE
 *
 * Description:
 * Gets an double value from a given form input.
 * Supports GET and POST methods.
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
 * cgiGetFormValue errors						All erros in "cgiGetFormValue" function.
 * cgiGetFormValueDoubleInvalid					Value is not a double.
 */
cgiError
CgiGetFormValueDouble (char *name, double *value);

/* 04. BEGIN HTTP HEADER
 *
 * Description:
 * Begins HTTP header with content type set as "text/html"
 *
 * No arguments.
 *
 * Return:
 * cgiOk										Success!
 */
cgiError
CgiBeginHttpHeader (void);

/* 05. END HTTP HEADER
 *
 * Description:
 * Ends HTTP header.
 *
 * No arguments.
 *
 * Return:
 * cgiOk										Success!
 */
cgiError
CgiEndHttpHeader (void);

/* 06. SET COOKIE
 *
 * Description:
 * Sets a cookie.
 * MUST be used between "CgiBeginHttpHeader" and "CgiEndHttpHeader".
 *
 * Arguments:
 * char * - cookie name [I]
 * char * - cookie value [I]
 * int *  - cookie maxAge [I]
 			(use 0 if you do not want to set)
 * char * - path [I]
 			(use NULL if you do not want to set)
 *
 * Return:
 * cgiOk										Success!
 * cgiSetCookieNameNull							Cookie name is NULL
 * cgiSetCookieNameEmpty						Cookie name is empty
 * cgiSetCookieValueNull						Cookie value is NULL
 * cgiSetCookieValueEmpty						Cookie value is empty
 */
cgiError
CgiSetCookie (char *name, char *value, int maxAge, char *path);
