#include "mainwindow.h"
#include "test_unit_general.h"

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    GenerateHashForm w;
    w.show();
    return a.exec();
    */

    /*if(argc == 0)
    {
        out << "No root dir provided";
        return -1;
    }*/

    QCoreApplication application(argc, argv);

    test_unit_general tests;
    tests.runTest_IndexManager();

    return 0;
}
