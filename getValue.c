#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
	cgiOk,
	cgiGetPostNull,
	cgiGetPostBoth,
	cgiNameNotFound,
} cgiError;

cgiError
cgiGetQueryString (char *query, char *name, char* value)
{
	size_t queryIndex, dataIndex;

	char dataName [1024 + 1], query [1024 + 1], dataValue [1024 + 1], value [1024 + 1]; /* TODO Receive size */
	strcpy (query, argv[1]);

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
			dataValue [dataIndex] = query [queryIndex];
			queryIndex++;
			dataIndex++;
		}
		dataValue [dataIndex] = '\0'; /* Inserts EOS */
		/* Jumps '&' character.
		 * Avoids jumping EOS */
		if (query [queryIndex] == '&')
			queryIndex++;

		if (strcmp (dataName, argv[2]) == 0)
		{
			strcpy (value, dataValue);
			return cgiOk;
		}

	}

	return cgiNameNotFound;
}
