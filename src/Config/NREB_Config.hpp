
    /**
     * @file NREB_Config.hpp
     * @brief Declaration of Builder's Config's Object : Config
     * @author Louis ABEL
     * @date 08/05/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <string>
    #include <vector>
    #include <fstream>
    #include <iostream>
    #include <sstream>

    /**
     * @namespace NREB
     * @brief The NRE-Builder global namespace
     */
    namespace NREB {
        /**
         * @namespace Config
         * @brief Builder's Configuration module
         */
        namespace Config {

            /**
             * @class Config
             * @brief Represent the analyser configuration
             */
            class Config {
                private :   // Fields
                    std::string compiler;
                    std::string linker;
                    std::string archiver;
                    std::string cFlags;
                    std::string ldFlags;
                    std::string out;
                    std::vector<std::string> includes;
                    std::vector<std::string> libs;
                    std::vector<std::string> libDirs;
                    std::vector<std::string> excluded;

                public :   // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        Config() = delete;

                    //## Copy Constructor ##//
                        /**
                         * Copy forbidden
                         * @param c the configuration to copy
                         */
                        Config(Config const& c) = delete;

                    //## Move Constructor ##//
                        /**
                         * Move forbidden
                         * @param c the configuration to move
                         */
                        Config(Config && c) = delete;

                    //## Deconstructor ##//
                        /**
                         * Config Deconstructor
                         */
                        ~Config() = default;

                    //## Getter ##//
                        /**
                         * @return the configuration compiler
                         */
                        std::string const& getCompiler() const;
                        /**
                         * @return the configuration linker
                         */
                        std::string const& getLinker() const;
                        /**
                         * @return the configuration archiver
                         */
                        std::string const& getArchiver() const;
                        /**
                         * @return the configuration cFlags
                         */
                        std::string const& getCFlags() const;
                        /**
                         * @return the configuration ldFlags
                         */
                        std::string const& getLdFlags() const;
                        /**
                         * @return the configuration out
                         */
                        std::string const& getOut() const;
                        /**
                         * @return the configuration includes
                         */
                        std::vector<std::string> const& getIncludes() const;
                        /**
                         * @return the configuration libs
                         */
                        std::vector<std::string> const& getLibs() const;
                        /**
                         * @return the configuration lib directories
                         */
                        std::vector<std::string> const& getLibDirs() const;
                        /**
                         * @return the configuration excluded files
                         */
                        std::vector<std::string> const& getExcluded() const;

                    //## Assignment Operator ##//
                        /**
                         * Copy forbidden
                         * @param c the object to copy into this
                         * @return  the reference of himself
                         */
                        Config& operator =(Config const& c) = delete;
                        /**
                         * Move forbidden
                         * @param c the object to move into this
                         * @return  the reference of himself
                         */
                        Config& operator =(Config && c) = delete;

                private :    // Methods
                    /**
                     * Construct the configuration
                     * @param configPath the configuration file path
                     */
                    Config(std::string const& configPath);
                    /**
                     * Remove configuration input lines
                     * @param includesLine the line contaning all includes
                     * @param libsLine     the line contaning all libraries
                     * @param libDirsLine  the line contaning all library directories
                     * @param excludedLine the line contaning all excluded files
                     */
                    void removeTags(std::string& includesLine, std::string& libsLine, std::string& libDirsLine, std::string& excludedLine);

                public :     // Static
                    /**
                     * Set the configuration file path
                     * @param configPath the configuration path
                     */
                    static void setConfigPath(std::string const& configPath);
                    /**
                     * @return the configuration instance
                     */
                    static Config const& getConfig();

                private :    // Static
                    static std::string configFilePath;

                public :     // Static
                    static const std::string TAG_COMPILER;
                    static const std::string TAG_LINKER;
                    static const std::string TAG_ARCHIVER;
                    static const std::string TAG_CFLAGS;
                    static const std::string TAG_LDFLAGS;
                    static const std::string TAG_INC;
                    static const std::string TAG_LIB;
                    static const std::string TAG_LIBDIR;
                    static const std::string TAG_OUT;
                    static const std::string TAG_EXCLUDED;
            };
        }
    }
