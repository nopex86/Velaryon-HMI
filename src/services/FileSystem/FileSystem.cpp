#include "FileSystem.h"

FileSystem::FileSystem(QObject* parent) : QObject(parent){
    addDirectory("statesDatas", "./outputs/testbench_status");
    addDirectory("ui_pictures", "./pictures");
    addDirectory("sequences", "./sequences");
}

void FileSystem::addDirectory(const std::string& name,
                              const std::string& path){
    m_pathList[name] = path;
}

bool FileSystem::getDirectory(const std::string& name,
                              std::string* path){
    auto it = m_pathList.find(name);
    if (it == m_pathList.end()){
        return false;
    }
    *path = it->second;
    return true;
}
