name = erg1
name2 = erg2
name3 = erg3
name4 = erg4
src = $(wildcard *.cpp)
obj = $(src:/c=.o)

CC = g++
CFLAGS = -std=c++0x -O3
LIBFLAGS = -lleda -lm
Leda = '/usr/local/LEDA/incl'
LedaLibs = '/usr/local/LEDA'
all: $(obj) $(name) $(name2) $(name3) $(name4)
$(name): $(obj)
	$(CC) $(CFLAGS) -o $@ $< -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)

$(name2): $(obj)
	$(CC) $(CFLAGS) -o $@ $< -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)

$(name3): $(obj)
	$(CC) $(CFLAGS) -o $@ $< -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)

$(name4): $(obj)
	$(CC) $(CFLAGS) -o $@ $< -I$(Leda) -L$(LedaLibs) $(LIBFLAGS)

$(obj): $(name) $(name2) $(name3)

run:
	echo "running circles graph familly"
	./$(name)
	echo "running 4 level graph"
	./$(name2)
	echo "running squares graph familly"
	./$(name3)
	echo "running bonus graph familly"
	./$(name4)

clean:
	rm -f $(name) $(name2) $(name3) $(name4)
