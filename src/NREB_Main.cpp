
    /**
     * @file NREB_Main.hpp
     * @brief Implementation of Builder's Main
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright CC-BY-NC-SA
     */

    #include "IO/File/NREB_File.hpp"
    #include "IO/Folder/NREB_Folder.hpp"
    #include "Config/NREB_Config.hpp"

    namespace FileSystem = std::experimental::filesystem;

    int main(int argc, char** argv) {
        if (argc == 2) {
            if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "-help") {
                std::cout << "Usage : \n";
                std::cout << "./NRE-Builder.exe [-a|-analyse|-c|-create|-t|-test] [-s=|-switch=]\n";
                std::cout << "\t-a|-analyse\n";
                std::cout << "\tAnalyse the src directory and regenerate all makefile\n";
                std::cout << "\tIf no option is specified, analyse is the default one\n\n";
                std::cout << "\t-c|-create\n";
                std::cout << "\tCreate a new project with base directory and makefile\n\n";
                std::cout << "\t-t|-test\n";
                std::cout << "\tAnalyse the test directory and regenerate all makefile,\n";
                std::cout << "\tuse the config.test.nre configuration file\n\n";
                std::cout << "\t-s=|-switch=\n";
                std::cout << "\tAllow to change configuration file at execution :\n";
                std::cout << "\t\t-s=linux\n";
                std::cout << "\tWill search for config.linux.nre file for the configuration\n";
                std::cout << "\t(or config.test.linux.nre, if test is specified)" << std::endl;
            } else if (std::string(argv[1]) == "-c" || std::string(argv[1]) == "-create") {
                FileSystem::create_directories("src");
                FileSystem::create_directories("test");
                FileSystem::create_directories("bin");
                FileSystem::create_directories("lib");
                FileSystem::create_directories("obj");
                FileSystem::create_directories("docs");
                FileSystem::create_directories("uml");
                std::ofstream base("src/main.cpp");
            }
        }

        if (argc == 1 || (argc >= 2 && (std::string(argv[1]) == "-a" || std::string(argv[1]) == "-analyse" || std::string(argv[1]) == "-c" || std::string(argv[1]) == "-create"))) {
            std::string config("config.nre");
            if (argc == 3) {
                std::string ext(argv[2]);
                if (ext.find("-s=") != std::string::npos) {
                    config = "config." + ext.substr(3) + ".nre";
                }
                if (ext.find("-switch=") != std::string::npos) {
                    config = "config." + ext.substr(8) + ".nre";
                }
            }

            NREB::Config::Config::setConfigPath(config);
            FileSystem::create_directories("src");
            NREB::IO::Folder src("src");

            NREB::IO::FileList files;
            NREB::IO::FolderList folders;

            src.createMakefile(files, folders);
            src.createProjectMakefile(files, folders);
            src.createArchiverScript(files);
        }

        if (argc >= 2 && (std::string(argv[1]) == "-t" || std::string(argv[1]) == "-test")) {
            std::string config("config.test.nre");
            if (argc == 3) {
                std::string ext(argv[2]);
                if (ext.find("-s=") != std::string::npos) {
                    config = "config.test." + ext.substr(3) + ".nre";
                }
                if (ext.find("-switch=") != std::string::npos) {
                    config = "config.test." + ext.substr(8) + ".nre";
                }
            }

            NREB::Config::Config::setConfigPath(config);
            FileSystem::create_directories("test");
            NREB::IO::Folder test("test");

            NREB::IO::FileList files;
            NREB::IO::FolderList folders;

            test.createMakefile(files, folders, "test");
            test.createProjectMakefile(files, folders, "test");
        }

        return 0;
    }
