#ifndef STYLES_H
#define STYLES_H

#include <QString>

struct Styles
{

    inline static QString label = QString(R"(
QLabel {
    font-size: 16px;
    font-weight: bold;
    color: white;
}
)");

    inline static QString standartButton = QString(R"(
QPushButton {
    background-color: #919191;
    border: 2px solid #BABABA;
    border-radius: 5px;
    color: white;
    padding: 8px 16px;
    font-size: 14px;
}

QPushButton:hover {
    background-color: #E8E8E8;
    border-color: #8C8C8C;
    color: #595959;
}

QPushButton:pressed {
    background-color: #8A8A8A;
    border-color: #E6E6E6;
}
)");

    inline static QString highlightedButton = QString(R"(
QPushButton {
    background-color: #2590db;
    border: 2px solid #2980b9;
    border-radius: 5px;
    color: white;
    padding: 8px 16px;
    font-weight: bold;
    font-size: 14px;
}

QPushButton:hover {
    background-color: #5dade2;
    border-color: #3498db;
}

QPushButton:pressed {
    background-color: #21618c;
    border-color: #1b4f72;
}
)");

    inline static QString lineEdit = QString(R"(
QLineEdit {
    background-color: #FFFFFF;
    border: 2px solid #BABABA;
    border-radius: 5px;
    color: #333333;
    padding: 6px 10px;
    font-size: 14px;
    selection-background-color: #919191;
    selection-color: white;
}

QLineEdit:hover {
    border-color: #8C8C8C;
}

QLineEdit:focus {
    border-color: #919191;
    background-color: #F8F8F8;
}

QLineEdit:disabled {
    background-color: #737373;
    border-color: #D0D0D0;
    color: #F7F7F7;
}

QLineEdit:read-only {
    background-color: #F5F5F5;
    border-color: #D0D0D0;
    color: #666666;
}
)");

    inline static QString comboBox = QString(R"(
QComboBox {
    background-color: #FFFFFF;
    border: 2px solid #BABABA;
    border-radius: 5px;
    color: black;
    padding: 6px 10px;
    font-size: 14px;
    min-height: 20px;
}

QComboBox:hover {
    border-color: #8C8C8C;
}

QComboBox:focus {
    border-color: #919191;
    background-color: #F8F8F8;
}

QComboBox:disabled {
    background-color: #F0F0F0;
    border-color: #D0D0D0;
    color: #888888;
}

QComboBox::drop-down {
    border: none;
    background: transparent;
    width: 25px;
}

QComboBox::down-arrow {
    image: url(:/arrow);
    width: 12px;
    height: 12px;
    border: none;
}

QComboBox::down-arrow:hover {
    border-top-color: #8C8C8C;
}

QComboBox QAbstractItemView {
    background-color: white;
    color: black;
    border: 2px solid #BABABA;
    border-radius: 5px;
    selection-background-color: #919191;
    selection-color: #707070;
    outline: none;
    padding: 4px;
}

QComboBox QAbstractItemView::item {
    padding: 6px 10px;
    border-radius: 3px;
}

QComboBox QAbstractItemView::item:hover {
    background-color: #F0F0F0;
}
)");

    inline static QString tabWidget = QString(R"(
QTabWidget::pane {
    border: 2px solid #5A5A5A;
    border-radius: 5px;
    background-color: #3A3A3A;
    padding: 5px;
}

QTabBar::tab {
    background-color: #4A4A4A;
    border: 2px solid #5A5A5A;
    border-bottom: none;
    border-radius: 4px 4px 0 0;
    padding: 8px 25px;
    color: #DDDDDD;
    font-size: 14px;
}

QTabBar::tab:selected {
    background-color: #2590db;
    color: #FFFFFF;
    border-bottom-color: #3A3A3A;
    font-weight: bold;
}

QTabBar::tab:hover {
    background-color: #555555;
    color: #F0F0F0;
}
)");
};

#endif // STYLES_H
