export CXX = g++.exe
export LD = g++.exe

export CFLAGS = -pedantic -Wno-virtual-move-assign -Wall -Wextra -Wfloat-equal -Wstrict-overflow -Wshadow -Wconversion -Wunreachable-code -Wuninitialized -Winit-self -Werror -fstrict-overflow -std=c++17
export LDFLAGS = -lstdc++fs

export INC = -I"C:\lib\MinGW64_7.3\include"
export LIBDIR = -L"C:\lib\MinGW64_7.3\lib"
export LIB = "C:\lib\MinGW64_7.3\x86_64-w64-mingw32\lib\libmingw32.a"

export TARGET = debug

OBJDIR = obj/
BIN = bin/
SOURCE = src
OBJ = $(OBJDIR)IO/NREB_Entry.o $(OBJDIR)IO/File/NREB_File.o $(OBJDIR)IO/Folder/NREB_Folder.o $(OBJDIR)NREB_Main.o
OUT = NRE-Builder

all : before out

before:
	@(cd $(SOURCE) && $(MAKE))

out : $(OBJ)
	@$(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LDFLAGS) $(LIB)
	@echo "Jobs done."

clean :
	@echo "Clear of obj/"
	@rm -r obj
	@mkdir obj
	@mkdir obj/IO
	@mkdir obj/IO/File
	@mkdir obj/IO/Folder
	@echo "obj/-Tree creation done."
	@echo "Clean done."
