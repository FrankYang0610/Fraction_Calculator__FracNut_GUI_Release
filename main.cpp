#include "mainwindow.h"

#include "Fraction.h"

#include <iostream>
#include <QApplication>

#include <cstring>
#include "Parser.cpp"
#include "Helper.cpp"
#include "ui_mainwindow.h"
#include "StringConvertor.cpp"

int main(int argc, char *argv[])
{
    QApplication FracNut(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    mainWindow.welcomeScreen();
    mainWindow.inputCountOutput();

    return FracNut.exec();
}
