#include "mainController.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPushButton>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto vlMain = new QVBoxLayout();

    auto vlGallow = new QVBoxLayout();
    QLabel* lblGallow = new QLabel(this);

    lblGallow->setMinimumSize(50,50);
    lblGallow->setMaximumSize(50,50);
    lblGallow->setText("Test");

    vlGallow->addWidget(lblGallow);

    QLabel* lblSecretWord = new QLabel(this);

    lblSecretWord->setMinimumSize(20,80);
    lblSecretWord->setMaximumSize(20,80);
    lblSecretWord->setText("_ _ _ _ _ _ ");

    vlGallow->addWidget(lblSecretWord);

    vlMain->addLayout(vlGallow);


}

MainWindow::~MainWindow()
{
    delete ui;
}
