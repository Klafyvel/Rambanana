#    Copyright (C) 2013 LEVY-FALK Hugo
#
#    This program is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this program; if not, write to the Free Software
#    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
.PHONY: clean, mrproper
.SUFFIXES:

#variables
CXX = g++
NAME = Rambanana
EXEC_DIR = bin/
EXEC = $(EXEC_DIR)$(NAME)
DEBUG = yes
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include

ifeq ($(DEBUG),yes)
	CXXFLAGS = -Wall -Wextra -Wunreachable-code -Wwrite-strings -g -std=c++11 $(SDL_INCLUDE)
else
	CXXFLAGS = -std=c++11 $(SDL_INCLUDE)
endif



#création de l'exécutable
all: main.o personnage.o SDLFunc.o
	mkdir bin
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS) $(SDL_LIB)
	@echo "\033[31mMakefile: \033[32m \t> un exemple a été créé à partir du fichier à cet endroit : $(EXEC)\n\t\t> 'make mrproper' pour réinitialiser le répertoire. \033[0m \n"
ifeq ($(DEBUG),yes)
	cd $(EXEC_DIR) && valgrind ./$(NAME)
else
	cd $(EXEC_DIR) && ./$(NAME)
endif

main.o: src/personnage.h src/defines.h src/SDLFunc.h
SDLFunc.o: src/SDLFunc.h
personnage.o: src/personnage.h

%.o: src/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# clean
clean:
	rm -rf *.o

# mrproper
mrproper: clean
	rm -rf $(EXEC) bin
