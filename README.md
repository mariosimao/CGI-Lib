<h1 align="center">CGI Library</h1>
<p align="center">
Free CGI Library writen in C<br>Created by Mario Simão</p>

## Contents
- [Size Definitions](#size-definitions)  
- [Functions List](#functions-list)

## Size Definitions

| Name        | Constant                   | Value  |
| ----------- | -------------------------- | ------:|
| Query       | CGI_QUERY_MAX_LENGTH       | 1024   |
| Input Name  | CGI_INPUT_NAME_MAX_LENGTH  | 64     |
| Input Value | CGI_INPUT_VALUE_MAX_LENGTH | 128    |

## Functions List
- [Get Form Value](#get-form-value)
- [Get Form Value - Integer](#get-form-value-integer)

#### Get Form Value
```C
cgiErrorCgi
GetFormValue (char *name, char* value);
```
**Description**  
 - Gets a value from a given form input.  
 - Suports GET and POST methods.  

**Arguments**  

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | input name<br>(same as in HTML form)| I |
| **2** | char \* | input value | O |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| cgiGetFormValueInvalidMethod | Did not received any form query data.|
| cgiGetFormValueQueryInvalidFormat | Query in invalid format. |
| cgiGetFormValueEmpty | Input value is empty. |
| cgiGetFormValueNameNotFound | Did not found form input name. |

---

#### Get Form Value - Integer

```C
cgiError
CgiGetFormValueInteger (char *name, int *value);
```

**Description**
- Gets an integer value from a given form input.  
- Supports GET and POST methods.

**Arguments**

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | input name<br>(same as in HTML form)| I |
| **2** | int \* | integer value | O |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| CgiGetFormValue errors | All errors in "CgiGetFormValue" |
| cgiGetFormValueIntegerInvalid | Value is not an integer. |

---
