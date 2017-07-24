#include "cgiLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
CgiGetFormValue (char *name, char* value)
{
	/* tempQuery and counter NEED the "static" prefix.
	 * Both variables store information from previous
	 * calls of the function. */
	static char tempQuery [CGI_QUERY_MAX_LENGTH + 1];
	static unsigned short counter = 0;
	char query [CGI_QUERY_MAX_LENGTH + 1];
	char dataName [CGI_INPUT_NAME_MAX_LENGTH + 1];
	char dataValue [CGI_INPUT_VALUE_MAX_LENGTH + 1];
	size_t queryIndex, dataIndex;
	char hexString [3];
	char *hexValidation;

	/* EOS (End of String) = '\0'
	 * Query format:  name1=value1&name2=value2&name3=value3
	 * Query example: name=Mario+Simao&age=19
	 * Spaces = '+'
	 * Special characters in HEX format (e.g. %A3)
	 */

	/* Gets GET query */
	if (strcmp (getenv ("REQUEST_METHOD"), "GET") == 0)
	{
		if (counter == 0)
		{
			strcpy (tempQuery, getenv ("QUERY_STRING"));
			counter++;
		}
	}
	/* Gets POST query */
	else if (strcmp (getenv ("REQUEST_METHOD"), "POST") == 0)
	{
		if (counter == 0)
		{
			fgets (tempQuery, CGI_QUERY_MAX_LENGTH + 1, stdin);
			counter++;
		}
	}
	/* Invalid method */
	else
		return cgiGetFormValueInvalidMethod;

	strcpy (query, tempQuery);

	/* Search data name */
	queryIndex = 0;
	while (query [queryIndex] != '\0')
	{
		dataIndex = 0;
		/* Get data name */
		while (query [queryIndex] != '=')
		{
			dataName [dataIndex] = query [queryIndex];
			queryIndex++;
			dataIndex++;
		}
		dataName [dataIndex] = '\0'; /* Inserts EOS */
		queryIndex++; /* Jumps '=' character */

		/* Get data value */
		dataIndex = 0;
		while ((query [queryIndex] != '&') && (query [queryIndex] != '\0'))
		{
			/* Convert '+' to spaces */
			if (query [queryIndex] == '+')
				dataValue [dataIndex] = ' ';
			/* Convert hex (e.g. %E1 = á)*/
			else if (query [queryIndex] == '%')
			{
				/* Get the 2 hex digits */
				hexString [0] = query [queryIndex + 1];
				hexString [1] = query [queryIndex + 2];
				hexString [2] = '\0';

				/* Convertion */
				dataValue [dataIndex] = (char) strtol (hexString, &hexValidation, 16);
				/* Convertion failed */
				if (*hexValidation != '\0')
					return cgiGetFormValueQueryInvalidFormat;
				queryIndex += 2;
			}
			else
				dataValue [dataIndex] = query [queryIndex];
			queryIndex++;
			dataIndex++;
		}
		dataValue [dataIndex] = '\0'; /* Inserts EOS */
		/* Jumps '&' character.
		 * Avoids jumping EOS */
		if (query [queryIndex] == '&')
			queryIndex++;

		/* Checks if data name corresponds */
		if (strcmp (dataName, name) == 0)
		{
			strcpy (value, dataValue);
			if (strlen (value) == 0)
				return cgiGetFormValueEmpty;
			return cgiOk;
		}
	}

	/* If reached this point, did not found the data name */
	return cgiGetFormValueNameNotFound;
}

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
CgiGetFormValueInteger (char *name, int *value)
{
	cgiError result;
	char stringValue [CGI_INPUT_VALUE_MAX_LENGTH];
	char *validation;

	/* Get string */
	result = CgiGetFormValue (name, stringValue);
	if (result != cgiOk)
	{
		value = NULL;
		return result;
	}

	/* Converts to double */
	*value = (int) strtol (stringValue, &validation, 10);
	if (*validation != '\0')
	{
		value = NULL;
		return cgiGetFormValueIntegerInvalid;
	}

	/* Success! */
	return cgiOk;
}

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
CgiGetFormValueDouble (char *name, double *value)
{
	cgiError result;
	char stringValue [CGI_INPUT_VALUE_MAX_LENGTH];
	char *validation;
	size_t index;

	/* Get string */
	result = CgiGetFormValue (name, stringValue);
	if (result != cgiOk)
	{
		value = NULL;
		return result;
	}

	/* Tranform ',' in '.' */
	index = 0;
	while (stringValue [index] != '\0')
	{
		if (stringValue [index] == ',')
			stringValue [index] = '.';
		index++;
	}

	/* Converts to double */
	*value = (double) strtod (stringValue, &validation);
	if (*validation != '\0')
	{
		value = NULL;
		return cgiGetFormValueDoubleInvalid;
	}

	/* Success! */
	return cgiOk;
}

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
CgiBeginHttpHeader (void)
{
	printf ("Content-Type: text/html\n");
	return cgiOk;
}

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
CgiEndHttpHeader (void)
{
	printf ("\n");
	return cgiOk;
}

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
CgiSetCookie (char *name, char *value, int maxAge, char *path)
{
	/* Use of name and value is mandatory */
	if (name == NULL)
		return cgiSetCookieNameNull;
	if (strlen (name) == 0)
		return cgiSetCookieNameEmpty;
	if (value == NULL)
		return cgiSetCookieValueNull;
	if (strlen (value) == 0)
		return cgiSetCookieValueEmpty;

	printf ("Set-Cookie: %s=%s;", name, value);

	/* Max-Age is optional */
	if (maxAge != 0)
		printf ("Max-Age=%d;", maxAge);

	/* Path is optional */
	if (path != NULL)
		printf ("Path=%s", path);

	/* Mandatory line breaker */
	printf ("\n");
	return cgiOk;
}

