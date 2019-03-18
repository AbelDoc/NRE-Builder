
    #include <vector>
    #include <fstream>
    #include <sstream>
    #include "../NREB_Entry.hpp"
    #include "../File/NREB_File.hpp"

    #pragma once

    /**
     * @namespace NREB
     * @brief The NRE-Builder global namespace
     */
    namespace NREB {
        /**
         * @namespace IO
         * @brief Builder's IO module
         */
        namespace IO {

            /**
             * @class Folder
             * @brief Represent a folder entry
             */
            class Folder : public Entry {
                private :   // Fields
                    EntryList childs;

                public:     // Methods
                    //## Constructor ##//
                        /**
                         * Construct an entry
                         * @param n the entry's name
                         * @param p the entry's parent
                         */
                        Folder(std::string const& n, Entry* p = nullptr);

                    //## Deconstructor ##//
                        /**
                         * Entry deconstructor
                         */
                         ~Folder();

                    //## Methods ##//
                        /**
                         * Create the entry corresponding makefile
                         * @param files   list containing all explorated files
                         * @param folders list containing all explorated folders
                         */
                        void createMakefile(FileList& files, FolderList& folders) const;
                        /**
                         * Create the project main makefile
                         * @param files   list containing all explorated files
                         * @param folders list containing all explorated folders
                         */
                        void createProjectMakefile(FileList& files, FolderList& folders) const;
                        /**
                         * @return if the entry has file childs
                         */
                        bool hasFileChild() const;
                        /**
                         * @return if the entry has folder childs
                         */
                        bool hasFolderChild() const;
                        /**
                         * @return if the entry is a file
                         */
                        bool isFile() const override;
                        /**
                         * @return if the folder is a folder
                         */
                        bool isFolder() const override;
                        /**
                         * Get all source file child in a vector
                         * @return the child's vector
                         */
                        FileList getSourceChild() const;
                        /**
                         * Get all header file child in a vector
                         * @return the child's vector
                         */
                        FileList getHeaderChild() const;
                        /**
                         * Get all folder child in a vector
                         * @return the child's vector
                         */
                        FolderList getFolderChild() const;
                        /**
                         * @return the path to return to src
                         */
                        std::string getBackwardPath() const;
                        /**
                         * @return the object path
                         */
                        std::string getObjectPath() const;
                        /**
                         * @return the entry name in upper case
                         */
                        std::string getUpperName() const;
                        /**
                         * @return if all sources has their headers
                         */
                        bool sourceHasHeader() const;
                        /**
                         * Insert header to declare file compilation
                         * @param file  the file output
                         * @param files list containing all explorated files
                         */
                        void insertFileChilds(std::ofstream& file, FileList& files) const;
                        /**
                         * Insert folder declaration
                         * @param file    the file output
                         * @param folders list containing all explorated file
                         */
                        void insertFolderChilds(std::ofstream& file, FolderList& folders) const;
                        /**
                         * Insert compilation target
                         * @param file      the file output
                         * @param hasFolder tell if the entry has folder childs
                         * @param hasFile   tell if the entry has file childs
                         */
                        void insertTarget(std::ofstream& file, bool hasFolder, bool hasFile) const;
                        /**
                         * Insert folder compilation call
                         * @param file the file output
                         */
                        void insertFolderCalls(std::ofstream& file) const;
                        /**
                         * Insert file compilation call
                         * @param file the file output
                         */
                        void insertFileCall(std::ofstream& file) const;
            };
        }
    }
