#include "window.h"

#include <QComboBox>
#include <QGridLayout>
#include <QSpinBox>

#include <QScrollArea>

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
    for(uint8_t i = 0; i < BOOKS_AMOUNT*2; i+=2) {
        books_combo->addItem(bible::books[i+1], bible::books[i]);
    }

    chapter = new QSpinBox(this);
    chapter->setMinimum(1);

    bible::cJSON* history = bible::bible_get_save();

    if (history != NULL) {
        bible::cJSON* version_json = bible::cJSON_GetObjectItemCaseSensitive(history, "version");
        bible::cJSON* book_json = bible::cJSON_GetObjectItemCaseSensitive(history, "book");
        bible::cJSON* chapter_json = bible::cJSON_GetObjectItemCaseSensitive(history, "chapter");

        versions_combo->setCurrentIndex(version_json->valueint);
        books_combo->setCurrentIndex(book_json->valueint);
        chapter->setValue(chapter_json->valueint);

        bible::cJSON_Delete(history);
    }

    connect(versions_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( VersionChanged() ));
    connect(books_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( BookChanged() ));

    connect(versions_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( ChapterChanged() ));
    connect(books_combo, SIGNAL(currentIndexChanged(int)), this, SLOT( ChapterChanged() ));

    connect(chapter, SIGNAL( valueChanged(int) ), this, SLOT ( ChapterChanged() ));

    grid->addWidget(versions_combo, 0, 0, Qt::AlignTop);
    grid->addWidget(books_combo, 0, 1, Qt::AlignTop);
    grid->addWidget(chapter, 0, 2, Qt::AlignTop);

    // O conteúdo do capítulo.

    page_scroll = new QScrollArea(this);
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
}

void Window::ChapterChanged() {
    page->clearVerses();

    uint8_t number = 1;
    bible::cJSON* verse;
    cJSON_ArrayForEach(verse, bible::cJSON_GetArrayItem(book_json, chapter->value()-1)) {
        page->addVerse(verse->valuestring, number);
        number++;
    }
    cJSON_Delete(verse);

    page->updateVerses();
}

Window::~Window() {
    bible::bible_save(versions_combo->currentIndex(), books_combo->currentIndex(), chapter->value());
}