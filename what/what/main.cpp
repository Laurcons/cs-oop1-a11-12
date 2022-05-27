#include <QtWidgets>
#include <QtWidgets/QApplication>
#include "ui.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    bub::tutorial_repo* repo = new bub::file_tutorial_repo{ "data.dat" };
    bub::tutorial_controller ctrl{ repo };

    AppUi* ui = new AppUi{ ctrl };
    ui->show();

    return a.exec();
}
