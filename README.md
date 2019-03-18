# NRE-Builder
NRE-Builder is an automatic makefile generator !  
It's allowing to create and manage C/C++ project easily :  

## Features
### Project creation  
__./NRE-Builder.exe -c__  
__./NRE-Builder.exe -create__  
The project will create a base project architecture :  
   * _**bin**_ : Will be used to store compiled binaries
   * _**obj**_ : Will be used to store .o files
   * _**src**_ : Will be used to store sources files, this folder will be analysed by the builder  
   * _**docs**_ : Will be used to store project's documentation
   * _**uml**_ : Will be used to store UML diagram
   * _**src/main.cpp**_ : An empty file   
After the creation the builder will analyse automatically the src directory to create corresponding makefile  

### Makefile generation  
__./NRE-Builder.exe__  
__./NRE-Builder.exe -a__  
__./NRE-Builder.exe -analyse__  
The project will analyse the src directory and create all needed makefile.  
Some makefile can be useless for directory with only header files
The builder will search for sub-directory recursively, no need to pack all files in one folder  
For the builder to correctly analyse the project you need to configurate it correctly :  
* The config.nre file need to be on the same level as the builder
* You need to fill compiler/linker/out fields
* Other fields aren't mandatory :
    * _**compiler**_ : You need to specify the compiler to use
    * _**linker**_ : You need to specify the linker to use
    * _**cflags**_ : Flags used for compilation
    * _**ldflags**_ : Flags used for linking
    * _**includes**_ : Includes for the project, only path separated by a whitespace
    * _**lib**_ : Library for the project, same format as includes
    * _**libdir**_ : Library directories for the project, same format as includes
    * _**out**_ : The out binaries name
