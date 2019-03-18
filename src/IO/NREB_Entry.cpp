
    #include "NREB_Entry.hpp"

    namespace NREB {
        namespace IO {
            const std::string Entry::MARKER_HEADER   = ".hpp";
            const std::string Entry::MARKER_COMPILER = "CXX";
            const std::string Entry::MARKER_CFLAGS   = "CFLAGS";
            const std::string Entry::MARKER_INC      = "INC";
            const std::string Entry::MARKER_CHILDS   = "childs";
            const std::string Entry::MARKER_OUT      = "out";
            const std::string Entry::MARKER_TARGET   = "all";
            const std::string Entry::MARKER_OBJ      = "OBJ";
            const std::string Entry::MARKER_SRC      = "src";
            const std::string Entry::MARKER_SOURCE   = ".cpp";
            const std::string Entry::MARKER_O        = ".o";
            const std::string Entry::MARKER_OBJDIR   = "OBJDIR";
            const std::string Entry::START_CALL      = "$(";
            const std::string Entry::END_CALL        = ")";
            const std::string Entry::CALL_COMPILER   = START_CALL + MARKER_COMPILER + END_CALL;
            const std::string Entry::CALL_CFLAGS     = START_CALL + MARKER_CFLAGS + END_CALL;
            const std::string Entry::CALL_INC        = START_CALL + MARKER_INC + END_CALL;
            const std::string Entry::CALL_OBJDIR     = START_CALL + MARKER_OBJDIR + END_CALL;
            const std::string Entry::CALL_OBJ        = START_CALL + MARKER_OBJ + END_CALL;
            const std::string Entry::MAKEFILE        = "Makefile";
            const std::string Entry::CONFIG          = "config.nre";

            Entry::Entry(std::string const& n, Entry* p) : name(n), parent(p) {
                std::size_t it = name.find("\\");
                while (it != std::string::npos) {
                    name.replace(0, it + 1, "");
                    it = name.find("\\");
                }
            }

            std::string const& Entry::getName() const {
                return name;
            }

            const Entry* Entry::getParent() const {
                return parent;
            }

            std::string Entry::getPath() const {
                if (!parent) {
                    return "/";
                }
                return parent->getPath() + name + "/";
            }
        }
    }
