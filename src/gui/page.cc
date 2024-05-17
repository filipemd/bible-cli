#include "page.h"

#include <QLabel>
#include <QVBoxLayout>

Page::Page(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    setContentsMargins(0,0,0,0);
    
    label = new QLabel(this);
    label->setWordWrap(true); // Habilita a quebra de linha

    layout->addWidget(label);
    setLayout(layout);
}

void Page::updateVerses(const std::vector<std::string>& verses) {
    uint8_t number = 1;
    QString htmlText;
    for(const auto& verse : verses) {
        htmlText.append("<p><font size=\"2\" color=\"gray\">" + QString::number(number) + "\t</font><font size=\"4\">" + QString::fromStdString(verse) + "</font></p>");
        number++;
    }

    label->setText(htmlText);

    adjustSize();
    
    // Ajuste a largura máxima do QLabel para corresponder à largura da janela
    label->setMaximumWidth(this->width());
}