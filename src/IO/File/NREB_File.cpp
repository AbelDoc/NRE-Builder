
    /**
     * @file NREB_File.hpp
     * @brief Implementation of Builder's IO's Object : File
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NREB_File.hpp"

    namespace NREB {
        namespace IO {

            File::File(std::string const& n, Entry* p) : Entry(n, p) {
            }

            bool File::isFile() const {
                return true;
            }

            bool File::isFolder() const {
                return false;
            }

            std::string File::getObjectName() const {
                std::string res(getName());
                std::size_t start = res.find(MARKER_SOURCE);
                if (start != std::string::npos) {
                    res.replace(start, MARKER_SOURCE.length(), MARKER_O);
                } else {
                    start = res.find(MARKER_SOURCE_C);
                    if (start != std::string::npos) {
                        res.replace(start, MARKER_SOURCE_C.length(), MARKER_O);
                    }  else {
                        res = "";
                    }
                }
                return res;
            }

            std::string File::getObjectPath() const {
                std::string path = getPath();
                path.replace(path.find(getName()), getName().length() + 1, getObjectName());
                path.replace(0, 1, "");
                return path;
            }
        }
    }
