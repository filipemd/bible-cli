#include "window.h"

#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>

namespace bible {
#include "../bible-lists.h"

extern "C" {
#include "../bible.h"
}
}

Window::Window(QWidget *parent) :
    QWidget(parent) {
    // Set size of the window
    setWindowTitle("Bible Desktop");

    grid = new QGridLayout(this);

    versions_combo = new QComboBox(this);
    for(unsigned i = 0; i < VERSIONS_AMOUNT*2; i+=2) {
        versions_combo->addItem(bible::versions[i+1], bible::versions[i]);
    }

    books_combo = new QComboBox(this);
    for(unsigned i = 0; i < BOOKS_AMOUNT*2; i+=2) {
        books_combo->addItem(bible::books[i+1], bible::books[i]);
    }

    connect(versions_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( BookChanged() ));
    connect(books_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( BookChanged() ));

    chapter = new QSpinBox;
    chapter->setMinimum(1);

    grid->addWidget(versions_combo, 0, 0, Qt::AlignTop);
    grid->addWidget(books_combo, 0, 1, Qt::AlignTop);
    grid->addWidget(chapter, 0, 2, Qt::AlignTop);
}

void Window::BookChanged() {
    const char* version = bible::versions[versions_combo->currentIndex()*2];
    const char* book = bible::books[books_combo->currentIndex()*2]; 

    const bible::cJSON* book_json = bible::get_bible(version, book);

    chapter->setMaximum(bible::cJSON_GetArraySize(book_json));
}