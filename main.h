#ifndef MAIN_H
#define MAIN_H

#include <QTranslator>
#include <QVector>

struct KeyBind {
    Qt::KeyboardModifier mod1;
    Qt::KeyboardModifier mod2;
    Qt::Key key;
};

const   QString langRus { "./QtLanguage_ru" };
const   QString langEng { "./QtLanguage_en" };

#endif // MAIN_H
