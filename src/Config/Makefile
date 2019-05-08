OBJ = $(OBJDIR)NREB_Config.o
OBJDIR = ../../obj/Config/

all : $(OBJ)

$(OBJDIR)%.o : %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)
