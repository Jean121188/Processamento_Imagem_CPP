# diretorios
APP		= ./app
BIN		= ./bin
INCLUDE	= ./include
OBJ		= ./obj
SRC		= ./src

all: build compile
	
build:
	g++ -c $(SRC)/image.cpp -I $(INCLUDE) -o $(OBJ)/image.o -lm

compile:
	g++ $(APP)/app.cpp $(OBJ)/*.o -I $(INCLUDE) -o $(BIN)/app -lm

run:
	$(BIN)/app

clean:
	rm -rf ./obj/image.o
	rm -rf ./bin/app