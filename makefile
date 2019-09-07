minishell: main.o exec.o piping.o
	g++ main.o exec.o piping.o -o minishell

main.o: main.cpp
	g++ -c main.cpp

exec.o: exec.cpp exec.h 
	g++ -c exec.cpp

piping.o: piping.cpp piping.h
	g++ -c piping.cpp

clean:
	rm -f *.o minishell