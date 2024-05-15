#ifndef VERSE_H
#define VERSE_H

#include <QWidget>

#include <string>
#include <vector>

class QString;
class QLabel;

class Page : public QWidget {
public:
    explicit Page(std::vector<std::string> verses, QWidget* parent);
private:
    QLabel* label;
};

#endif