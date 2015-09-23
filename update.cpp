#include "update.h"

Update::Update(QWidget *parent) : QDialog(parent)
{
    QWidget::setStyleSheet("MainWindow, QMessageBox, QDialog, QMenu, QAction, QMenuBar {background-color: "
                           "#DDD6FF}"
                           "QMenu {"
                           "font: bold}"
                           "QMenu::item:selected {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QMenuBar::item:selected {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QPushButton {"
                           "border: 1px solid black;"
                           "min-height: 20px;"
                           "min-width: 70px;"
                           "padding: 1px;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold}"

                           "QPushButton:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00}"

                           "QPushButton:focus {border-color: yellow}"
                           "LineEdit:hover {background-color: #FFFF99}"
                           "QComboBox:hover {background-color: #FFFF99}"
                           "QDateEdit:hover {background-color: #FFFF99}"
                           "LineEdit:focus {background-color: #FFFFCC}"
                           "QComboBox:focus {background-color: #FFFFCC}"
                           "QDateEdit:focus {background-color: #FFFFCC}"

                           "QProgressBar {"
                           "border: 1px solid black;"
                           "text-align: center;"
                           "color: #00B600;"
                           "font: bold;"
                           "padding: 1px;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
                           "stop: 0 #fff,"
                           "stop: 0.4999 #eee,"
                           "stop: 0.5 #ddd,"
                           "stop: 1 #eee );"
                           "width: 15px;"
                           "}"

                           "QProgressBar::chunk {"
                           "background: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1,"
                           "stop: 0 #78d,"
                           "stop: 0.4999 #46a,"
                           "stop: 0.5 #45a,"
                           "stop: 1 #238 );"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "border: 1px solid black;}"

                           "QTabWidget::pane {"
                           "border: 1px solid #A3A3FF;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "border-bottom-right-radius: 5px;"
                           "border-bottom-left-radius: 5px;"
                           "top: -0.5em}"

                           "QTabWidget::tab-bar {"
                           "left: 5px;}"

                           "QTabBar::tab {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #DDD6FF,"
                           "stop:0.5 #A3A3FF,"
                           "stop:0.51 #A3A3FF,"
                           "stop:1 #DDD6FF);"
                           "border: 1px solid #A3A3FF;"
                           "padding: 1px;"
                           "min-width: 90px;"
                           "border-top-right-radius: 5px;"
                           "border-top-left-radius: 5px;"
                           "font: bold;}"

                           "QTabBar::tab:!selected {background-color: "
                           "#DDD6FF;"
                           "margin-top: 2px;"
                           "font: normal;}"

                           "QTabBar::tab:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;"
                           "font: bold;}"

                           "QDoubleSpinBox {padding-left: 15px; padding-right: 15px; border: 1px;}"

                           "QDoubleSpinBox::up-button {subcontrol-position: right; subcontrol-origin: border; "
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QDoubleSpinBox::up-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"

                           "QDoubleSpinBox::up-arrow {width: 10px; height: 10px;}"
                           "QDoubleSpinBox::down-arrow {width: 10px; height: 10px;}"

                           "QDoubleSpinBox::up-arrow {image: url(:/upblack.png);}"

                           "QDoubleSpinBox::up-arrow:hover {image: url(:/upgreen.png);}"

                           "QDoubleSpinBox::down-arrow {image: url(:/downblack.png);}"

                           "QDoubleSpinBox::down-arrow:hover {image: url(:/downred.png);}"

                           "QDoubleSpinBox::down-button {subcontrol-position: left; subcontrol-origin: border;"
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QDoubleSpinBox::down-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"

                           "QSpinBox {padding-left: 15px; padding-right: 15px; border: 1px;}"

                           "QSpinBox::up-button {subcontrol-position: right; subcontrol-origin: border; "
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QSpinBox::up-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"

                           "QSpinBox::up-arrow {width: 10px; height: 10px;}"
                           "QSpinBox::down-arrow {width: 10px; height: 10px;}"

                           "QSpinBox::up-arrow {image: url(:/upblack.png);}"

                           "QSpinBox::up-arrow:hover {image: url(:/upgreen.png);}"

                           "QSpinBox::down-arrow {image: url(:/downblack.png);}"

                           "QSpinBox::down-arrow:hover {image: url(:/downred.png);}"

                           "QSpinBox::down-button {subcontrol-position: left; subcontrol-origin: border;"
                           "min-width: 15px; min-height: 15px;"
                           "background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #d3d3d3,"
                           "stop:0.5 #bebebe,"
                           "stop:0.51 #bebebe,"
                           "stop:1 #848484);"
                           "color: #231A4C;"
                           "font: bold;}"

                           "QSpinBox::down-button:hover {background-color: "
                           "qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                           "stop:0 #cfcccc,"
                           "stop:0.5 #333232,"
                           "stop:0.51 #000000,"
                           "stop:1 #585c5f);"
                           "color: #00cc00;}"
                           );
}

void Update::iniVersion()
{
    QString iniFileName = "MSOFromSite.ini";
    fileHttpIni = new QFile;
    fileHttpIni->setFileName(iniFileName);
    QNetworkConfigurationManager config;
    if(config.isOnline()){
        if(!fileHttpIni->open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,tr("Attention!"),
                                 tr("Don't open %1!").arg(iniFileName));
        }else{
            url = "http://91.102.219.74/QtProject/MSO/MSO.ini";
            replyIni = httpIni.get(QNetworkRequest(url));
            replyIni->ignoreSslErrors();
            connect(replyIni,SIGNAL(finished()),this,SLOT(httpDoneIni()));
            connect(replyIni,SIGNAL(readyRead()),this,SLOT(httpReadyReadIni()));

        }
    }
}

