#Rutas
MODEL = src/model
VIEW = src/view
CONTROL = src/controller
LIBS = libs/

#BinFiles < Archivos a dejar en .o
BIN_MODEL = $(filter-out main.cpp, $(wildcard $(MODEL)/*.cpp))
BIN_VIEW = $(wildcard $(VIEW)/*.cpp)
BIN_CONTROL = $(wildcard $(CONTROL)/*.cpp)
BIN_LIB = $(wildcard $(LIB)/*.cpp)

H_MODEL = $(wildcard $(MODEL)/*.h)
H_VIEW = $(wildcard $(VIEW)/*.h)
H_CONTROL = $(wildcard $(CONTROL)/*.h)
H_LIB = $(wildcard $(LIB)/*.h)

#OBJ: Archivo final a Compilar
#$(wildcard *.cpp) agarra todoslos cpp
OBJ = $(MODEL)/main.cpp
#CC: Compilador 
CC = gcc 
#COMPILER_FLAGS: Parametros de compilacion 
COMPILER_FLAGS = -Wall -pedantic -g
#LINKER_FLAGS: Librerias adicionales
LINKER_FLAGS = -lSDL2 -lSDL2_image
#OBJ_NAME: Nombre del ejecutable
SALIDA = MK-FIUBA.exe

#Target para compilar 
all: control view model main

model: $(BIN_MODEL) $(H_MODEL)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $<

view: $(BIN_VIEW) $(H_VIEW)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $<

control: $(BIN_CONTROL) $(H_CONTROL)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $<

main : $(BINFILES) $(OBJ)
	$(CC) $(OBJ) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(BINFILES) -o $(SALIDA)
