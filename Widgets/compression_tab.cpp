#include "compression_tab.h"

CompressionTab::CompressionTab(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout* layout = new QGridLayout(this);

    m_archiveManager = new ArchiveManager(this);

    QLabel* selectorLbl = new QLabel("Select compression type:", this);

    QWidget* typeSelectionWgt = new QWidget(this);
    QVBoxLayout* typeSelectionLayout = new QVBoxLayout(typeSelectionWgt);

    QLabel* typeSelectorLbl = new QLabel("Select compression type:", this);

    QComboBox* compressionTypeSelector = new QComboBox(this);
    compressionTypeSelector->addItems(m_archiveManager->getAvailableCompressions());

    typeSelectionLayout->addWidget(typeSelectorLbl);
    typeSelectionLayout->addWidget(compressionTypeSelector);
    typeSelectionWgt->setFixedHeight(compressionTypeSelector->height() * 3);

    layout->addWidget(typeSelectionWgt, 0, 0, 1, 5);


    QWidget* targetSelectionWgt = new QWidget(this);
    QGridLayout* targetSelectionLayout = new QGridLayout(targetSelectionWgt);

    QLabel* targetSelectionLbl = new QLabel("Select an achive target:", this);
    QComboBox* targetTypeSelector = new QComboBox(this);
    targetTypeSelector->addItems({"File", "Folder"});
    FileSelector* targetSelector = new FileSelector(m_archiveManager, SelectionType::File, this);

    targetSelectionLayout->addWidget(targetSelectionLbl, 0, 0, 1, 1);
    targetSelectionLayout->addWidget(targetTypeSelector, 0, 1, 1, 1);
    targetSelectionLayout->addWidget(targetSelector, 1, 0, 1, 4);
    targetSelectionWgt->setFixedHeight(targetSelector->height() * 3);

    connect(targetTypeSelector, &QComboBox::currentIndexChanged, [targetSelector](int currentIndex){
        switch (currentIndex)
        {
        case 0:
            targetSelector->setType(SelectionType::File);
            targetSelector->clearText();
            break;
        case 1:
            targetSelector->setType(SelectionType::Dir);
            targetSelector->clearText();
            break;
        }
    });

    layout->addWidget(targetSelectionWgt, 3, 0, 1, 5);

    QWidget* destinationSelectionWgt = new QWidget(this);
    QVBoxLayout* destinationSelectionLayout = new QVBoxLayout(destinationSelectionWgt);

    QLabel* destinationSelectionLbl = new QLabel("Select destination path:", this);
    FileSelector* destinationSelector = new FileSelector(m_archiveManager, SelectionType::Dir, this);

    destinationSelectionLayout->addWidget(destinationSelectionLbl);
    destinationSelectionLayout->addWidget(destinationSelector);
    destinationSelectionWgt->setFixedHeight(destinationSelector->height() * 3);

    layout->addWidget(destinationSelectionWgt, 4, 0, 1, 5);


    QPushButton* compressArchiveBtn = new QPushButton("Compress", this);
    layout->addWidget(compressArchiveBtn, 5, 5, 1, 1);

    connect(compressArchiveBtn, &QPushButton::clicked, [this, targetSelector, compressionTypeSelector, destinationSelector]{
        if (targetSelector->getPath() == "" || targetSelector->getPath().isEmpty())
        {
            qDebug() << targetSelector->getPath();
            QMessageBox* msg = new QMessageBox(this);
            msg->setText("Error! Please, select an archive target.");
            msg->exec();
        }
        else
        {
            qDebug() << targetSelector->getPath();
            if (destinationSelector->getPath() == "" || destinationSelector->getPath().isEmpty())
                m_archiveManager->compress(targetSelector->getPath(),
                                           QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath(),
                                                                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ),
                                           ArchiveManager::getCompressionTypeFromIndex(compressionTypeSelector->currentIndex()));
            else
                m_archiveManager->compress(targetSelector->getPath(), destinationSelector->getPath(),
                                           ArchiveManager::getCompressionTypeFromIndex(compressionTypeSelector->currentIndex()));
        }
    });

    connect (m_archiveManager.get(), &ArchiveManager::compressionFinished, [destinationSelector]{
        QDesktopServices::openUrl(QUrl::fromLocalFile(destinationSelector->getPath()));
    });
}
