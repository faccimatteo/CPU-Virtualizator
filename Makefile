objects = vm.o leggi.o stampa.o esegui.o
executable = VM
# -fsanitize=address -fsanitize=undefined have problems with windows
cflags = -g3 -std=gnu89 -pedantic-errors -Wall -Wextra
libs = -lm


# implicit rules
%.o: ./src/%.c ./include/*.h
	gcc $(cflags) -c $^

$(executable) : $(objects)
	gcc $(cflags) -o $@ $^ $(libs)

clean:
	rm $(executable)  $(objects)


	 