bool Update::newVersion()
{
    bool resultUpdate = false;
    QSettings settings("MSOFromSite.ini",QSettings::IniFormat);
    QString siteVersion = settings.value("Version").toString();

    QSettings nowSettings("MSO.ini",QSettings::IniFormat);
    nowVersion = nowSettings.value("Version").toString();

    if(siteVersion.toFloat() > nowVersion.toFloat()){
        int que = QMessageBox::warning(this,tr("New Updates"),
                                       tr("New Updates Available! Download?"),
                                       QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
        if(que == QMessageBox::Yes){
            nowSettings.setValue("Version",siteVersion);
            nowSettings.sync();
            resultUpdate = true;
            exeVersion();
        }else{
            QFile fileRe;
            fileRe.setFileName("./MSOFromSite.ini");
            if(fileRe.exists()){
                fileRe.remove();
            }
        }
    }
    return resultUpdate;
}

void Update::exeVersion()
{
    progressDialogExe = new QProgressDialog(this);
    connect(progressDialogExe,SIGNAL(canceled()),this,SLOT(cancelDownLoadExe()));
    fileHttpExe = new QFile("./MSO.tmp");
    fileHttpExe->open(QIODevice::ReadWrite);

    QFile renFile;
    renFile.setFileName("./MSO.exe.bak");
    if(renFile.exists()){
        renFile.remove();
    }

    QFile fileR;
    fileR.setFileName("./MSO.exe");
    fileR.rename("./MSO.exe.bak");
    fileR.close();

    QFile fileRe;
    fileRe.setFileName("./MSOFromSite.ini");
    fileRe.remove();

    url = "http://91.102.219.74/QtProject/MSO/MSO.exe";
    replyExe->ignoreSslErrors();
    replyExe = httpExe.get(QNetworkRequest(url));
    connect(replyExe,SIGNAL(finished()),this,SLOT(httpDoneExe()));
    connect(replyExe,SIGNAL(readyRead()),this,SLOT(httpReadyReadExe()));
    connect(replyExe,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateDataReadProgressExe(qint64,qint64)));
    connect(replyExe,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgressExe(qint64,qint64)));


    progressDialogExe->setLabelText(tr("Downloading MSO ..."));
    progressDialogExe->setEnabled(true);
    progressDialogExe->exec();
}

void Update::tranceVersion()
{
    progressDialogTrance = new QProgressDialog(this);
    connect(progressDialogTrance,SIGNAL(canceled()),this,SLOT(cancelDownLoadTrance()));
    fileHttpTrance = new QFile("./MSO_ru.qm");
    fileHttpTrance->open(QIODevice::WriteOnly);

    url = "http://91.102.219.74/QtProject/MSO/MSO_ru.qm";
    replyTrance->ignoreSslErrors();
    replyTrance = httpTrance.get(QNetworkRequest(url));
    connect(replyTrance,SIGNAL(finished()),this,SLOT(httpDoneTrance()));
    connect(replyTrance,SIGNAL(readyRead()),this,SLOT(httpReadyReadTrance()));
    connect(replyTrance,SIGNAL(uploadProgress(qint64,qint64)),this,SLOT(updateDataReadProgressTrance(qint64,qint64)));
    connect(replyTrance,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(updateDataReadProgressTrance(qint64,qint64)));

    progressDialogTrance->setLabelText(tr("Downloading MSO translation ..."));
    progressDialogTrance->setEnabled(true);
    progressDialogTrance->exec();
}

void Update::cancelDownLoadExe()
{
    if(fileHttpExe->exists()){
        fileHttpExe->close();
        fileHttpExe->remove();
    }
}

void Update::cancelDownLoadTrance()
{
    if(fileHttpTrance->exists()){
        fileHttpTrance->close();
        fileHttpTrance->remove();
    }
}

void Update::restartProgramm()
{
    QProcess::startDetached("./MSO.exe");
    qApp->quit();
}

void Update::httpDoneIni()
{
    fileHttpIni->close();
    newVersion();
}

void Update::httpDoneExe()
{
#ifdef Q_OS_WIN32
    fileHttpExe->rename("./MSO.exe");
#else
    fileHttpExe->rename("./MSO.app");
#endif

    fileHttpExe->close();
    tranceVersion();
}

void Update::httpDoneTrance()
{
    fileHttpTrance->close();
    closeConnection();
    restartProgramm();
}

void Update::closeConnection()
{
    httpIni.destroyed();
    httpExe.destroyed();
    httpTrance.destroyed();
}

void Update::updateDataReadProgressExe(qint64 readBytes,qint64 totalBytes)
{
    progressDialogExe->setMaximum(totalBytes);
    progressDialogExe->setValue(readBytes);
}

void Update::updateDataReadProgressTrance(qint64 readBytes,qint64 totalBytes)
{
    progressDialogTrance->setMaximum(totalBytes);
    progressDialogTrance->setValue(readBytes);
}

void Update::httpReadyReadIni()
{
    if(fileHttpIni)
        fileHttpIni->write(replyIni->readAll());
}

void Update::httpReadyReadExe()
{
    if(fileHttpExe)
        fileHttpExe->write(replyExe->readAll());
    progressDialogExe->hide();
}

void Update::httpReadyReadTrance()
{
    if(fileHttpTrance)
        fileHttpTrance->write(replyTrance->readAll());
    progressDialogTrance->hide();
}
