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
    m_radioListContainer->setSelectionMode(QAbstractItemView::SingleSelection); // only one radio can be selected at a time

    QPushButton *newRadioButton= new QPushButton("Add Radio");

    QVBoxLayout *firstColumn= new QVBoxLayout();
    firstColumn->addWidget(m_radioListContainer);
    firstColumn->addWidget(newRadioButton);

    QHBoxLayout *controlButtonsLayout= new QHBoxLayout();
    QPushButton *playButton= new QPushButton("Play");
    QPushButton *stopButton= new QPushButton("Stop");
    controlButtonsLayout->addWidget(playButton);
    controlButtonsLayout->addWidget(stopButton);

    QHBoxLayout *horizontalLayout= new QHBoxLayout();
    horizontalLayout->addLayout(firstColumn);
    horizontalLayout->addLayout(controlButtonsLayout);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(horizontalLayout);

    // connect buttons
    connect(newRadioButton, SIGNAL(clicked()), this, SLOT(newRadioButtonPressed()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playButtonPressed()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopButtonPressed()));

    m_radioManager.setRadioListViewHandler(this);
    // add test radio
    m_radioManager.addRadio("RockFM", "http://195.55.74.224/cope/rockfm.mp3?GKID=7c175e00f02d11e4a49e00163e914f69&fspref=aHR0cDovL3BsYXllci5yb2NrZm0uZm0vc3dmL3ZpZGVvL3BsYXllci5zd2Y%3D");
}


void MainWindow::newRadioButtonPressed()
{
    AddRadioDialog *dialog= new AddRadioDialog(&m_radioManager);
    dialog->show();
}


void MainWindow::playButtonPressed()
{
    m_radioManager.playRadio(m_radioListContainer->selectedItems().first()->text().toStdString());
}


void MainWindow::stopButtonPressed()
{
    m_radioManager.stop();
}


void MainWindow::updateList(const RadioStationsContainer &container)
{
    m_radioListContainer->clear();
    RadioStationsContainer::StationsMap radioMap= container.getRadioMap();
    RadioStationsContainer::StationsMap::const_iterator itMap= radioMap.begin();
    for (; itMap != radioMap.end(); ++itMap)
    {
        QString radioName= QString::fromStdString(itMap->first);;
        m_radioListContainer->addItem(radioName);
    }
}


