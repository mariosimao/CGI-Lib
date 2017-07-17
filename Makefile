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

TESTOBJS = teste.o cgiLib.o

EXECS = teste

ALL = $(EXECS)

# Implicit Rule
.c.o:
	$(CC) $(CFLAGS) -c $<

# Compiles and link-edits all the code
all: $(ALL)

teste: $(TESTOBJS)
	$(LD) $(LFLAGS) -o $@.cgi $(TESTOBJS)

# Removes all objects and executables
clean:
	rm -f *.o $(ALL)
