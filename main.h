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


struct StyleColors {
    QColor firstColor;
    QColor secondColor;
    QColor thirdColor;
    QColor fourthColor;
    QColor textOne;
    QColor textTwo;

    bool operator==(const StyleColors &other) const
    {
       return (firstColor == other.firstColor) && (secondColor == other.secondColor)
               && (thirdColor == other.thirdColor) && (fourthColor == other.fourthColor)
                && (textOne == other.textOne) && (textTwo == other.textTwo);
    }
};

const StyleColors colorsArr [] =
{
    //light
   { { 255, 255, 0 },
     { 255, 255, 204 },
     { 255, 255, 230 },
     { 255, 255, 102 },
     Qt::black,
     Qt::white
   },

   { { 204, 255, 153 },
     { 204, 255, 51 },
     { 204, 255, 204 },
     { 204, 204, 0 },
     Qt::black,
     Qt::white
   },

    //dark
   { { 25, 26, 255 },
     { 102, 102, 255 },
     { 25, 25, 25 },
     { 128, 128, 255 },
      Qt::white,
      Qt::black
   },

    //dark default
   { { 53, 53, 53 },
     { 128, 128, 128 },
     { 25, 25, 25 },
     { 42, 130, 218 },
      Qt::white,
      Qt::black
   }
};

#endif // MAIN_H
