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
- [Get Form Value](#1-get-form-value)
- [Get Form Value - Integer](#2-get-form-value---integer)
- [Get Form Value - Double](#3-get-form-value---double)
- [Begin HTTP Header](#4-begin-http-header)
- [End HTTP Header](#5-end-http-header)
- [Set Cookie](#6-set-cookie)
- [Get Cookie](#7-get-cookie)
- [Delete Cookie](#8-delete-cookie)

---

### 1. Get Form Value
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

### 2. Get Form Value - Integer

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

### 3. Get Form Value - Double

```C
cgiError
CgiGetFormValueDouble (char *name, double *value);
```

**Description**
- Gets a double value from a given form input.  
- Supports GET and POST methods.

**Arguments**

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | input name<br>(same as in HTML form)| I |
| **2** | double \* | double value | O |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| CgiGetFormValue errors | All errors in "CgiGetFormValue" |
| cgiGetFormValueDoubleInvalid | Value is not a double. |

---

### 4. Begin HTTP Header

```C
cgiError
CgiBeginHttpHeader (void);
```

**Description**
- Begins HTTP header with content type set as "text/html"

**Arguments**

- No arguments.

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |

---

### 5. End HTTP Header

```C
cgiError
CgiEndHttpHeader (void);
```

**Description**
- Ends HTTP header.

**Arguments**

- No arguments.

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |

---

### 6. Set Cookie

```C
cgiError
CgiSetCookie (char *name, char *value, int maxAge, char *path);
```

**Description**
- Sets a cookie.
- **Must** be used between [*CgiBeginHttpHeader*](#4-begin-http-header) and [*CgiEndHttpHeader*](#5-end-http-header).

**Arguments**

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | cookie name| I |
| **2** | char \* | cookie value | I |
| **3** | int | cookie maxAge<br>(use ***0*** if you don't want to set) | I |
| **4** | char * | path <br>(use ***NULL*** if you don't want to set)| I |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| cgiSetCookieNameNull | Cookie name is *NULL* |
| cgiSetCookieNameEmpty |Cookie name is empty |
| cgiSetCookieValueNull | Cookie value is *NULL* |
| cgiSetCookieValueEmpty | Cookie value is empty |

---

### 7. Get Cookie

```C
cgiError
CgiGetCookie (char *name, char* value);
```

**Description**
- Gets a cookie value.
- **Must** be used between [*CgiBeginHttpHeader*](#4-begin-http-header) and [*CgiEndHttpHeader*](#5-end-http-header).

**Arguments**

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | cookie name| I |
| **2** | char \* | cookie value | O |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| cgiGetCookieNullName | Cookie name is *NULL*. |
| cgiGetCookieNameEmpty |Cookie name is empty. |
| cgiGetCookieNullValue | Cookie value is *NULL*. |
| cgiGetCookieNullCookie | Could not list the cookies. |
| cgiGetCookieNameNotFound | Cookie name not found. |

---

### 8. Delete Cookie

```C
cgiError
CgiDeleteCookie (char *name, char* path);
```

**Description**
- Delets a cookie.
- **Must** be used between [*CgiBeginHttpHeader*](#4-begin-http-header) and [*CgiEndHttpHeader*](#5-end-http-header).

**Arguments**

| #| Type | Description | I / O |
| - |:----:| ---- |:-----:|
| **1** | char \* | cookie name| I |
| **2** | char \* | cookie path<br>(same path the cookie was set) | I |

**Return**

| Returned code | Information |
| ------------- | ----------- |
| cgiOk         | Success!    |
| cgiDeleteCookieNameNull | Cookie name is *NULL*. |
| cgiDeleteCookieNameEmpty |Cookie name is empty. |

---
