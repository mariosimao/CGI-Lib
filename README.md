CGI LIBRARY

	Maximum Lengths (you can change this values in cgiLib.h)

		- Query: 1024			[CGI_QUERY_MAX_LENGTH];
		- Input Name: 64 		[CGI_INPUT_NAME_MAX_LENGTH];
		- Input Value: 128		[CGI_INPUT_VALUE_MAX_LENGTH];

	Functions List:

		 cgiError
		 cgiGetFormString (char *name, char* value);
		|
		|	GET FORM STRING
		|
		|	Description:
		|	Gets a value from a given form input.
		|	Suports GET and POST methods.
		|	Converts '+' to spaces.
		|	Converts hex (e.g. E1) to string.
		|
		|	Arguments:
		|	char * - input name (same as in HTML form) [I]
		|	char * - input value [O]
		|
		|	Return:
		|	cgiOk										Success!
		|	cgiGetFormStringGetPostNull					Did not received any form query data.
		|	cgiGetFormStringQueryInvalidFormat			Query in invalid format.
		|	cgiGetFormStringNameNotFound				Did not found form input name.
