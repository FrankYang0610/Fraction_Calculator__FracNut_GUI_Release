#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "StringConvertor.cpp"
#include "Parser.cpp"
#include "Helper.cpp"
#include <cstring>
#include <cstdio>
#include <QScrollBar>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->CommandLine->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// KEY PRESS EVENT
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        // STORE
        this->currentInput = ui->CommandLine->toPlainText().toStdString();

        // MAKE THE CURSOR THE LAST POSITION
        ui->Output->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

        // CALCULATE & PROCESSING
        forResult();

        // FOR SCROLL BAR
        ui->Output->verticalScrollBar()->setValue(ui->Output->verticalScrollBar()->maximum());
    }
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *_QKeyEvent = static_cast <QKeyEvent *> (event);

        if (_QKeyEvent->key() == Qt::Key_Return || _QKeyEvent->key() == Qt::Key_Enter)
        {
            // STORE
            this->currentInput = ui->CommandLine->toPlainText().toStdString();

            // MAKE THE CURSOR THE LAST POSITION
            ui->Output->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

            // CALCULATE & PROCESSING
            forResult();

            // FOR SCROLL BAR
            ui->Output->verticalScrollBar()->setValue(ui->Output->verticalScrollBar()->maximum());
        }
    }

    return QWidget::eventFilter(target,event);
}

void MainWindow::inputCountOutput()
{
    ui->Output->insertPlainText("Input");
    ui->Output->insertPlainText("[");
    ui->Output->insertPlainText(unsignedIntConvert(this->inputCount));
    ui->Output->insertPlainText("]");
    ui->Output->insertPlainText(":");
    ui->Output->insertPlainText(" ");

    ui->InputNotifier->clear();
    ui->InputNotifier->insert("Input");
    ui->InputNotifier->insert("[");
    ui->InputNotifier->insert(unsignedIntConvert(this->inputCount));
    ui->InputNotifier->insert("]");
}

void MainWindow::outputCountOutput()
{
    ui->Output->insertPlainText("Output");
    ui->Output->insertPlainText("[");
    ui->Output->insertPlainText(unsignedIntConvert(this->inputCount));
    ui->Output->insertPlainText("]");
    ui->Output->insertPlainText(":");
    ui->Output->insertPlainText(" ");
}

void MainWindow::forResult()
{

    // OUTPUT THE NUMBER
    ui->Output->insertPlainText(stringConvert(currentInput));
    ui->Output->insertPlainText("\n");
    outputCountOutput();


    // PROCESS THE CURRENT CALCULATION
    std::string parsed = parse(currentInput);

    if (parsed == "EMPTY_STRING")
        ui->Output->insertPlainText("NO CONTENT!");

    else if (parsed == "INVALID_STRING")
        ui->Output->insertPlainText("INVALID INPUT!");

    else if (parsed == "quit()")
    {}

    else if (parsed == "help()")
        getHelp();

    else if (parsed == "clear()")
    {
        ui->CommandLine->clear();
        ui->Output->clear();
    }

    else if (parsed == "lastResult()")
        ui->Output->insertPlainText(stringConvert(this->lastResult));

    else if (parsed == "clipboard()")
        ui->Output->insertPlainText(stringConvert(this->clipboard));

    else if (parsed == "copy(lastResult())")
    {
        clipboard = lastResult;
        ui->Output->insertPlainText("Copied.");
    }

    else if (parsed == "remove(clipboard())")
    {
        clipboard = "0";
        ui->Output->insertPlainText("Removed.\n");
    }

    else if (parsed == "remove(lastResult())")
    {
        lastResult = "0";
        ui->Output->insertPlainText("Removed.");
    }

    else if (parsed.size() >= 9 &&
             parsed[0] == 'd' &&
             parsed[1] == 'e' &&
             parsed[2] == 'c' &&
             parsed[3] == 'i' &&
             parsed[4] == 'm' &&
             parsed[5] == 'a' &&
             parsed[6] == 'l' &&
             parsed[7] == '(' &&
             parsed[parsed.size() - 1] == ')') // decimal
    {
        std::string insideParsed = "";
        bool resultInvalid = false;

        if (parsed.size() == 9)
        {
            ui->Output->insertPlainText("NOTHING TO DECIMAL!");
            resultInvalid = true;
        }
        else if (parsed == "decimal(lastResult())") {
            insideParsed = this->lastResult;
        }

        else if (parsed == "decimal(clipboard())"){
            insideParsed = this->clipboard;
        }

        else {
            for (int i = 8; i <= parsed.size() - 2; i++) {
                insideParsed += parsed[i];
            }
        }

        std::string resultToDecimal = parse(insideParsed); // expressionToDecimal is now a simplified fraction

        for (int i = 0; i<=resultToDecimal.size() - 1; i++) {
            if (!((resultToDecimal[i] >= 0x30 && resultToDecimal[i] <= 0x39) || resultToDecimal[i] == '/' || resultToDecimal[i] == '-')) {
                resultInvalid = true;
            }
        }

        if (resultInvalid) {
            ui->Output->insertPlainText("INVALID INPUT!\n");
        }
        else
        {
            bool divisionExists = 0;
            for (int i = 0; i <= resultToDecimal.size() - 1; i++) {
                if (resultToDecimal[i] == '/') {
                    divisionExists = true;
                    break;
                }
            }

            if (!divisionExists){ // integer
                ui->Output->insertPlainText(stringConvert(resultToDecimal));
                this->lastResult = resultToDecimal;
            }
            else { // fraction
                ui->Output->insertPlainText(doubleConvert(stringFractionToDouble(resultToDecimal)));
                this->lastResult = doubleConvert(stringFractionToDouble(resultToDecimal)).toStdString();
            }
        }
    }

    else if ((parsed[0] >= 0x30 && parsed[0] <=0x39) || parsed[0]=='-') // EXPRESSION
    {
        ui->Output->insertPlainText(stringConvert(parsed));
        this->lastResult = parsed;
    }
    else
        ui->Output->insertPlainText("INVALID INPUT!\n");

    // PREPARE FOR NEW CALCULATION
    this->inputCount++;
    this->currentInput.clear();
    ui->Output->insertPlainText("\n\n");
    inputCountOutput();

    ui->CommandLine->clear();
}

