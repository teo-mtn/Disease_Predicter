#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include "mafenetre.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MaFenetre fenetre(nullptr);
    fenetre.show();
    return app.exec();
}
