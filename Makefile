#Copyright (c) 2014, LEVY-FALK Hugo
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
#
#1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
#
#2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.PHONY: clean, mrproper
.SUFFIXES:
 
#variables
CXX = g++
NAME = Rambanana
EXEC_DIR = bin/
EXEC_DIR_EXIST :=`ls | grep bin | wc -l`
EXEC = $(EXEC_DIR)$(NAME)
EXEC_EDIT = $(EXEC_DIR)Editeur
DEBUG = yes
RUNAPP = yes

LIB = -L $(HOME)/SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -L ./lib -ljson
INCLUDE = -I $(HOME)/SFML-2.1/include -I ./include -DNDEBUG
ifeq ($(DEBUG),yes)
	CXXFLAGS = -Wall -Wextra -Wunreachable-code -Wwrite-strings -g -std=c++11 $(INCLUDE)
else
  CXXFLAGS = -std=c++11 $(INCLUDE)
endif


#création de l'exécutable
all: exec_dir 
	make game 
	make editor
	make clean

exec_dir: mrproper
	mkdir bin

game: main.o personnage.o World.o
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS) $(LIB)
ifeq ($(RUNAPP),yes)
ifeq ($(DEBUG),yes)
	cd $(EXEC_DIR) && valgrind --track-origins=yes ./$(NAME)
else
	cd $(EXEC_DIR) && ./$(NAME)
endif
endif

editor: menu.o mapeditor.o World.o SDLFunc.o
	$(CXX) $^ -o $(EXEC_EDIT) $(CXXFLAGS) $(LIB)
ifeq ($(RUNAPP),yes)
ifeq ($(DEBUG),yes)
	cd $(EXEC_DIR) && valgrind --track-origins=yes ./Editeur
else
	cd $(EXEC_DIR) && ./Editeur
endif
endif

	

main.o: src/personnage.h src/defines.h src/World.h
World.o: src/World.h src/personnage.h
personnage.o: src/personnage.h src/World.h
menu.o: src/menu.h src/World.h
mapeditor.o: src/mapeditor.h src/menu.h src/World.h src/defines.h

%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# clean
clean:
	rm -rf *.o

# mrproper
mrproper: clean
	rm -rf $(EXEC) bin
