//
// Created by Herman on 2/9/2024.
//

#pragma once
#include <QPixmap>
#include <QString>


struct Record
{
  QPixmap image;
  float similarToPrev{};
  QString hash;
};