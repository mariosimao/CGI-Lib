#include "cgiLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
CgiGetFormValue (char *name, char* value)
{
	unsigned long postLength;
	char getQuery [CGI_QUERY_MAX_LENGTH + 1];
	char postQuery [CGI_QUERY_MAX_LENGTH + 1];
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

	/* Get GET Query */
	strcpy (getQuery, getenv ("QUERY_STRING"));

	/* Get POST Query */
	if (getenv ("CONTENT_LENGTH"))
	{
		postLength = strtol (getenv ("CONTENT_LENGTH"), NULL, 10);
		fgets (postQuery, postLength + 1, stdin);
	}

	/* Post and Get queries are NULL */
	if ((strlen (getQuery) == 0) && (strlen (postQuery) == 0))
		return cgiGetFormValueGetPostNull;
	/* Get query */
	else if (strlen (getQuery) > 0)
		strcpy (query, getQuery);
	/* Post query */
	else
		strcpy (query, postQuery);

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
CgiGetFormValueInteger (char *name, int *value)
{
	cgiError result;
	char stringValue [CGI_INPUT_VALUE_MAX_LENGTH];
	char *validation;

	/* Get string */
	result = CgiGetFormValue (name, stringValue);
	if (result != cgiOk)
		return result;

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
CgiGetFormValueDouble (char *name, double *value)
{
	cgiError result;
	char stringValue [CGI_INPUT_VALUE_MAX_LENGTH];
	char *validation;
	size_t index;

	/* Get string */
	result = CgiGetFormValue (name, stringValue);
	if (result != cgiOk)
		return result;

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
