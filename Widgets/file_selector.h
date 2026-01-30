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
#include "../services/archive_manager.h"
#include "../styles.h"

class FileSelector : public QWidget
{
    Q_OBJECT
public:
    explicit FileSelector(ArchiveManager* archiveManager, SelectionType type, QWidget *parent = nullptr);

    QString getPath() { return m_containedPath; }
    void setType(SelectionType type) { m_type = type; }
    void clearText() { m_path->clear(); m_containedPath.clear(); }
private:

    QString m_containedPath;

    SelectionType m_type;

    QPointer<QHBoxLayout> m_layout;
    QPointer<QLineEdit> m_path;
};

#endif // FILE_SELECTOR_H
