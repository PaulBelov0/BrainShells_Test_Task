#include "archive_manager.h"

ArchiveManager::ArchiveManager(QObject *parent)
    : QObject{parent}
{}

QStringList ArchiveManager::getAvailableCompressions()
{
    struct archive* a = archive_write_new();

    QStringList formatList;

    if (archive_write_set_format_7zip(a) == ARCHIVE_OK) formatList.append(QString("7-Zip (*.7z)"));
    if (archive_write_set_format_zip(a) == ARCHIVE_OK) formatList.append(QString("ZIP (*.zip)"));
    if (archive_write_set_format_gnutar(a) == ARCHIVE_OK) formatList.append(QString("TAR (*.tar)"));
    if (archive_write_set_format_iso9660(a) == ARCHIVE_OK) formatList.append(QString("ISO (*.iso)"));
    if (archive_write_set_format_xar(a) == ARCHIVE_OK) formatList.append(QString("XAR (*.xar)"));
    if (archive_write_set_format_warc(a) == ARCHIVE_OK) formatList.append(QString("WARC (*.warc)"));
    if (archive_write_set_format_cpio(a) == ARCHIVE_OK) formatList.append(QString("CPIO (*.cpio)"));

    archive_write_free(a);
    return formatList;
}

CompressionType ArchiveManager::getCompressionTypeFromIndex(int index)
{
    switch(index)
    {
    case 0: return CompressionType::Seven_Z;
    case 1: return CompressionType::ZIP;
    case 2: return CompressionType::TAR;
    case 3: return CompressionType::ISO;
    case 4: return CompressionType::XAR;
    case 5: return CompressionType::WARC;
    case 6: return CompressionType::CPIO;
    }
    return CompressionType::Seven_Z;
}

QString ArchiveManager::getSupportedArchiveFormats()
{
    QString formats;
    struct archive* a = archive_write_new();

    QStringList formatList;

    if (archive_write_set_format_7zip(a) == ARCHIVE_OK) formatList.append(QString("7-Zip (*.7z)"));
    if (archive_write_set_format_zip(a) == ARCHIVE_OK) formatList.append(QString("ZIP (*.zip)"));
    if (archive_write_set_format_gnutar(a) == ARCHIVE_OK) formatList.append(QString("TAR (*.tar)"));
    if (archive_write_set_format_iso9660(a) == ARCHIVE_OK) formatList.append(QString("ISO (*.iso)"));
    if (archive_write_set_format_xar(a) == ARCHIVE_OK) formatList.append(QString("XAR (*.xar)"));
    if (archive_write_set_format_warc(a) == ARCHIVE_OK) formatList.append(QString("WARC (*.warc)"));
    if (archive_write_set_format_cpio(a) == ARCHIVE_OK) formatList.append(QString("CPIO (*.cpio)"));


    if (!formatList.isEmpty())
    {
        formats = formatList.join(";;");
    }
    else
    {
        formats = "All files (*.*)";
    }

    archive_write_free(a);
    return formats;
}

bool ArchiveManager::extract(QString archivePath, QString destinationPath)
{
    qDebug() << "Save Path:" << destinationPath;
    qDebug() << "Archive Path:" << archivePath;

    QDir().mkpath(destinationPath);

    struct archive *a = archive_read_new();
    struct archive *ext = archive_write_disk_new();
    struct archive_entry *entry;
    int r;

    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    if (archive_read_open_filename(a, archivePath.toLocal8Bit().constData(), 10240) != ARCHIVE_OK) return false;

    QString oldPath = QDir::currentPath();
    QDir::setCurrent(destinationPath);

    bool success = true;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
    {
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK)
        {
            qDebug() << "Header error:" << archive_error_string(ext);
        }
        else
        {
            const void *buff;
            size_t size;
            la_int64_t offset;

            while (true)
            {
                r = archive_read_data_block(a, &buff, &size, &offset);

                if (r == ARCHIVE_EOF) break;

                if (r != ARCHIVE_OK)
                {
                    qDebug() << "Data error:" << archive_error_string(a);
                    success = false;
                    break;
                }
                archive_write_data_block(ext, buff, size, offset);
            }
            archive_write_finish_entry(ext);
        }
    }

    QDir::setCurrent(oldPath);
    archive_read_close(a);
    archive_read_free(a);
    archive_write_close(ext);
    archive_write_free(ext);

    emit extractionFinished();

    return success;
}

