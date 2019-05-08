# NRE-Builder
NRE-Builder is an automatic makefile generator !  
It's allowing to create and manage C/C++ project easily :  

## Features
### Project creation  
__./NRE-Builder.exe -c__  
__./NRE-Builder.exe -create__  
The project will create a base project architecture :  
   * _**bin**_ : Will be used to store compiled binaries
   * _**lib**_ : Will be used to store static libraries
   * _**obj**_ : Will be used to store .o files
   * _**src**_ : Will be used to store sources files, this folder will be analysed by the builder  
   * _**docs**_ : Will be used to store project's documentation
   * _**uml**_ : Will be used to store UML diagram
   * _**src/main.cpp**_ : An empty file   
After the creation the builder will analyse automatically the src directory to create corresponding makefile  

### Makefile & Libraries generation  
__./NRE-Builder.exe__  
__./NRE-Builder.exe -a__  
__./NRE-Builder.exe -analyse__  
The project will analyse the src directory and create all needed makefile.  
Some makefile can be useless for directory with only header files
The builder will search for sub-directory recursively, no need to pack all files in one folder  
For the builder to correctly analyse the project you need to configurate it correctly :  
* The config.nre file need to be on the same level as the builder
* You need to fill compiler/linker/archiver/out fields
* Other fields aren't mandatory :
    * _**compiler**_ : You need to specify the compiler to use
    * _**linker**_ : You need to specify the linker to use
    * _**archiver**_ : You need to specify the archiver to use
    * _**cflags**_ : Flags used for compilation
    * _**ldflags**_ : Flags used for linking
    * _**includes**_ : Includes for the project, only path separated by a whitespace
    * _**lib**_ : Library for the project, same format as includes
    * _**libdir**_ : Library directories for the project, same format as includes
    * _**out**_ : The out binaries name
    * _**excluded**_ : Path or word (separated by a whitespace) excluded from the build, every file contaning one of this word/path will be excluded from makefile generation

When analysing the tool will create also an archive generation script.  
A simple bash script to create a static library in the lib directory  
* With the following name format : Y/libX.a  
* Where Y is the configuration out path and X the configuration out name  
* It will regroup every object file (except those excluded from the build)

### Multiple Configuration
__./NRE-Builder.exe -a -s=XXX__  
__./NRE-Builder.exe -a -switch=XXX__  
The project will no longer search for config.nre file, instead it will search for config.XXX.nre.  
Allowing you to have multiple configuration easily.  
