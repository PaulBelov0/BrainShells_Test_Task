#include "file_selector.h"

FileSelector::FileSelector(SelectionType type, QWidget *parent)
    : QWidget{parent}
{
    m_type = type;
    m_layout = new QHBoxLayout(this);

    m_path = new QLineEdit(this);
    m_path->setEnabled(false);
    QPushButton* fileDialogBtn = new QPushButton("Select", this);

    m_layout->addWidget(m_path);
    m_layout->addWidget(fileDialogBtn);

    connect(fileDialogBtn, &QPushButton::clicked, [this, type] {
        if (type == SelectionType::Archive)
        {
            m_path->setText(QFileDialog::getOpenFileName(this, "Select your archive", QDir::homePath(), getSupportedArchiveFormats()));
        }
    });
}

QString FileSelector::getSupportedArchiveFormats()
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

bool FileSelector::extractArchive(QString savePath)
{
    if (m_type != SelectionType::Archive)
        return false;

    qDebug() << "Save Path:" << savePath;
    qDebug() << "Archive Path:" << m_path->text();
    QString archivePath = m_path->text();

    QDir().mkpath(savePath);

    struct archive *a = archive_read_new();
    struct archive *ext = archive_write_disk_new();
    struct archive_entry *entry;
    int r;

    archive_read_support_format_all(a);
    archive_read_support_filter_all(a);

    int flags = ARCHIVE_EXTRACT_TIME | ARCHIVE_EXTRACT_PERM | ARCHIVE_EXTRACT_ACL | ARCHIVE_EXTRACT_FFLAGS;

    if (archive_read_open_filename(a, archivePath.toLocal8Bit().constData(), 10240) != ARCHIVE_OK) return false;

    QString oldPath = QDir::currentPath();
    QDir::setCurrent(savePath);

    bool success = true;
    while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
    {
        r = archive_write_header(ext, entry);
        if (r != ARCHIVE_OK) {
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

    return success;
}
