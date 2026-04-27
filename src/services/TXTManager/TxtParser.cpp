#include <QFile>
#include <QTextStream>
#include "TxtParser.h"

TxtParser::TxtParser(QObject* parent) : QObject(parent){}

void TxtParser::parseFile(const QString& path, const QString& fileName){
    QFile file(path+"/"+fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    // Read content
    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    file.close();

    SequenceParameters parameters;
    for (const QString& line : lines) {
        QStringList parts = line.split(",");
        if (parts.size() >= 2) { // Ensure at least title and value exist
            QString title = parts[0].trimmed();
            QString valueStr = parts[1].trimmed();
            QString unit = (parts.size() >= 3) ? parts[2].trimmed() : " ";  // Assign space if unit is missing

            bool ok;
            int value = valueStr.toInt(&ok);
            if (ok) {
                parameters.push_back({title.toStdString(), value, unit.toStdString()});
            }
        }
    }
    emit FileParsed(parameters);
}

