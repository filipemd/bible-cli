#ifndef VERSE_H
#define VERSE_H

#include <QWidget>

#include <string>
#include <vector>

class QString;
class QLabel;

class Page : public QWidget {
public:
    explicit Page(QWidget* parent);
    void updateVerses(const std::vector<std::string>& verses);
private:
    QLabel* label;
};

#endif