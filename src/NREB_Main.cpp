
    #include "IO/File/NREB_File.hpp"
    #include "IO/Folder/NREB_Folder.hpp"

    int main(int, char**) {
        NREB::IO::Folder src("src");

        src.createMakefile();

        return 0;
    }
