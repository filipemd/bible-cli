#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QComboBox;
class QGridLayout;
class QSpinBox;

class Window : public QWidget
{
public:
    explicit Window(QWidget *parent = 0);
private:
    QGridLayout* grid;

    QComboBox* versions_combo;
    QComboBox* books_combo;

    QSpinBox* chapter;
};

#endif // WINDOW_H