void ArchiveManager::compress(QString sourcePath, QString destPath, CompressionType comprType)
{
    QString destinationPath = destPath;

    switch(comprType)
    {
    case CompressionType::Seven_Z:
        destinationPath += ".7z";
        break;
    case CompressionType::ZIP:
        destinationPath += ".zip";
        break;
    case CompressionType::CPIO:
        destinationPath += ".cpio";
        break;
    case CompressionType::ISO:
        destinationPath += ".iso";
        break;
    case CompressionType::TAR:
        destinationPath += ".tar";
        break;
    case CompressionType::WARC:
        destinationPath += ".warc";
        break;
    case CompressionType::XAR:
        destinationPath += ".xar";
        break;
    }

    qDebug() << "Source path:" << sourcePath;
    qDebug() << "Destination path:" << destinationPath;

    QFileInfo sourceInfo(sourcePath);
    if (!sourceInfo.exists())
    {
        qDebug() << "Source path does not exist!";
        emit compressionFinished();
        return;
    }

    struct archive* a;
    struct archive_entry* entry;
    char buff[8192];
    int len;

    a = archive_write_new();

    switch (comprType)
    {
    case CompressionType::Seven_Z: archive_write_set_format_7zip(a); break;
    case CompressionType::ZIP: archive_write_set_format_zip(a); break;
    case CompressionType::TAR: archive_write_set_format_gnutar(a); break;
    case CompressionType::ISO: archive_write_set_format_iso9660(a); break;
    case CompressionType::XAR: archive_write_set_format_xar(a); break;
    case CompressionType::WARC: archive_write_set_format_warc(a); break;
    case CompressionType::CPIO: archive_write_set_format_cpio(a); break;
    }

    // For 7-z and zip
    if (comprType != CompressionType::ZIP && comprType != CompressionType::Seven_Z)
    {
        archive_write_add_filter_gzip(a);
    }

    if (archive_write_open_filename(a, destinationPath.toLocal8Bit().constData()) != ARCHIVE_OK)
    {
        qDebug() << "Failed to open archive file for writing";
        archive_write_free(a);
        emit compressionFinished();
        return;
    }

    if (sourceInfo.isFile())
    {
        qDebug() << "Compressing single file";

        QFile file(sourcePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Cannot open source file";
            archive_write_close(a);
            archive_write_free(a);
            emit compressionFinished();
            return;
        }

        entry = archive_entry_new();
        archive_entry_set_pathname(entry, sourceInfo.fileName().toLocal8Bit().constData());
        archive_entry_set_size(entry, file.size());
        archive_entry_set_filetype(entry, AE_IFREG);
        archive_entry_set_perm(entry, 0644);
        archive_entry_set_mtime(entry, sourceInfo.lastModified().toSecsSinceEpoch(), 0);

        if (archive_write_header(a, entry) == ARCHIVE_OK)
        {
            while ((len = file.read(buff, sizeof(buff))) > 0)
            {
                archive_write_data(a, buff, len);
            }
            archive_write_finish_entry(a);
        }

        archive_entry_free(entry);
        file.close();
    }
    // For directory
    else if (sourceInfo.isDir())
    {
        qDebug() << "Compressing directory";

        QDirIterator it(sourcePath, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        QDir rootDir(sourcePath);
        int fileCount = 0;

        while (it.hasNext())
        {
            fileCount++;
            QString filePath = it.next();
            QString relativePath = rootDir.relativeFilePath(filePath);

            qDebug() << "File #" << fileCount << ":" << relativePath;

            QFile file(filePath);
            if (!file.open(QIODevice::ReadOnly))
            {
                qDebug() << "  Skipping, cannot open";
                continue;
            }

            entry = archive_entry_new();

            archive_entry_set_pathname(entry, relativePath.toLocal8Bit().constData());
            archive_entry_set_size(entry, file.size());
            archive_entry_set_filetype(entry, AE_IFREG);
            archive_entry_set_perm(entry, 0644);
            archive_entry_set_mtime(entry, QFileInfo(filePath).lastModified().toSecsSinceEpoch(), 0);

            if (archive_write_header(a, entry) == ARCHIVE_OK)
            {
                while ((len = file.read(buff, sizeof(buff))) > 0)
                {
                    archive_write_data(a, buff, len);
                }
                archive_write_finish_entry(a);
            } else {
                qDebug() << "  Failed to write header";
            }

            archive_entry_free(entry);
            file.close();
        }

        qDebug() << "Total files processed:" << fileCount;
    }

    archive_write_close(a);
    archive_write_free(a);

    qDebug() << "Compression finished. Archive:" << destinationPath;
    qDebug() << "Archive size:" << QFileInfo(destinationPath).size() << "bytes";

    emit compressionFinished();
}
