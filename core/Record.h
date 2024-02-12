//
// Created by Herman on 2/9/2024.
//

#pragma once
#include <QPixmap>
#include <QString>


struct Record
{
  float similarToPrev{};
  QString hash;
};

Q_DECLARE_METATYPE(Record)