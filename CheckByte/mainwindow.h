#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseFile();
    void computeChecksum();
    void checkChecksumMatch();

private:
    QLineEdit *lineEditFilePath;
    QPushButton *pushButtonBrowse;
    QPushButton *pushButtonCompute;
    QLabel *labelChecksum;
    QLineEdit *lineEditChecksumInput;
    QLabel *labelMatchStatus;
};

#endif // MAINWINDOW_H
