//
// Created by Herman on 2/9/2024.
//

#pragma once
#include <QPixmap>
#include <QString>


struct Record
{
  float similarity{};
  QString hash;
};

Q_DECLARE_METATYPE(Record)
Q_DECLARE_METATYPE(QList<Record>)