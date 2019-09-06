minishell: main.o exec.o
	g++ main.o exec.o -o minishell

main.o: main.cpp
	g++ -c main.cpp

exec.o: exec.cpp exec.h 
	g++ -c exec.cpp

clean:
	rm -f *.o minishell