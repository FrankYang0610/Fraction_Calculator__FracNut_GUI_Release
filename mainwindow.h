#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void welcomeScreen();

private slots:
    void on_Keypad1_clicked();

    void on_Keypad2_clicked();

    void on_Keypad3_clicked();

    void on_KeypadPlus_clicked();

    void on_Keypad4_clicked();

    void on_Keypad5_clicked();

    void on_Keypad6_clicked();

    void on_Keypad7_clicked();

    void on_Keypad8_clicked();

    void on_Keypad9_clicked();

    void on_Keypad0_clicked();

    void on_KeypadLeftBracket_clicked();

    void on_KeypadRightBracket_clicked();

    void on_KeypadDot_clicked();

    void on_KeypadMinus_clicked();

    void on_KeypadMultiply_clicked();

    void on_KeypadDivide_clicked();

    void on_KeypadCalculate_clicked();

    void on_CommandLine_textChanged();

    void on_KeypadBackspace_clicked();

    void on_KeypadClearOutput_clicked();

    void on_KeypadLeftParentheses_clicked();

    void on_KeypadRightparentheses_clicked();

    void on_MenuGetForHelp_clicked();

    void on_MenuLastResult_clicked();

    void on_MenuRemoveLastResult_clicked();

    void on_MenuSaveToClipboard_clicked();

    void on_MenuClipboard_clicked();

    void on_MenuRemoveClipboard_clicked();

    void on_MenuUseLastResult_clicked();

    void on_MenuUseClipboard_clicked();

    void on_MenuClearOutput_clicked();

    void on_MenuDecimal_clicked();

    void on_MenuDecimalLastResult_clicked();

    void on_MenuDecimalClioboard_clicked();

    void on_MenuClearCommandLine_clicked();


    void on_KeypadClearCommandLine_clicked();

    void on_MenuCalculate_clicked();

public:
    Ui::MainWindow *ui;

// FOR CALCULATIONS
public:
    std::string currentInput = "";
    unsigned int inputCount = 1;
    std::string lastResult = "0";
    std::string clipboard = "0";

public:
    void inputCountOutput();
    void outputCountOutput();

public:
    void forResult();

public:
    void getHelp();

// KEY EVENTS
protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *target, QEvent *event);
};
#endif // MAINWINDOW_H
