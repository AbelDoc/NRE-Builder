OBJ = $(OBJDIR)NREB_File.o 
OBJDIR = ../../../obj/IO/File/

all : $(OBJ)

$(OBJDIR)%.o : %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)