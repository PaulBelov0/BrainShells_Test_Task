#include "file_selector.h"

FileSelector::FileSelector(ArchiveManager* archiveManager, SelectionType type, QWidget *parent)
    : QWidget{parent}
{
    m_type = type;
    m_layout = new QHBoxLayout(this);

    m_containedPath = "";

    m_path = new QLineEdit(this);
    m_path->setEnabled(false);
    m_path->setStyleSheet(Styles::lineEdit);
    QPushButton* fileDialogBtn = new QPushButton("Select", this);
    fileDialogBtn->setStyleSheet(Styles::standartButton);

    m_layout->addWidget(m_path);
    m_layout->addWidget(fileDialogBtn);

    connect(fileDialogBtn, &QPushButton::clicked, [this, archiveManager] {
        switch(m_type)
        {
        case SelectionType::Archive:
        {
            m_containedPath = QFileDialog::getOpenFileName(this, "Select your archive", QDir::homePath(), archiveManager->getSupportedArchiveFormats());
            break;
        }
        case SelectionType::Dir:
        {
            m_containedPath = QFileDialog::getExistingDirectory(this, "Select folder", QDir::homePath(),
                                                                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks );
            break;
        }
        case SelectionType::File:
        {
            m_containedPath = QFileDialog::getOpenFileName(this, "Select your archive", QDir::homePath(), "*.*");
            break;
        }
        }
        m_path->setText(m_containedPath);
    });
}

