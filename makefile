EXE = minishell

bin/minishell: obj/main.o obj/exec.o obj/piping.o obj/directory.o
	g++ obj/main.o obj/exec.o obj/piping.o obj/directory.o -o bin/$(EXE)

obj/main.o: src/main.cpp
	g++ -c -Iinclude src/main.cpp -o obj/main.o

obj/exec.o: src/exec.cpp include/exec.h 
	g++ -c -Iinclude src/exec.cpp -o obj/exec.o

obj/piping.o: src/piping.cpp include/piping.h
	g++ -c -Iinclude src/piping.cpp -o obj/piping.o

obj/directory.o: src/directory.cpp include/directory.h
	g++ -c -Iinclude src/directory.cpp -o obj/directory.o

clean:
	rm -f obj/*.o bin/minishell