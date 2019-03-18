
    #include <vector>
    #include <fstream>
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
                    std::vector<Entry*> childs;

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
                         */
                        void createMakefile() const;
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
                        std::vector<File*> getSourceChild() const;
                        /**
                         * Get all header file child in a vector
                         * @return the child's vector
                         */
                        std::vector<File*> getHeaderChild() const;
                        /**
                         * Get all folder child in a vector
                         * @return the child's vector
                         */
                        std::vector<Folder*> getFolderChild() const;
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
                         * @param file the file output
                         */
                        void insertFileChilds(std::ofstream& file) const;
                        /**
                         * Insert folder declaration
                         * @param file the file output
                         */
                        void insertFolderChilds(std::ofstream& file) const;
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
