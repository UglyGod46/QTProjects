#include <QApplication>
#include "authwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    AuthWindow window;
    window.setWindowTitle("Авторизация");
    window.resize(400, 200);
    window.show();
    return app.exec();
}
