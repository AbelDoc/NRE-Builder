OBJ = $(OBJDIR)NREB_Entry.o 
OBJDIR = ../../obj/IO/

FILE = File
FOLDER = Folder

all : childs $(OBJ)

childs:
	@(cd $(FILE) && $(MAKE))
	@(cd $(FOLDER) && $(MAKE))

$(OBJDIR)%.o : %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)