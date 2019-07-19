#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QStringRef>
#include <iostream>
#include <bitset>
#include <QUdpSocket>
#include <QDateTime>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    QList<QLabel *> labels; // for storing lables

    ~Dialog();


private:
    Ui::Dialog *ui;
    QUdpSocket *udpSocket;
    void sendDatagram(int8_t);


private slots:
  void updateVal(int num) ;






};

#endif // DIALOG_H
