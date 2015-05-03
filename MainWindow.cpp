#include "MainWindow.h"
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>
#include "AddRadioDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // initialize Main Window layout
    m_radioListContainer= new QListWidget();
    m_radioListContainer->setStyleSheet("QListWidget::item {"
                                      "border-style: solid;"
                                      "border-width:1px;"
                                      "border-color:black;"
                                      "background-color: green;"
                                      "}"
                                      "QListWidget::item:selected {"
                                      "background-color: red;"
                                      "}");

    m_radioListContainer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    QPushButton *addRadioButton= new QPushButton("Add Radio");

    QVBoxLayout *firstColumn= new QVBoxLayout();
    firstColumn->addWidget(m_radioListContainer);
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
    connect(m_radioListContainer, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(radioSelected(QListWidgetItem *)));
    connect(addRadioButton, SIGNAL(clicked()), this, SLOT(addRadioButtonPressed()));

    m_radioManager.setRadioListViewHandler(this);
    // add test radio
    m_radioManager.addRadio("RockFM", "http://195.55.74.224/cope/rockfm.mp3?GKID=7c175e00f02d11e4a49e00163e914f69&fspref=aHR0cDovL3BsYXllci5yb2NrZm0uZm0vc3dmL3ZpZGVvL3BsYXllci5zd2Y%3D");
}


void MainWindow::radioSelected(QListWidgetItem *item)
{
    QString selectedText= item->text();
    m_radioManager.playRadio(selectedText.toStdString());
}


void MainWindow::addRadioButtonPressed()
{
    AddRadioDialog *dialog= new AddRadioDialog(&m_radioManager);
    dialog->show();
}


void MainWindow::updateList(const RadioStationsContainer &container)
{
    m_radioListContainer->clear();
    RadioStationsContainer::StationsMap radioMap= container.getRadioMap();
    RadioStationsContainer::StationsMap::const_iterator itMap= radioMap.begin();
    for (; itMap != radioMap.end(); ++itMap)
    {
        QString radioName= QString::fromStdString(itMap->first);
        m_radioListContainer->addItem(radioName);
    }
}