/* 07. GET COOKIE
 *
 * Description:
 * Gets a cookie value.
 * MUST be used between "CgiBeginHttpHeader" and "CgiEndHttpHeader".
 *
 * Arguments:
 * char * - cookie name [I]
 * char * - cookie value [O]
 *
 * Return:
 * cgiOk										Success!
 * cgiGetCookieNullName							Cookie name is NULL.
 * cgiGetCookieNullValue						Cookie value is NULL.
 * cgiGetCookieNameEmpty						Cookie name is empty.
 * cgiGetCookieNullCookie						Could not list the cookies.
 * cgiGetCookieNameNotFound						Cookie name not found.
 */
cgiError
CgiGetCookie (char *name, char* value)
{
	char *cookie;
	size_t cookieIndex, dataIndex;
	char dataName [CGI_INPUT_NAME_MAX_LENGTH + 1];
	char dataValue [CGI_INPUT_VALUE_MAX_LENGTH + 1];

	if (name == NULL)
		return cgiGetCookieNullName;

	if (strlen (name) == 0)
		return cgiGetCookieNameEmpty;

	if (value == NULL)
		return cgiGetCookieNullValue;

	cookie = getenv("HTTP_COOKIE");
	if (cookie == NULL)
		return cgiGetCookieNullCookie;

	cookieIndex = 0;
	while (cookie [cookieIndex] != '\0')
	{
		dataIndex = 0;
		/* Get data name */
		while (cookie [cookieIndex] != '=')
		{
			dataName [dataIndex] = cookie [cookieIndex];
			cookieIndex++;
			dataIndex++;
		}
		dataName [dataIndex] = '\0'; /* Inserts EOS */
		cookieIndex++; /* Jumps '=' character */

		/* Get data value */
		dataIndex = 0;
		while ((cookie [cookieIndex] != ';') && (cookie [cookieIndex] != '\0'))
		{
			dataValue [dataIndex] = cookie [cookieIndex];
			cookieIndex++;
			dataIndex++;
		}
		dataValue [dataIndex] = '\0'; /* Inserts EOS */
		/* Jumps ';' character.
		 * Avoids jumping EOS */
		if (cookie [cookieIndex] == ';')
			cookieIndex++;
		if (cookie [cookieIndex] == ' ')
			cookieIndex++;

		/* Checks if data name corresponds */
		if (strcmp (dataName, name) == 0)
		{
			strcpy (value, dataValue);
			if (strlen (value) == 0)
				return cgiGetCookieValueEmpty;
			return cgiOk;
		}

	}

	/* If reached this point, did not found the data name */
	return cgiGetCookieNameNotFound;
}

/* 08. DELETE COOKIE
 *
 * Description:
 * Deletes a cookie by setting the value to zero and
 * the expiration time to 01/01/1970.
 * To delete the right cookie, the path must be the
 * same as the path from the cookie you want delete.
 * Otherwise, it will only create a new cookie, with
 * the same name, but other path, value=0 and expiration
 * time set to 01/01/1970.
 * MUST be used between "CgiBeginHttpHeader" and "CgiEndHttpHeader".
 *
 * Arguments:
 * char * - cookie name [I]
 * char * - cookie path [I]
 *
 * Return:
 * cgiOk										Success!
 * cgiDeleteCookieNameNull						Cookie name is NULL.
 * cgiDeleteCookieNameEmpty						Cookie name is empty.
 */
cgiError
CgiDeleteCookie (char *name, char *path)
{
	/* Use of name is mandatory */
	if (name == NULL)
		return cgiDeleteCookieNameNull;
	if (strlen (name) == 0)
		return cgiDeleteCookieNameEmpty;

	/* To delete a cookie,
	 * Sets its value to zero,
	 * and its expeiration time
	 * to 01/01/1970 */
	printf ("Set-Cookie: %s=0; expires=Thu, 01 Jan 1970 00:00:00 GMT;", name);

	if (path != NULL)
		if (strlen (path) != 0)
			printf ("Path=%s", path);

	printf ("\n");

	return cgiOk;
}
