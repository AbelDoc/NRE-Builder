
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <experimental/filesystem>

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
             * @class Entry
             * @brief Represent a system entry
             */
            class Entry {
                private :   // Fields
                    std::string name;   /**< The entry's name */
                    Entry* parent;      /**< The entry's parent */

                public:     // Methods
                    //## Constructor ##//
                        /**
                         * Construct an entry
                         * @param n the entry's name
                         * @param p the entry's parent
                         */
                        Entry(std::string const& n, Entry* p = nullptr);

                    //## Deconstructor ##//
                        /**
                         * Entry deconstructor
                         */
                        virtual ~Entry() = default;

                    //## Methods ##//
                        /**
                         * Get the entry's path
                         * @return the computed path
                         */
                        std::string getPath() const;
                        /**
                         * @return the entry's name
                         */
                        std::string const& getName() const;
                        /**
                         * @return the entry's parent
                         */
                        const Entry* getParent() const;
                        /**
                         * @return if the entry is a file
                         */
                        virtual bool isFile() const = 0;
                        /**
                         * @return if the folder is a folder
                         */
                        virtual bool isFolder() const = 0;

                public:     // static const
                    static const std::string MARKER_HEADER;
                    static const std::string MARKER_COMPILER;
                    static const std::string MARKER_CFLAGS;
                    static const std::string MARKER_INC;
                    static const std::string MARKER_CHILDS;
                    static const std::string MARKER_OUT;
                    static const std::string MARKER_TARGET;
                    static const std::string MARKER_OBJ;
                    static const std::string MARKER_SRC;
                    static const std::string MARKER_SOURCE;
                    static const std::string MARKER_O;
                    static const std::string MARKER_OBJDIR;
                    static const std::string START_CALL;
                    static const std::string END_CALL;
                    static const std::string CALL_COMPILER;
                    static const std::string CALL_CFLAGS;
                    static const std::string CALL_INC;
                    static const std::string CALL_OBJDIR;
                    static const std::string CALL_OBJ;
                    static const std::string MAKEFILE;
                    static const std::string CONFIG;
            };

            class File;
            class Folder;

            typedef std::vector<File*>      FileList;
            typedef std::vector<Entry*>     EntryList;
            typedef std::vector<Folder*>    FolderList;
        }
    }
