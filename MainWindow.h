#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RadioManager.h"

class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:

    RadioManager m_radioManager;

signals:

public slots:

    void radioSelected(QListWidgetItem *item);

};

#endif // MAINWINDOW_H
