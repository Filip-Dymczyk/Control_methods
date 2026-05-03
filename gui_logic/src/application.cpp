#include "application.h"
#include <QtWidgets/QApplication>
#include "main_window.h"

int
Application::exec(int argc, char** argv)
{
    QApplication app(argc, argv);
    Main_Window* main_window = new Main_Window();
    main_window->show();  // First show so that the view is set up for centralizing.
    main_window->centralize();
    int const result = app.exec();
    // main_window is automatically deleted by Qt when app.exec() completes via WA_DeleteOnClose
    return result;
}
