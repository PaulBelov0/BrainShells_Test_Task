#ifndef FILE_SELECTOR_H
#define FILE_SELECTOR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QPointer>
#include <QHBoxLayout>
#include <QStringList>

#include <archive.h>
#include <archive_entry.h>

#include "../resources.h"

class FileSelector : public QWidget
{
    Q_OBJECT
public:
    explicit FileSelector(SelectionType type, QWidget *parent = nullptr);

public slots:
    bool extractArchive(QString savePath);
private:
    QString getSupportedArchiveFormats();

    SelectionType m_type;

    QPointer<QHBoxLayout> m_layout;
    QPointer<QLineEdit> m_path;
};

#endif // FILE_SELECTOR_H
