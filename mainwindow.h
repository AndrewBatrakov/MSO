#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSql>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void createPanel();
    void readSettings();
    void writeSettings();
    void createActions();
    void createMenu();
    void aboutProgramm();
    void splitterCreate();
    void createContextMenu();
    void viewTemplateTable(QString);
    void sortTable(int);
    void updatePanel(QModelIndex);
    void prefixForm();

    void addRecordOfTable();
    void deleteRecordOfTable();
    void editRecordOfTable();
    void copyRecordOfTable();

    void viewNode();
    void viewEmployee();
    void viewPost();
    void viewSubdivision();
    void viewMedicalService();
    void viewTreatment();
    void viewDisease();
    void viewLocation();
    void viewTypeOfWork();
    void viewOrganization();
    void viewPreparation();
    void viewPreparationDoc();

    void putBaseProcedure();
    void getBaseProcedure();
    void searchProcedure();
    //void readItem();
    void exchangeData();

    void sendMail();

private:
    QVBoxLayout *mainLayout;
    //QListWidget *listWidget;
    QWidget *panel;
    QSplitter *splitter;

    QTableView *tableView;
    QLabel *tableLabel;
    QSqlRelationalTableModel *templateModel;

    QPushButton *addRecordButton;
    QPushButton *editRecordButton;
    QPushButton *deleteRecordButton;

    QAction *addAction;
    QAction *deleteAction;
    QAction *editAction;
    QAction *copyAction;

    QMenu *fileMenu;
    QAction *prefixAction;
    QAction *exitAction;

    QMenu *referenceMenu;
    QAction *nodeAction;
    QAction *employeeAction;
    QAction *subdivisionAction;
    QAction *postAction;
    QAction *medicalService;
    QAction *treatmentAction;
    QAction *diseaseAction;
    QAction *locationActon;
    QAction *typeOfWorkAction;
    QAction *organizationAction;
    QAction *preparationAction;

    QMenu *documentMenu;
    QAction *preparationDocAction;

    QMenu *reportMenu;

    QMenu *serviceMenu;
    //QAction *ademantAction;
    //QAction *ftpAction;
    QAction *searchAction;
    QAction *putAction;
    QAction *getAction;
    QAction *exchangeAction;
    //QAction *vaccumAction;

    QMenu *helpMenu;
    QAction *aboutQtAction;
    QAction *aboutProgAction;

    //int addressInt, portInt;
    bool setFilter;
    QString filterTable;
    QFile fileExchange;

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
