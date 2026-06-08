# Makefile
# 
# Mike Henderson
# June 2026

APP = elevator

CPPS = main.cpp elevator.cpp
HEADERS = elevator.h exception.h

all: ${APP} 

${APP}: ${CPPS} ${HEADERS}
	g++ -std=c++14 ${CPPS} -o ${APP}
