#ifndef COMPRESSION_TAB_H
#define COMPRESSION_TAB_H

#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QDesktopServices>

#include "file_selector.h"
#include "../services/archive_manager.h"

class CompressionTab : public QWidget
{
    Q_OBJECT
public:
    explicit CompressionTab(QWidget *parent = nullptr);

private:
    QPointer<ArchiveManager> m_archiveManager;
};

#endif // COMPRESSION_TAB_H
