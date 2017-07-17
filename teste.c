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
cgiGetQueryString (char *query, char *name, char* value);

cgiError
main (void)
{
	char *getQuery;
	unsigned long postLength;
	char postQuery [1024 + 1], query [1024 + 1]; /* TODO Create a constant for the size */
	size_t queryIndex, dataIndex;
	char value [1024 + 1];
	char dataName [1024 + 1], dataValue [1024 + 1]; /* TODO Receive size */

	/* EOS (End of String) = '\0'
	 * Query format:  name1=value1&name2=value2&name3=value3
	 * Query example: name=Mario

	/* Get GET Query */
	getQuery = getenv ("QUERY_STRING");

	/* Get POST Query */
	if (getenv ("CONTENT_LENGTH"))
	{
		postLength = strtol (getenv ("CONTENT_LENGTH"), NULL, 10);
		fgets (postQuery, 1024 + 1, stdin); /* TODO Insert constant */
	}
	printf ("Content-Type: text/html\n\n");
	printf ("<pre>");
	printf (" Get-query: [%s]\n", getQuery);
	printf ("Post-query: [%s]\n", postQuery);

	/* Post and Get queries are NULL */
	if ((strlen (getQuery) == 0) && (strlen (postQuery) == 0))
		return cgiGetPostNull;
	/* Post and Get queries are not NULL (both) */
	else if ((strlen (getQuery) > 0) && (strlen (postQuery) > 0))
		return cgiGetPostBoth;
	/* Get query */
	else if (strlen (getQuery) > 0)
		strcpy (query, getQuery);
	/* Post query */
	else
		strcpy (query, postQuery);

	printf (" All-query: [%s]\n", query);
	printf ("</pre>");

	cgiGetQueryString (query, "age", value);

	printf ("<pre>");
	printf ("Value: [%s]\n", value);
	printf ("</pre>");

	return cgiNameNotFound;
}

cgiError
cgiGetQueryString (char *query, char *name, char* value)
{
	size_t queryIndex, dataIndex;

	char dataName [1024 + 1], dataValue [1024 + 1]; /* TODO Receive size */

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

		if (strcmp (dataName, name) == 0)
		{
			strcpy (value, dataValue);
			return cgiOk;
		}

	}

	return cgiNameNotFound;
}
