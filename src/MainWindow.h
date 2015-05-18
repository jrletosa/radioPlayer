#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RadioManager.h"

class QListWidget;
class QListWidgetItem;

class RadioListViewHandler
{
public:

    virtual void updateList(const RadioStationsContainer &container) = 0;
};

class MainWindow : public QMainWindow
                 , public RadioListViewHandler
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void updateList(const RadioStationsContainer &container);

private:

    RadioManager m_radioManager;

    QListWidget *m_radioListContainer;

signals:

public slots:

    void newRadioButtonPressed();
    void playButtonPressed();
    void stopButtonPressed();

};

#endif // MAINWINDOW_H
