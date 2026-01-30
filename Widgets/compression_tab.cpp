#include "compression_tab.h"

CompressionTab::CompressionTab(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout* layout = new QGridLayout(this);

    m_archiveManager = new ArchiveManager(this);

    QWidget* typeSelectionWgt = new QWidget(this);
    QVBoxLayout* typeSelectionLayout = new QVBoxLayout(typeSelectionWgt);

    QLabel* typeSelectorLbl = new QLabel("Select compression type:", this);
    typeSelectorLbl->setStyleSheet(Styles::label);

    QComboBox* compressionTypeSelector = new QComboBox(this);
    compressionTypeSelector->setStyleSheet(Styles::comboBox);
    compressionTypeSelector->addItems(m_archiveManager->getAvailableCompressions());

    typeSelectionLayout->addWidget(typeSelectorLbl);
    typeSelectionLayout->addWidget(compressionTypeSelector);
    typeSelectionWgt->setFixedHeight(compressionTypeSelector->height() * 2);

    layout->addWidget(typeSelectionWgt, 0, 0, 1, 5);


    QWidget* targetSelectionWgt = new QWidget(this);
    QGridLayout* targetSelectionLayout = new QGridLayout(targetSelectionWgt);

    QLabel* targetSelectionLbl = new QLabel("Select an achive target:", this);
    targetSelectionLbl->setStyleSheet(Styles::label);

    QComboBox* targetTypeSelector = new QComboBox(this);
    targetTypeSelector->addItems({"File", "Folder"});
    targetTypeSelector->setStyleSheet(Styles::comboBox);
    FileSelector* targetSelector = new FileSelector(m_archiveManager, SelectionType::File, this);

    targetSelectionLayout->addWidget(targetSelectionLbl, 0, 0, 1, 1);
    targetSelectionLayout->addWidget(targetTypeSelector, 0, 1, 1, 1);
    targetSelectionLayout->addWidget(targetSelector, 1, 0, 1, 4);
    targetSelectionWgt->setFixedHeight(targetSelectionWgt->height() * 5);

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
    destinationSelectionLbl->setStyleSheet(Styles::label);

    FileSelector* destinationSelector = new FileSelector(m_archiveManager, SelectionType::Dir, this);

    destinationSelectionLayout->addWidget(destinationSelectionLbl);
    destinationSelectionLayout->addWidget(destinationSelector);
    destinationSelectionWgt->setFixedHeight(targetSelectionWgt->height());

    layout->addWidget(destinationSelectionWgt, 4, 0, 1, 5);

    QLabel* archiveNameLbl = new QLabel("   Archive name:", this);
    archiveNameLbl->setStyleSheet(Styles::label);

    QLineEdit* archiveName = new QLineEdit(this);
    archiveName->setText("new_archive");
    archiveName->setStyleSheet(Styles::lineEdit);

    layout->addWidget(archiveNameLbl, 5, 0, 1, 1);
    layout->addWidget(archiveName, 5, 1, 1, 1);

    QPushButton* compressArchiveBtn = new QPushButton("Compress", this);
    compressArchiveBtn->setStyleSheet(Styles::highlightedButton);
    layout->addWidget(compressArchiveBtn, 6, 4, 1, 2);

    connect(compressArchiveBtn, &QPushButton::clicked, [this, targetSelector, compressionTypeSelector, destinationSelector, archiveName]{

        QPointer<QMessageBox> msg = new QMessageBox(this);

        if (targetSelector->getPath() == "" || targetSelector->getPath().isEmpty())
        {
            msg->setText("Error! Please, select an archive target.");
            msg->exec();
            return;
        }

        if (archiveName->text() == "" || archiveName->text().isEmpty())
        {
            msg->setText("Error! Please, enter archive name.");
            msg->exec();
            return;
        }

        qDebug() << targetSelector->getPath();
        if (destinationSelector->getPath() == "" || destinationSelector->getPath().isEmpty())
            m_archiveManager->compress(targetSelector->getPath(),
                                       QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath(),
                                                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks ) + "/" + archiveName->text(),
                                       ArchiveManager::getCompressionTypeFromIndex(compressionTypeSelector->currentIndex()));
        else
            m_archiveManager->compress(targetSelector->getPath(), destinationSelector->getPath() + "/" + archiveName->text(),
                                       ArchiveManager::getCompressionTypeFromIndex(compressionTypeSelector->currentIndex()));
    });

    connect (m_archiveManager.get(), &ArchiveManager::compressionFinished, [destinationSelector]{
        QDesktopServices::openUrl(QUrl::fromLocalFile(destinationSelector->getPath()));
    });
}
