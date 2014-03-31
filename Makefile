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
WINCXX = i586-mingw32msvc-g++
NAME = Rambanana
EXEC_DIR = bin/
EXEC_DIR_EXIST :=`ls | grep bin | wc -l`
EXEC = $(EXEC_DIR)$(NAME)
EXEC_EDIT = $(EXEC_DIR)Editeur

DEBUG = yes
RUNAPP = yes
WINEX = no

ifeq ($(WINEX),no)
LIB = -L $(HOME)/SFML-2.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lm
INCLUDE = -I $(HOME)/SFML-2.1/include -I include/
ifeq ($(DEBUG),yes)
	CXXFLAGS = -Wall -Wextra -Wunreachable-code -Wwrite-strings -Werror -Wfatal-errors -pedantic -g -std=c++11 $(INCLUDE)
else
  CXXFLAGS = -std=c++11 $(INCLUDE)
endif
else
LIB = -L $(HOME)/SFML-2.1-win/lib -lsfml-graphics -lsfml-window -lsfml-system -lm
INCLUDE = -I $(HOME)/SFML-2.1-win/include -I include/
ifeq ($(DEBUG),yes)
	CXXFLAGS = -Wall -Wextra -Wunreachable-code -Wwrite-strings -Werror -Wfatal-errors -g $(INCLUDE)
else
  CXXFLAGS = $(INCLUDE)
endif
endif

#création de l'exécutable
all: exec_dir 
	make game 
#	make editor
	make clean

exec_dir: mrproper
	mkdir bin

game: main.o game.o personnage.o World.o cJSON.o menu.o
ifeq ($(WINEX),yes)
	$(WINCXX) $^ -o $(EXEC).exe $(CXXFLAGS) $(LIB)
	@cp $(HOME)/SFML-2.1-win/bin/sfml-graphics-2.dll bin/
	@cp $(HOME)/SFML-2.1-win/bin/sfml-system-2.dll bin/
	@cp $(HOME)/SFML-2.1-win/bin/sfml-window-2.dll bin/
	@cp $(HOME)/SFML-2.1-win/bin/libsndfile-1.dll bin/
	@cp $(HOME)/SFML-2.1-win/bin/openal32.dll bin/
	@cp $(HOME)/SFML-2.1-win/bin/sfml-audio-2.dll bin/
ifeq ($(RUNAPP),yes)
	cd bin && wine $(NAME).exe && cd ..
endif
else
	$(CXX) $^ -o $(EXEC) $(CXXFLAGS) $(LIB)
ifeq ($(RUNAPP),yes)
ifeq ($(DEBUG),yes)
	cd $(EXEC_DIR) && valgrind --track-origins=yes --leak-check=full ./$(NAME)
else
	cd $(EXEC_DIR) && ./$(NAME)
endif
endif
endif


editor: menu.o mapeditor.o World.o cJSON.o
ifeq ($(WINEX),yes)
	$(WINCXX) $^ -o $(EXEC_EDIT) $(CXXFLAGS) $(LIB)
else
	$(CXX) $^ -o $(EXEC_EDIT) $(CXXFLAGS) $(LIB)
endif
ifeq ($(RUNAPP),yes)
ifeq ($(DEBUG),yes)
	cd $(EXEC_DIR) && valgrind --track-origins=yes ./Editeur
else
	cd $(EXEC_DIR) && ./Editeur
endif
endif

winarchive: clean
	make RUNAPP=no WINEX=yes
	zip -r $(NAME).zip ./bin ./font ./lvl ./sprites
	

main.o: src/personnage.h src/defines.h src/World.h src/game.h
game.o: src/game.h src/defines.h src/World.h src/personnage.h
World.o: src/World.h src/personnage.h
personnage.o: src/personnage.h src/World.h
menu.o: src/menu.h src/World.h
mapeditor.o: src/mapeditor.h src/menu.h src/World.h src/defines.h
cJSON.o: include/cJSON.c include/cJSON.h
ifeq ($(WINEX),yes)
	$(WINCXX) -c $< -o $@ $(CXXFLAGS)
else
	$(CXX) -c $< -o $@ $(CXXFLAGS)
endif

%.o: src/%.cpp
ifeq ($(WINEX),yes)
	$(WINCXX) -c $< -o $@ $(CXXFLAGS)
else
	$(CXX) -c $< -o $@ $(CXXFLAGS)
endif
# clean
clean:
	rm -rf *.o

# mrproper
mrproper: clean
	rm -rf $(EXEC) bin *.zip
