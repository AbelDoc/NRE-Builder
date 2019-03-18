
    #include "IO/File/NREB_File.hpp"
    #include "IO/Folder/NREB_Folder.hpp"

    int main(int, char**) {
        NREB::IO::Folder src("src");

        FileList files;
        FolderList folders;

        src.createMakefile(files, folders, true);
        createProjectMakefile(files, folders);

        return 0;
    }
