EXE = minishell
DIR = $(shell pwd)

bin/minishell: obj/main.o obj/exec.o obj/piping.o obj/directory.o
	g++ $(DIR)/obj/main.o $(DIR)/obj/exec. $(DIR)/obj/piping.o $(DIR)/obj/directory.o -o $(DIR)/bin/$(EXE)

obj/main.o: src/main.cpp
	g++ -c -Iinclude $(DIR)/src/main.cpp -o $(DIR)/obj/main.o

obj/exec.o: src/exec.cpp include/exec.h 
	g++ -c -Iinclude $(DIR)/src/exec.cpp -o $(DIR)/obj/exec.o

obj/piping.o: src/piping.cpp include/piping.h
	g++ -c -Iinclude $(DIR)/src/piping.cpp -o $(DIR)/obj/piping.o

obj/directory.o: src/directory.cpp include/directory.h
	g++ -c -Iinclude $(DIR)/src/directory.cpp -o $(DIR)/obj/directory.o

clean:
	rm -f $(DIR)/obj/*.o $(DIR)/bin/minishell
