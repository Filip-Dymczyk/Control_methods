// Control methods for linear SISO dynamical systems.
// Author: Filip Dymczyk

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QPushButton button("Hello, World!");
    button.resize(200, 100);
    button.show();

    return app.exec();
}