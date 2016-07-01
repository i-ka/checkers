#include "Field.hpp"
#include "Checker.hpp"

#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QQuickView view;
    qmlRegisterType<Field>("GameComponents",1,0,"Field");
    qmlRegisterType<Checker>("GameComponents",1,0,"Checker");
    view.setSource(QUrl("qrc:///main.qml"));
    view.show();

    return a.exec();
}
