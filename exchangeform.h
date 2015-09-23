#ifndef EXCHANGEFORM_H
#define EXCHANGEFORM_H

#include <QtWidgets>
#include <QtNetwork>

class ExchangeForm : public QDialog
{
    Q_OBJECT
public:
    ExchangeForm(QWidget *parent = 0);

private slots:
    void readExchanges();
    void writeExchanges();

private:
    QPushButton *exchangeButton;
    QDialogButtonBox *buttonBox;
};

#endif // EXCHANGEFORM_H
