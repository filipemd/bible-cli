#ifndef VERSE_H
#define VERSE_H

#include <QWidget>

#include <string>

class QString;
class QLabel;

class Page : public QWidget {
public:
    explicit Page(QWidget* parent);
    void addVerse(std::string verse, uint8_t number);
    void updateVerses();
    void clearVerses();
private:
    QLabel* label;

    QString text;
};

#endif