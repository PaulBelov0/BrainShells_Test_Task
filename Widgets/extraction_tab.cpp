#include "extraction_tab.h"

ExtractionTab::ExtractionTab(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout* layout = new QGridLayout(this);

    m_archiveManager = new ArchiveManager(this);


    QWidget* fileSelectionWgt = new QWidget(this);
    QVBoxLayout* fileSelectionLayout = new QVBoxLayout(fileSelectionWgt);

    QLabel* fileSelectionLbl = new QLabel("Select an achive:", this);
    FileSelector* fileSelector = new FileSelector(m_archiveManager, SelectionType::Archive, this);

    fileSelectionLayout->addWidget(fileSelectionLbl);
    fileSelectionLayout->addWidget(fileSelector);
    fileSelectionWgt->setFixedHeight(fileSelector->height() * 3);

    layout->addWidget(fileSelectionWgt, 3, 0, 1, 5);



    QWidget* destinationSelectionWgt = new QWidget(this);
    QVBoxLayout* destinationSelectionLayout = new QVBoxLayout(destinationSelectionWgt);

    QLabel* destinationSelectionLbl = new QLabel("Select destination path:", this);
    FileSelector* destinationSelector = new FileSelector(m_archiveManager, SelectionType::Dir, this);

    destinationSelectionLayout->addWidget(destinationSelectionLbl);
    destinationSelectionLayout->addWidget(destinationSelector);
    destinationSelectionWgt->setFixedHeight(destinationSelector->height() * 3);

    layout->addWidget(destinationSelectionWgt, 4, 0, 1, 5);


    QPushButton* extractArchiveBtn = new QPushButton("Extract", this);
    layout->addWidget(extractArchiveBtn, 6, 5, 1, 1);

    connect(extractArchiveBtn, &QPushButton::clicked, [this, fileSelector, destinationSelector]{
        if (fileSelector->getPath() == "" || fileSelector->getPath().isEmpty())
        {
            qDebug() << fileSelector->getPath();
            QMessageBox* msg = new QMessageBox(this);
            msg->setText("Error! Please, select an archive.");
            msg->exec();
        }
        else
        {
            qDebug() << fileSelector->getPath();
            if (destinationSelector->getPath() == "" || destinationSelector->getPath().isEmpty())
                m_archiveManager->extract(fileSelector->getPath(),
                                          QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath(),
                                                                            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ));
            else
                m_archiveManager->extract(fileSelector->getPath(), destinationSelector->getPath());
        }
    });

    connect (m_archiveManager.get(), &ArchiveManager::extractionFinished, [destinationSelector]{
        QDesktopServices::openUrl(QUrl::fromLocalFile(destinationSelector->getPath()));
    });
}
