
    /**
     * @file NREB_Folder.hpp
     * @brief Declaration of Builder's IO's Object : Folder
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright CC-BY-NC-SA
     */

    #include <vector>
    #include <fstream>
    #include <sstream>

    #include "../NREB_Entry.hpp"
    #include "../File/NREB_File.hpp"
    #include "../../Config/NREB_Config.hpp"

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
                    EntryList childs;       /**< Folder's childs */

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
                         * Analyse the folder
                         */
                        void analyse();
                        /**
                         * Create the entry corresponding makefile
                         * @param files   list containing all explorated files
                         * @param folders list containing all explorated folders
                         * @param src     the source directory
                         */
                        void createMakefile(FileList& files, FolderList& folders, std::string const& src = "src") const;
                        /**
                         * Create the project main makefile
                         * @param files   list containing all explorated files
                         * @param folders list containing all explorated folders
                         * @param src     the source directory
                         */
                        void createProjectMakefile(FileList& files, FolderList& folders, std::string const& src = "src") const;
                        /**
                         * Create a bash script to create object archive
                         * @param files list containing all explorated files
                         */
                        void createArchiverScript(FileList& files) const;
                        /**
                         * @return if the entry has file childs
                         */
                        bool hasFileChild() const;
                        /**
                         * @return if the entry has folder childs
                         */
                        bool hasFolderChild() const;
                        /**
                         * @return if the entry has deep sources
                         */
                        bool hasDeepSources() const;
                        /**
                         * @return if the entry is a file
                         */
                        bool isFile() const override;
                        /**
                         * @return if the folder is a folder
                         */
                        bool isFolder() const override;
                        /**
                         * @return if the folder is not only composed of headers
                         */
                        bool notOnlyHeaders() const;
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
                         * @return if the folder contains cpp sources
                         */
                        bool hasCppSource() const;
                        /**
                         * @return if the folder contains cpp header
                         */
                        bool hasCppHeader() const;
                        /**
                         * @return if the folder contains c sources
                         */
                        bool hasCSource() const;
                        /**
                         * @return if the folder contains c header
                         */
                        bool hasCHeader() const;
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
                        /**
                         * Check if a path is excluded
                         * @param  path the path to check
                         * @return      the test result
                         */
                        bool isExcluded(std::string const& path);
            };
        }
    }
