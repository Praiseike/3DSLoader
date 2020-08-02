
main: main.o
	g++ -std=c++11 -o main main.o -lGLU -lglut -lGL -lGLEW -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o

clean:
	rm *.o main
