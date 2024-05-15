#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <vector>
namespace bible {
extern "C" {
#include "../bible.h"
}
}

#include "page.h"

class QComboBox;
class QSpinBox;
class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
private slots:
    void BookChanged();
private:
    Page* page;

    QComboBox* versions_combo;
    QComboBox* books_combo;

    QSpinBox* chapter;

    // JSON da Bíblia
    bible::cJSON* book_json;
};

#endif // WINDOW_H