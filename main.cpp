#include "mainwindow.h"
#include <QApplication>

#include "update.h"
#include "registrationform.h"
#include "mystyle.h"

int main(int argc, char *argv[])
{
    //QApplication::setStyle(new MyStyle);
    QApplication app(argc, argv);

    Update update;
    update.iniVersion();

    QTranslator translator;
    if(translator.load("MSO_ru.qm"))
        app.installTranslator(&translator);

    RegistrationForm regForm;
    if(!regForm.checkFile()){
        return 0;
    }
    if(!regForm.checkInput()){
        return 0;
    }

    MainWindow w;
    w.show();

    return app.exec();
}
