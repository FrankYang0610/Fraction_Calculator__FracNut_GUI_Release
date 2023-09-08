//
// Created by Frank Yang on 2023/8/14.
//

#include <iostream>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

void MainWindow::welcomeScreen()
{
    ui->Output->insertPlainText("WELCOME TO FRACNUT🌰 BY FRANK YANG\n");
    ui->Output->insertPlainText("To start using this command-line tool, please be knowing these instructions:\n");

    ui->Output->insertPlainText("1. Use help() for getting help.\n");
    ui->Output->insertPlainText("2. Use clear() for clearing the screen.\n");

    ui->Output->insertPlainText("FracNut GUI Stable Release 1.0.0\n");
    ui->Output->insertPlainText("Release Date: Sept 9, 2023\n");

    ui->Output->insertPlainText("\n");
}
