
    /**
     * @file NREB_Main.hpp
     * @brief Implementation of Builder's Main
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright CC-BY-NC-SA
     */

    #include "IO/File/NREB_File.hpp"
    #include "IO/Folder/NREB_Folder.hpp"

    namespace FileSystem = std::experimental::filesystem;

    int main(int argc, char** argv) {
        if (argc == 2) {
            if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "-help") {
                std::cout << "Usage : \n";
                std::cout << "./NRE-Builder.exe [-a|-analyse|-c|-create]\n";
                std::cout << "\t-a|-analyse\n";
                std::cout << "\tAnalyse the src directory and regenerate all makefile\n";
                std::cout << "\tIf no option is specified, analyse is the default one\n\n";
                std::cout << "\t-c|-create\n";
                std::cout << "\tCreate a new project with base directory and makefile\n" << std::endl;
            } else if (std::string(argv[1]) == "-c" || std::string(argv[1]) == "-create") {
                FileSystem::create_directories("src");
                FileSystem::create_directories("bin");
                FileSystem::create_directories("obj");
                FileSystem::create_directories("docs");
                FileSystem::create_directories("uml");
                std::ofstream base("src/main.cpp");
            }
        }

        if (argc == 1 || (argc == 2 && (std::string(argv[1]) == "-a" || std::string(argv[1]) == "-analyse" || std::string(argv[1]) == "-c" || std::string(argv[1]) == "-create"))) {
            FileSystem::create_directories("src");
            NREB::IO::Folder src("src");

            NREB::IO::FileList files;
            NREB::IO::FolderList folders;

            src.createMakefile(files, folders);
            src.createProjectMakefile(files, folders);
        }

        return 0;
    }
