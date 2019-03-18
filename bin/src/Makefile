OBJ = $(OBJDIR)NREB_Main.o 
OBJDIR = ../obj/

EVENT = Event
IO = IO

all : childs $(OBJ)

childs:
	@(cd $(EVENT) && $(MAKE))
	@(cd $(IO) && $(MAKE))

$(OBJDIR)%.o : %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)