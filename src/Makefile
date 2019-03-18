OBJ = $(OBJDIR)NREB_Main.o 
OBJDIR = ../obj/

IO = IO

all : childs $(OBJ)

childs:
	@(cd $(IO) && $(MAKE))

$(OBJDIR)%.o : %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)