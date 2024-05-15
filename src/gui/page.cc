#include "page.h"

#include <QLabel>
#include <QVBoxLayout>

Page::Page(std::vector<std::string> verses, QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    label = new QLabel(this);
    label->setWordWrap(true);

    uint8_t number = 1;
    for(const auto& verse : verses) {
        label->setText(label->text() + "<p><font size=2 color=gray>" + QString::fromStdString(std::to_string(number)) + "\t</font><font size=4>" + QString::fromStdString(verse) + "</font><p>");

        number++;
    }

    layout->addWidget(label);
    setLayout(layout);
}
