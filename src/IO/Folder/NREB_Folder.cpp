
    #include "NREB_Folder.hpp"


    namespace FileSystem = std::experimental::filesystem;

    namespace NREB {
        namespace IO {

            Folder::Folder(std::string const& n, Entry* p) : Entry(n, p) {
                for (auto& path : FileSystem::directory_iterator(n)) {
                    if (FileSystem::is_regular_file(path.symlink_status())) {
                        if (path.path().string().find(MAKEFILE) == std::string::npos) {
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
                    f->createMakefile();
                }
            }

            void Folder::createProjectMakefile(FileList& files, FolderList& folders) const {
                std::ofstream makefile(MAKEFILE);
                std::ifstream config(CONFIG);
                if (config.fail()) {
                    std::cout << "Missing or Corrupted config file" << std::endl;
                }
                makefile <<
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

            bool Folder::isFile() const {
                return false;
            }

            bool Folder::isFolder() const {
                return true;
            }

            FileList Folder::getSourceChild() const {
                FileList res;
                for (auto& e : childs) {
                    if (e->isFile() && e->getName().find(MARKER_SOURCE) != std::string::npos) {
                        res.emplace_back(static_cast <File*> (e));
                    }
                }
                return res;
            }

            FileList Folder::getHeaderChild() const {
                FileList res;
                for (auto& e : childs) {
                    if (e->isFile() && e->getName().find(MARKER_HEADER) != std::string::npos) {
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

            bool Folder::sourceHasHeader() const {
                FileList sources = getSourceChild();
                FileList headers = getHeaderChild();
                bool find = true;
                std::size_t cnt = 0;
                while (find && cnt < sources.size()) {
                    bool hasHeader = false;
                    std::size_t cntH = 0;
                    std::string srcName = sources[cnt]->getName();
                    srcName.replace(srcName.find(MARKER_SOURCE), MARKER_SOURCE.length(), "");
                    while (!hasHeader && cntH < headers.size()) {
                        hasHeader = headers[cntH]->getName().find(srcName) != std::string::npos;
                        cntH++;
                    }
                    find = hasHeader;
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
                    file << f->getUpperName() << " = " << f->getName() << '\n';
                    folders.push_back(f);
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
                    file << "\t@(cd $(" << f->getUpperName() << ") && $(MAKE))\n";
                }
                file << '\n';
            }

            void Folder::insertFileCall(std::ofstream& file) const {
                file << CALL_OBJDIR << '%' << MARKER_O << " : %" << MARKER_SOURCE;
                if (sourceHasHeader()) {
                    file << " %" << MARKER_HEADER;
                }
                file << "\n\t@" << CALL_COMPILER << " -o $@ -c $< " << CALL_CFLAGS << " " << CALL_INC;
            }

        }
    }
