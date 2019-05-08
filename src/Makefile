OBJ = $(OBJDIR)NREB_Main.o
OBJDIR = ../obj/

IO = IO
CONFIG = Config

all : childs $(OBJ)

childs:
	@(cd $(CONFIG) && $(MAKE))
	@(cd $(IO) && $(MAKE))

$(OBJDIR)%.o : %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)
