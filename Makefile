CC= gcc
FLAGS= -Wall -g
LIB= -lreadline

.PHONY: clean readline-install

shell: build_parser build_jobs build_builtin src/shell.c
	$(CC) $(LIB) $(FLAGS) out/parser.o out/jobs.o out/builtin.o src/shell.c -o out/trash

build_parser: src/parser.c src/parser.h
	$(CC) -c $(FLAGS) src/parser.c -o out/parser.o

build_jobs: src/jobs.c src/jobs.h
	$(CC) -c $(FLAGS) src/jobs.c -o out/jobs.o

build_builtin: src/builtin.c src/builtin.h
	$(CC) -c $(FLAGS) src/builtin.c -o out/builtin.o

clean:
	rm out/*

readline-install:
	echo "Install readline"
	#sudo apt-get ...
