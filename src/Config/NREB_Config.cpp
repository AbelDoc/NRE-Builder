
    /**
     * @file NREB_Config.cpp
     * @brief Implementation of Builder's Config's Object : Config
     * @author Louis ABEL
     * @date 08/05/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NREB_Config.hpp"

    namespace NREB {
        namespace Config {

            std::string Config::configFilePath = "";
            const std::string Config::TAG_COMPILER    = "compiler=";
            const std::string Config::TAG_LINKER      = "linker=";
            const std::string Config::TAG_ARCHIVER    = "archiver=";
            const std::string Config::TAG_CFLAGS      = "cflags=";
            const std::string Config::TAG_LDFLAGS     = "ldflags=";
            const std::string Config::TAG_INC         = "includes=";
            const std::string Config::TAG_LIB         = "lib=";
            const std::string Config::TAG_LIBDIR      = "libdir=";
            const std::string Config::TAG_OUT         = "out=";
            const std::string Config::TAG_EXCLUDED    = "excluded=";

            Config::Config(std::string const& configPath) {
                std::ifstream config(configPath);
                if (config.fail()) {
                    std::cout << configPath << " : Missing or Corrupted config file" << std::endl;
                    std::exit(-1);
                }
                std::string includesLine, libsLine, libDirsLine, excludedLine, current;
                std::getline(config, compiler);
                std::getline(config, linker);
                std::getline(config, archiver);
                std::getline(config, cFlags);
                std::getline(config, ldFlags);
                std::getline(config, includesLine);
                std::getline(config, libsLine);
                std::getline(config, libDirsLine);
                std::getline(config, out);
                std::getline(config, excludedLine);

                removeTags(includesLine, libsLine, libDirsLine, excludedLine);

                std::stringstream parserInc(includesLine);
                while (std::getline(parserInc, current, ' ')) {
                    includes.push_back(current);
                }

                std::stringstream parserLibs(libsLine);
                while (std::getline(parserLibs, current, ' ')) {
                    libs.push_back(current);
                }

                std::stringstream parserLibDirs(libDirsLine);
                while (std::getline(parserLibDirs, current, ' ')) {
                    libDirs.push_back(current);
                }
                std::stringstream parserExc(excludedLine);
                while (std::getline(parserExc, current, ' ')) {
                    excluded.push_back(current);
                }
            }

            void Config::removeTags(std::string& includesLine, std::string& libsLine, std::string& libDirsLine, std::string& excludedLine) {
                compiler.replace(0, TAG_COMPILER.length(), "");
                linker.replace(0, TAG_LINKER.length(), "");
                archiver.replace(0, TAG_ARCHIVER.length(), "");
                cFlags.replace(0, TAG_CFLAGS.length(), "");
                ldFlags.replace(0, TAG_LDFLAGS.length(), "");
                includesLine.replace(0, TAG_INC.length(), "");
                libsLine.replace(0, TAG_LIB.length(), "");
                libDirsLine.replace(0, TAG_LIBDIR.length(), "");
                out.replace(0, TAG_OUT.length(), "");
                excludedLine.replace(0, TAG_EXCLUDED.length(), "");
            }

            std::string const& Config::getCompiler() const {
                return compiler;
            }

            std::string const& Config::getLinker() const {
                return linker;
            }

            std::string const& Config::getArchiver() const {
                return archiver;
            }

            std::string const& Config::getCFlags() const {
                return cFlags;
            }

            std::string const& Config::getLdFlags() const {
                return ldFlags;
            }

            std::string const& Config::getOut() const {
                return out;
            }

            std::vector<std::string> const& Config::getIncludes() const {
                return includes;
            }

            std::vector<std::string> const& Config::getLibs() const {
                return libs;
            }

            std::vector<std::string> const& Config::getLibDirs() const {
                return libDirs;
            }

            std::vector<std::string> const& Config::getExcluded() const {
                return excluded;
            }

            void Config::setConfigPath(std::string const& configPath) {
                configFilePath = configPath;
            }

            Config const& Config::getConfig() {
                static Config instance(configFilePath);
                return instance;
            }

        }
    }