void MainWindow::on_Keypad1_clicked() {
    ui->CommandLine->insertPlainText("1");
}


void MainWindow::on_Keypad2_clicked() {
    ui->CommandLine->insertPlainText("2");
}


void MainWindow::on_Keypad3_clicked() {
    ui->CommandLine->insertPlainText("3");
}


void MainWindow::on_Keypad4_clicked() {
    ui->CommandLine->insertPlainText("4");
}


void MainWindow::on_Keypad5_clicked() {
    ui->CommandLine->insertPlainText("5");
}


void MainWindow::on_Keypad6_clicked() {
    ui->CommandLine->insertPlainText("6");
}


void MainWindow::on_Keypad7_clicked() {
    ui->CommandLine->insertPlainText("7");
}


void MainWindow::on_Keypad8_clicked() {
    ui->CommandLine->insertPlainText("8");
}


void MainWindow::on_Keypad9_clicked() {
    ui->CommandLine->insertPlainText("9");
}


void MainWindow::on_Keypad0_clicked() {
    ui->CommandLine->insertPlainText("0");
}


void MainWindow::on_KeypadLeftBracket_clicked() {
    ui->CommandLine->insertPlainText("[");
}


void MainWindow::on_KeypadRightBracket_clicked() {
    ui->CommandLine->insertPlainText("]");
}


void MainWindow::on_KeypadDot_clicked() {
    ui->CommandLine->insertPlainText(".");
}


void MainWindow::on_KeypadPlus_clicked() {
    ui->CommandLine->insertPlainText("+");
}


void MainWindow::on_KeypadMinus_clicked() {
    ui->CommandLine->insertPlainText("-");
}


void MainWindow::on_KeypadMultiply_clicked() {
    ui->CommandLine->insertPlainText("*");
}


void MainWindow::on_KeypadDivide_clicked() {
    ui->CommandLine->insertPlainText("/");
}

void MainWindow::on_KeypadCalculate_clicked() {
    // STORE
    this->currentInput = ui->CommandLine->toPlainText().toStdString();

    // MAKE THE CURSOR THE LAST POSITION
    ui->Output->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    // CALCULATE & PROCESSING
    forResult();

    // FOR SCROLL BAR
    ui->Output->verticalScrollBar()->setValue(ui->Output->verticalScrollBar()->maximum());
}



void MainWindow::on_CommandLine_textChanged() {

}


void MainWindow::on_KeypadBackspace_clicked() {
    // For TextEdit
    QTextCursor cursor = ui->CommandLine->textCursor();
    cursor.deletePreviousChar();
}


void MainWindow::on_KeypadClearOutput_clicked() {
    ui->Output->clear();

    inputCountOutput();
}


void MainWindow::on_KeypadLeftParentheses_clicked() {
    ui->CommandLine->insertPlainText("(");
}


void MainWindow::on_KeypadRightparentheses_clicked() {
    ui->CommandLine->insertPlainText(")");
}


void MainWindow::on_MenuGetForHelp_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("help()");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuLastResult_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("lastResult()");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuRemoveLastResult_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("remove(lastResult())");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuSaveToClipboard_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("copy(lastResult())");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuClipboard_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("clipboard()");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuRemoveClipboard_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("remove(clipboard())");
    on_KeypadCalculate_clicked();
}

void MainWindow::on_MenuUseLastResult_clicked() {
    ui->CommandLine->insertPlainText(stringConvert(this->lastResult));
}


void MainWindow::on_MenuUseClipboard_clicked() {
    ui->CommandLine->insertPlainText(stringConvert(this->clipboard));
}


void MainWindow::on_MenuClearOutput_clicked() {
    ui->Output->clear();

    inputCountOutput();
}


void MainWindow::on_MenuDecimal_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("decimal(");
}


void MainWindow::on_MenuDecimalLastResult_clicked(){
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("decimal(lastResult())");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuDecimalClioboard_clicked() {
    ui->CommandLine->clear();
    ui->CommandLine->insertPlainText("decimal(clipboard())");
    on_KeypadCalculate_clicked();
}


void MainWindow::on_MenuClearCommandLine_clicked() {
    ui->CommandLine->clear();
}


void MainWindow::on_KeypadClearCommandLine_clicked() {
    ui->CommandLine->clear();
}


void MainWindow::on_MenuCalculate_clicked() {
    // STORE
    this->currentInput = ui->CommandLine->toPlainText().toStdString();

    // MAKE THE CURSOR THE LAST POSITION
    ui->Output->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);

    // CALCULATE & PROCESSING
    forResult();

    // FOR SCROLL BAR
    ui->Output->verticalScrollBar()->setValue(ui->Output->verticalScrollBar()->maximum());
}

