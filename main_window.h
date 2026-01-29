#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTabWidget>

#include "widgets/file_selector.h"
#include "widgets/extraction_tab.h"
#include "Widgets/compression_tab.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QPointer<QTabWidget> m_tabWidget;
    QPointer<QVBoxLayout> m_layout;
};
#endif // MAIN_WINDOW_H
