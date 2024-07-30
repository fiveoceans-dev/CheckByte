#include "mainwindow.h"
#include <QFileDialog>
#include <QCryptographicHash>
#include <QFile>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set fixed size for the main window
    setFixedSize(800, 500);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // File path input and browse button
    QHBoxLayout *filePathLayout = new QHBoxLayout();
    lineEditFilePath = new QLineEdit(this);
    pushButtonBrowse = new QPushButton("Browse", this);
    filePathLayout->addWidget(lineEditFilePath);
    filePathLayout->addWidget(pushButtonBrowse);
    mainLayout->addLayout(filePathLayout);

    // Compute checksum button
    pushButtonCompute = new QPushButton("Compute Checksum", this);
    mainLayout->addWidget(pushButtonCompute);

    // Label to display the checksum
    labelChecksum = new QLabel("Checksum: ", this);
    mainLayout->addWidget(labelChecksum);

    // Input field for checksum to compare
    lineEditChecksumInput = new QLineEdit(this);
    lineEditChecksumInput->setPlaceholderText("Enter checksum to compare");
    mainLayout->addWidget(lineEditChecksumInput);

    // Label to display the match status
    labelMatchStatus = new QLabel(this);
    mainLayout->addWidget(labelMatchStatus);

    // Connect signals to slots
    connect(pushButtonBrowse, &QPushButton::clicked, this, &MainWindow::browseFile);
    connect(pushButtonCompute, &QPushButton::clicked, this, &MainWindow::computeChecksum);
    connect(lineEditChecksumInput, &QLineEdit::textChanged, this, &MainWindow::checkChecksumMatch);
}

MainWindow::~MainWindow()
{
}

void MainWindow::browseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File", "", "All Files (*)");
    if (!filePath.isEmpty()) {
        lineEditFilePath->setText(filePath);
    }
}

void MainWindow::computeChecksum()
{
    QString filePath = lineEditFilePath->text();
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a file first.");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Cannot open the selected file.");
        return;
    }

    QCryptographicHash hash(QCryptographicHash::Sha256);
    if (hash.addData(&file)) {
        QString checksum = hash.result().toHex();
        labelChecksum->setText("Checksum: " + checksum);
        checkChecksumMatch();
    } else {
        QMessageBox::warning(this, "Warning", "Failed to compute checksum.");
    }
}

void MainWindow::checkChecksumMatch()
{
    QString computedChecksum = labelChecksum->text().mid(10); // Extract the checksum from the label text
    QString enteredChecksum = lineEditChecksumInput->text();

    if (enteredChecksum.isEmpty()) {
        labelMatchStatus->clear();
        return;
    }

    if (computedChecksum == enteredChecksum) {
        labelMatchStatus->setText("✅ Checksums match");
    } else {
        labelMatchStatus->setText("❌ Checksums do not match");
    }
}
