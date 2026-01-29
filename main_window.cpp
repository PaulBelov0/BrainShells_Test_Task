#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    QWidget* wgt = new QWidget(this);
    setCentralWidget(wgt);

    m_layout = new QVBoxLayout(wgt);

    m_tabWidget = new QTabWidget(this);

    ExtractionTab* extractionTab = new ExtractionTab(this);
    CompressionTab* compressionTab = new CompressionTab(this);

    m_tabWidget->addTab(extractionTab, "Extract");
    m_tabWidget->addTab(compressionTab, "Compress");
    m_layout->addWidget(m_tabWidget);
}
