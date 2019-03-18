
    /**
     * @file NREB_File.hpp
     * @brief Declaration of Builder's IO's Object : File
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright GNU GPL v3
     */

    #include "../NREB_Entry.hpp"

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
             * @class File
             * @brief Represent a file entry
             */
            class File : public Entry {
                private :   // Fields

                public:     // Methods
                    //## Constructor ##//
                        /**
                         * Construct an entry
                         * @param n the entry's name
                         * @param p the entry's parent
                         */
                        File(std::string const& n, Entry* p = nullptr);

                    //## Deconstructor ##//
                        /**
                         * Entry deconstructor
                         */
                         ~File() = default;

                    //## Methods ##//
                        /**
                         * @return if the entry is a file
                         */
                        bool isFile() const override;
                        /**
                         * @return if the folder is a folder
                         */
                        bool isFolder() const override;
                        /**
                         * @return the object's file name
                         */
                        std::string getObjectName() const;
                        /**
                         * @return the object's file path
                         */
                        std::string getObjectPath() const;
            };
        }
    }
