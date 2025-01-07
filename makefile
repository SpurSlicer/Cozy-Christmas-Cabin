# project
EXE=final

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -DSDL2
LIBS=-lmingw32 -lSDL2main -lSDL2 -mwindows -lSDL2_mixer -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r|sed -E 's/(.).*/\1/'|tr 12 21)
CFLG=-O3 -Wall -Wno-deprecated-declarations -DRES=$(RES) -DSDL2
LIBS=-lSDL2main -lSDL2 -lSDL2_mixer -framework Cocoa -framework OpenGL
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall -DSDL2
LIBS=-lSDL2 -lSDL2_mixer -lglut -lGLU -lGL -lm -lpng
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif

# Dependencies
project.o: project.cpp object.h game.h camera.h house.h
object.o: object.cpp object.h
camera.o: object.cpp object.h camera.cpp camera.h
models.o: object.cpp object.h models.cpp models.h
house.o: object.cpp object.h models.cpp models.h house.cpp house.h 
window.o: object.cpp object.h window.cpp window.h
tree.o: object.cpp object.h tree.cpp tree.h
snow_generator.o: object.cpp object.h snow_generator.cpp snow_generator.h
game.o: object.cpp object.h house.cpp house.h game.cpp game.h

#  Create archive
dep.a: object.o camera.o models.o house.o window.o tree.o snow_generator.o game.o
	ar -rcs $@ $^

# Compile rules
.c.o:
	gcc -c $(CFLG)  $<
.cpp.o:
	g++ -c $(CFLG)  $<

#  Link
final:project.o   dep.a
	g++ $(CFLG) -o $@ $^  $(LIBS)

#  Clean
clean:
	$(CLEAN)
