SRCDIR = src/
BLDDIR = build/
main : ${SRCDIR}main.cpp ${BUILD}tictactoe.o
	g++ -Wall -o ${BLDDIR}main ${SRCDIR}main.cpp ${BLDDIR}tictactoe.o
tictactoe.o : ${SRCDIR}tictactoe.cpp ${SRCDIR}tictactoe.h
	g++ -c -o ${BLDDIR}tictactoe.o ${SRCDIR}tictactoe.cpp
clean :
	rm ${BLDDIR}*
