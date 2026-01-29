#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    QWidget* wgt = new QWidget(this);
    setCentralWidget(wgt);

    QVBoxLayout* layout = new QVBoxLayout(wgt);

    FileSelector* fileSelector = new FileSelector(SelectionType::Archive, this);
    layout->addWidget(fileSelector);
    QPushButton* extractArchiveBtn = new QPushButton("Extract", this);
    layout->addWidget(extractArchiveBtn);

    connect(extractArchiveBtn, &QPushButton::clicked, [this, fileSelector]{
        fileSelector->extractArchive(QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ));
    });
}
