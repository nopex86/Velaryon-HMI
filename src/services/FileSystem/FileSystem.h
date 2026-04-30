#pragma once
#include <QObject>

/**
 * @file FileSystem.h
 * @brief File system allow the managment of files path used
 * in the application.
 * @ingroup Storage
 */

/**
 * @brief File system allow the managment of files path used
 * in the application.
 * @details Responsibiliies :
 *  - Storing file path.
 *  - Verifying the integrity of the file system.
 *    (Not currently done)
 *  - Providing files path to the rest of the app.
 */
class FileSystem : public QObject{
    Q_OBJECT
public :
    FileSystem(QObject* parent);

    /**
     * @brief Allow to get the path to the path to a directory.
     * @param name Name of the path, as registered.
     * @param path Pointer to the path.
     * @return
     */
    bool getDirectory(const std::string& name,
                      std::string* path);
private :


    /**
     * @brief Add path to a directory in the list.
     * @param name Name of the directory
     * @param path Path to the directory
     */
    void addDirectory(const std::string& name,
                      const std::string& path);

    /**
     * @brief List that contain the paths and their names.
     */
    std::unordered_map<std::string, std::string> m_pathList;
};
