#ifndef TXTPARSER_H
#define TXTPARSER_H

#include <QObject>
#include "src/core/Protocols/Messages.h"

class TxtParser : public QObject{
    Q_OBJECT
public :
    explicit TxtParser(QObject* parent = nullptr);
    void parseFile(const QString& path, const QString& fileName);
signals :
    void FileParsed(SequenceParameters parameters);
};

#endif // TXTPARSER_H
