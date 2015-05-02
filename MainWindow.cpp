#include "MainWindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // initialize Main Window layout
    QListWidget *radioListContainer= new QListWidget();
    radioListContainer->setStyleSheet("QListWidget::item {"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-color:black;"
                                      "background-color: green;"
                                      "}"
                                      "QListWidget::item:selected {"
                                      "background-color: red;"
                                      "}");

    radioListContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    //radioListContainer->setMinimumHeight(50);
    radioListContainer->addItem("RockFM");

    QPushButton *addRadioButton= new QPushButton("Add Radio");

    QVBoxLayout *firstColumn= new QVBoxLayout();
    firstColumn->addWidget(radioListContainer);
    firstColumn->addWidget(addRadioButton);

    QVBoxLayout *buttonsLayout= new QVBoxLayout();
    QPushButton *testButton= new QPushButton();
    buttonsLayout->addWidget(testButton);

    QHBoxLayout *horizontalLayout= new QHBoxLayout();
    horizontalLayout->addLayout(firstColumn);
    horizontalLayout->addLayout(buttonsLayout);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(horizontalLayout);

    // connect buttons
    connect(radioListContainer, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(radioSelected(QListWidgetItem *)));

    // add test radio
    m_radioManager.addRadio("RockFM", "http://195.55.74.224/cope/rockfm.mp3?GKID=7c175e00f02d11e4a49e00163e914f69&fspref=aHR0cDovL3BsYXllci5yb2NrZm0uZm0vc3dmL3ZpZGVvL3BsYXllci5zd2Y%3D");
}


void MainWindow::radioSelected(QListWidgetItem *item)
{
    QString selectedText= item->text();
    m_radioManager.playRadio(selectedText.toStdString());
}


