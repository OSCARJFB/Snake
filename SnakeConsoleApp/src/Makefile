# Writen by: Oscar Bergström
# https://github.com/OSCARJFB

all: release debug 

# Compiles the graphical version.
release: snakeEngine.c
	gcc snakeEngine.c -o snake

# Compiles with debug flag.
debug: snakeEngine.c
	gcc snakeEngine.c -DDEBUG -g -o debug

# Remove all object files.
clean: 
	rm -rf snake
	rm -rf debug