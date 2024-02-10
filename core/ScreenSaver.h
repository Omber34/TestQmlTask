//
// Created by Herman on 2/9/2024.
//

#pragma once

#include <QObject>

class ScreenSaver
{

public:
  ScreenSaver();

  void start();
  void pause();
  void takeNewRecord();



private:

  ScreenSaver(const ScreenSaver& other) = delete;
  ScreenSaver& operator=(const ScreenSaver& other) = delete;

private:



};
