#include "window.h"

#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>

#include <QScrollArea>
#include <QScrollBar>

#include <iostream>
namespace bible {
#include "../bible-lists.h"
}

Window::Window(QWidget *parent) :
    QWidget(parent), book_json(NULL) {
    
    setWindowTitle("Bible Desktop");

    // UI para selecionar o capítulo.
    QGridLayout* grid = new QGridLayout(this);

    versions_combo = new QComboBox(this);
    for(unsigned i = 0; i < VERSIONS_AMOUNT*2; i+=2) {
        versions_combo->addItem(bible::versions[i+1], bible::versions[i]);
    }

    books_combo = new QComboBox(this);
    for(unsigned i = 0; i < BOOKS_AMOUNT*2; i+=2) {
        books_combo->addItem(bible::books[i+1], bible::books[i]);
    }

    connect(versions_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( VersionChanged() ));
    connect(books_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( BookChanged() ));

    connect(versions_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( ChapterChanged() ));
    connect(books_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( ChapterChanged() ));

    chapter = new QSpinBox(this);
    chapter->setMinimum(1);

    connect(chapter, SIGNAL( valueChanged(int) ), this, SLOT ( ChapterChanged() ));

    grid->addWidget(versions_combo, 0, 0, Qt::AlignTop);
    grid->addWidget(books_combo, 0, 1, Qt::AlignTop);
    grid->addWidget(chapter, 0, 2, Qt::AlignTop);

    // O conteúdo do capítulo.

    QScrollArea* page_scroll = new QScrollArea(this);
    page_scroll->setWidgetResizable(true);
    page_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        
    grid->addWidget(page_scroll, 1, 0, 1, 3);

    page = new Page(page_scroll);

    page_scroll->setWidget(page);

    BookChanged();
    ChapterChanged();
}

void Window::VersionChanged() {

    if(book_json != NULL) {
        bible::cJSON_Delete(book_json);
    }

    book_json = bible::get_bible(bible::versions[versions_combo->currentIndex()*2], bible::books[books_combo->currentIndex()*2]);

    chapter->setMaximum(bible::cJSON_GetArraySize(book_json));
}

void Window::BookChanged() {
    VersionChanged();

    chapter->setValue(1);
}

void Window::ChapterChanged() {
    std::vector<std::string> verses;

    bible::cJSON* verse;
    cJSON_ArrayForEach(verse, bible::cJSON_GetArrayItem(book_json, chapter->value()-1)) {
        verses.push_back(verse->valuestring);
    }
    cJSON_Delete(verse);

    page->updateVerses(verses);
}