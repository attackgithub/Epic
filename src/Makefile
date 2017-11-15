CC := gcc
CWARN := -Wall
CSTD := -std=c1x
OPT := -O2
LIB := -lws2_32

all : server client

server :
	${CC} $@.c -o sev ${CWARN} ${CSTD} ${OPT} ${LIB}

client :
	${CC} $@.c -o cli ${CWARN} ${CSTD} ${OPT} ${LIB}

