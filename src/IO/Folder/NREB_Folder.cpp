
    /**
     * @file NREB_Folder.hpp
     * @brief Implementation of Builder's IO's Object : Folder
     * @author Louis ABEL
     * @date 18/03/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NREB_Folder.hpp"

    namespace FileSystem = std::experimental::filesystem;

    namespace NREB {
        namespace IO {

            Folder::Folder(std::string const& n, Entry* p) : Entry(n, p) {
                for (auto& path : FileSystem::directory_iterator(n)) {
                    if (FileSystem::is_regular_file(path.symlink_status())) {
                        if (path.path().string().find(MAKEFILE) == std::string::npos && !isExcluded(path.path().string())) {
                            childs.emplace_back(new File(path.path().string(), this));
                        }
                    } else {
                        childs.emplace_back(new Folder(path.path().string(), this));
                    }
                }
            }

            Folder::~Folder() {
                for (auto& e : childs) {
                    delete e;
                }
            }

            void Folder::createMakefile(FileList& files, FolderList& folders) const {
                if (hasDeepSources()) {
                    std::ofstream makefile(MARKER_SRC + getPath() + MAKEFILE);
                    bool hasFile = hasFileChild();
                    bool hasFolder = hasFolderChild();
                    if (hasFile) {
                        insertFileChilds(makefile, files);
                    }
                    if (hasFolder) {
                        insertFolderChilds(makefile, folders);
                    }
                    insertTarget(makefile, hasFolder, hasFile);
                    if (hasFolder) {
                        insertFolderCalls(makefile);
                    }
                    if (hasFile) {
                        insertFileCall(makefile);
                    }
                    for (auto& f : getFolderChild()) {
                        f->createMakefile(files, folders);
                    }
                }
            }

            void Folder::createProjectMakefile(FileList& files, FolderList& folders) const {
                std::ofstream makefile(MAKEFILE);

                const Config::Config& config = Config::Config::getConfig();

                makefile << "export " << MARKER_COMPILER << " = " << config.getCompiler() << '\n';
                makefile << "export " << MARKER_LINKER << " = " << config.getLinker() << "\n\n";
                makefile << "export " << MARKER_CFLAGS << " = " << config.getCFlags() << '\n';
                makefile << "export " << MARKER_LDFLAGS << " = " << config.getLdFlags() << "\n\n";
                makefile << "export " << MARKER_INC << " = ";

                for (std::string const& current : config.getIncludes()) {
                    makefile << "-I\"" << current << "\" ";
                }
                makefile << '\n';
                makefile << "export " << MARKER_LIB << " = ";

                for (std::string const& current : config.getLibs()) {
                    makefile << "\"" << current << "\" ";
                }
                makefile << '\n';
                makefile << "export " << MARKER_LIBDIR << " = ";

                for (std::string const& current : config.getLibDirs()) {
                    makefile << "-L\"" << current << "\" ";
                }
                makefile << "\n\n";
                makefile << MARKER_OBJDIR << " = obj/\n";
                makefile << MARKER_BIN << " = bin/\n";
                makefile << "SRC = " << MARKER_SRC << "\n";
                makefile << MARKER_OBJ << " = ";
                for (File* f : files) {
                    makefile << CALL_OBJDIR << f->getObjectPath() << " ";
                }
                makefile << "\n";
                makefile << "OUT = " << config.getOut() << "\n\n";
                makefile << MARKER_TARGET << " : " << MARKER_CHILDS << " " << MARKER_OUT << "\n\n";
                makefile << "childs :\n\t@(cd $(SRC) && $(MAKE))\n\n";
                makefile << MARKER_OUT << " : " << CALL_OBJ << "\n";
                makefile << "\t@$(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LDFLAGS) $(LIB)\n";
                makefile << "\t@echo \"Jobs done.\"\n\n";
                makefile << "clean : \n";
                makefile << "\t@echo \"Clear of obj/\"\n";
                makefile << "\t@rm -r obj\n";
                makefile << "\t@mkdir obj\n";
                for (Folder* f : folders) {
                    makefile << "\t@mkdir obj" << f->getPath() << "\n";
                }
                makefile << "\t@echo \"obj-Tree creation done.\"\n";
                makefile << "\t@echo \"Clean done.\"\n";
            }

            bool Folder::hasFileChild() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFile();
                    cnt++;
                }
                return find;
            }

            bool Folder::hasFolderChild() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFolder();
                    cnt++;
                }
                return find;
            }

            bool Folder::hasDeepSources() const {
                bool find = notOnlyHeaders();
                if (!find) {
                    for (auto& e : childs) {
                        if (e->isFolder()) {
                            find = find || static_cast <Folder*> (e)->hasDeepSources();
                        }
                    }
                }
                return find;
            }

            bool Folder::isFile() const {
                return false;
            }

            bool Folder::isFolder() const {
                return true;
            }

            bool Folder::notOnlyHeaders() const {
                bool res = false;
                for (auto& e : childs) {
                    if (e->isFile()) {
                        if (e->getName().find(MARKER_SOURCE) != std::string::npos || e->getName().find(MARKER_SOURCE_C) != std::string::npos) {
                            res = true;
                        }
                    }
                }
                return res;
            }

            FileList Folder::getSourceChild() const {
                FileList res;
                for (auto& e : childs) {
                    if (e->isFile() && (e->getName().find(MARKER_SOURCE) != std::string::npos || e->getName().find(MARKER_SOURCE_C) != std::string::npos)) {
                        res.emplace_back(static_cast <File*> (e));
                    }
                }
                return res;
            }

            FileList Folder::getHeaderChild() const {
                FileList res;
                for (auto& e : childs) {
                    if (e->isFile() && (e->getName().find(MARKER_HEADER) != std::string::npos || e->getName().find(MARKER_HEADER_C) != std::string::npos)) {
                        res.emplace_back(static_cast <File*> (e));
                    }
                }
                return res;
            }

            FolderList Folder::getFolderChild() const {
                FolderList res;
                for (auto& e : childs) {
                    if (e->isFolder()) {
                        res.emplace_back(static_cast <Folder*> (e));
                    }
                }
                return res;
            }

            std::string Folder::getBackwardPath() const {
                if (getParent() == nullptr) {
                    return "../";
                }
                return "../" + static_cast <const Folder*> (getParent())->getBackwardPath();
            }

            std::string Folder::getObjectPath() const {
                return getBackwardPath() + "obj" + getPath();
            }

            std::string Folder::getUpperName() const {
                std::string path(getName());
                std::transform(path.begin(), path.end(),path.begin(), ::toupper);
                return path;
            }

            bool Folder::hasCppSource() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFile() && childs[cnt]->getName().find(MARKER_SOURCE) != std::string::npos;
                    cnt++;
                }
                return find;
            }

            bool Folder::hasCppHeader() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFile() && childs[cnt]->getName().find(MARKER_HEADER) != std::string::npos;
                    cnt++;
                }
                return find;
            }

            bool Folder::hasCSource() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFile() && childs[cnt]->getName().find(MARKER_SOURCE_C) != std::string::npos && childs[cnt]->getName().find(MARKER_SOURCE) == std::string::npos;
                    cnt++;
                }
                return find;
            }

            bool Folder::hasCHeader() const {
                bool find = false;
                std::size_t cnt = 0;
                while (!find && cnt < childs.size()) {
                    find = childs[cnt]->isFile() && childs[cnt]->getName().find(MARKER_HEADER_C) != std::string::npos && childs[cnt]->getName().find(MARKER_HEADER) == std::string::npos;
                    cnt++;
                }
                return find;
            }

            void Folder::insertFileChilds(std::ofstream& file, FileList& files) const {
                file << MARKER_OBJ << " = ";
                for (auto& f : getSourceChild()) {
                    file << CALL_OBJDIR << f->getObjectName() << " ";
                    files.push_back(f);
                }
                file << '\n';
                file << MARKER_OBJDIR << " = " << getObjectPath() << "\n\n";
            }

            void Folder::insertFolderChilds(std::ofstream& file, FolderList& folders) const {
                for (auto& f : getFolderChild()) {
                    if (f->hasDeepSources()) {
                        file << f->getUpperName() << " = " << f->getName() << '\n';
                        folders.push_back(f);
                    }
                }
                file << '\n';
            }

            void Folder::insertTarget(std::ofstream& file, bool hasFolder, bool hasFile) const {
                file << MARKER_TARGET << " : ";
                if (hasFolder) {
                    file << MARKER_CHILDS << " ";
                }
                if (hasFile) {
                    file << CALL_OBJ;
                }
                file << "\n\n";
            }

            void Folder::insertFolderCalls(std::ofstream& file) const {
                file << MARKER_CHILDS << ":\n";
                for (auto& f : getFolderChild()) {
                    if (f->hasDeepSources()) {
                        file << "\t@(cd $(" << f->getUpperName() << ") && $(MAKE))\n";
                    }
                }
                file << '\n';
            }

            void Folder::insertFileCall(std::ofstream& file) const {
                file << CALL_OBJDIR << '%' << MARKER_O << " : ";
                if (hasCppSource()) {
                    file << " %" << MARKER_SOURCE;
                }
                if (hasCppHeader()) {
                    file << " %" << MARKER_HEADER;
                }
                if (hasCSource()) {
                    file << " %" << MARKER_SOURCE_C;
                }
                if (hasCHeader()) {
                    file << " %" << MARKER_HEADER_C;
                }
                file << "\n\t@" << CALL_COMPILER << " -o $@ -c $< " << CALL_CFLAGS << " " << CALL_INC;
            }

            bool Folder::isExcluded(std::string const& path) {
                for (std::string const& ex : Config::Config::getConfig().getExcluded()) {
                    if (path.find(ex) != std::string::npos) {
                        return true;
                    }
                }
                return false;
            }

        }
    }
