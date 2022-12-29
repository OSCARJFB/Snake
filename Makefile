# Writen by: Oscar Bergström
# https://github.com/OSCARJFB

all: graphics no_graphics 

# Compiles the graphical version.
graphics: snake_engine_raylib_app.c 
	cc snake_engine_raylib_app.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o SnakeRaylibApp

# Compiles the console version.
no_graphics: snake_engine_console_app.c
	cc snake_engine_console_app.c -o SnakeConsoleApp

# Remove all object files.
clean: 
	rm -rf SnakeRaylibApp
	rm -rf SnakeConsoleApp