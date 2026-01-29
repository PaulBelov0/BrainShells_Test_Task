#ifndef ARCHIVE_MANAGER_H
#define ARCHIVE_MANAGER_H

#include <QObject>
#include <QDir>
#include <QDirIterator>

#include <archive.h>
#include <archive_entry.h>

enum class CompressionType {
    Seven_Z,
    ZIP,
    TAR,
    ISO,
    XAR,
    WARC,
    CPIO
};

class ArchiveManager : public QObject
{
    Q_OBJECT
public:
    explicit ArchiveManager(QObject *parent = nullptr);

    static CompressionType getCompressionTypeFromIndex(int index);

    void compress(QString sourcePath, QString destinationPath, CompressionType comprType);
    bool extract(QString archivePath, QString destinationPath);
    QString getSupportedArchiveFormats();
    QStringList getAvailableCompressions();
signals:
    void extractionFinished();
    void compressionFinished();
};

#endif // ARCHIVE_MANAGER_H
