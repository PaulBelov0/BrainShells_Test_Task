#ifndef EXTRACTION_TAB_H
#define EXTRACTION_TAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QDesktopServices>

#include "file_selector.h"
#include "../services/archive_manager.h"

class ExtractionTab : public QWidget
{
    Q_OBJECT
public:
    explicit ExtractionTab(QWidget *parent = nullptr);

private:
    QPointer<ArchiveManager> m_archiveManager;
};

#endif // EXTRACTION_TAB_H
