#include "./views/gamewindow.h"

#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    srand(time(NULL)); // random seeder for the whole project, only needs to be called once
    w.show();
    return a.exec();
}
