all: ejecutable 



SOURCES := $(wildcard *.cpp)
OBJECTS := $(subst .cpp,.o,$(SOURCES))
LIBS 	:= -lIrrlicht -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lBulletWorldImporter -lfmod -lfmodstudio -Wl,-rpath=lib -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE := -I. -I/usr/include/bullet/ -I/usr/include/irrlicht/ -I/usr/local/include -L/usr/local/lib  
CC		:= g++

ejecutable: $(OBJECTS)
	g++ -g -o $@ $^ $(INCLUDE) $(LIBS)

%.o: %.cpp
	g++ -g -o $@ -c $^ $(INCLUDE)

info:
	$(info $(SOURCES))
	$(info $(OBJECTS))

clean:
	rm -f ejecutable *.o
