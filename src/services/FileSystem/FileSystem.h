#pragma once
#include <QObject>

class FileSystem : public QObject{
    Q_OBJECT
private :
    std::unordered_map<std::string, std::string> m_pathList;
public :
    FileSystem(QObject* parent) : QObject(parent){
        addDirectory("statesDatas", "./outputs/testbench_status");
        addDirectory("ui_pictures", "./pictures");
        addDirectory("sequences", "./sequences");
    }
    void addDirectory(const std::string& name, const std::string& path){
        m_pathList[name] = path;
    }
    bool getDirectory(const std::string& name, std::string* path){
        auto it = m_pathList.find(name);
        if (it == m_pathList.end()){
            return false;
        }
        *path = it->second;
        return true;
    }
};
