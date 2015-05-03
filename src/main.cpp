#include <iostream>
#include "MainWindow.h"
#include <QApplication>

using namespace std;

int main(int argc, char **argv)
{
    cout << "Hello World!" << endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 500);
    w.show();

    return a.exec();
}

