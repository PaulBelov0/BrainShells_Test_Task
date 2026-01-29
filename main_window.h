#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>

#include "Widgets/file_selector.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
};
#endif // MAIN_WINDOW_H
