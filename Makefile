# +------------------------------------------+
# |               CGI LIBRARY                |
# +------------------------------------------+
# | Created by: Mario Simao                  |
# |                                          |
# | Universidade Federal do Rio de Janeiro   |
# | Tab size: 4                              |
# +------------------------------------------+

CC = gcc
LD = gcc

CFLAGS = -Wall -std=c99 -ansi
LFLAGS = -Wall -std=c99 -ansi

SIMPLE_FORM_OBJS = simpleForm.o cgiLib.o
SIMPLE_COOKIE_OBJS = simpleCookie.o cgiLib.o

EXECS = simpleForm\
		simpleCookie

ALL = $(EXECS)

# Implicit Rule
.c.o:
	$(CC) $(CFLAGS) -c $<

# Compiles and link-edits all the code
all: $(ALL)

simpleForm: $(SIMPLE_FORM_OBJS)
	$(LD) $(LFLAGS) -o $@.cgi $(SIMPLE_FORM_OBJS)

simpleCookie: $(SIMPLE_COOKIE_OBJS)
	$(LD) $(LFLAGS) -o $@.cgi $(SIMPLE_COOKIE_OBJS)

# Removes all objects and executables
clean:
	rm -f *.o $(ALL)
