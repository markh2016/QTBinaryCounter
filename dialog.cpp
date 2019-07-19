#include "dialog.h"
#include "ui_dialog.h"
#include <string>

/* Written by MD Harrington 15 July 2019    */


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->RotaryDial,SIGNAL(valueChanged(int)),this,SLOT(updateVal(int)));

     udpSocket = new QUdpSocket(this);


    // assign each label to the array

      for (int i = 0; i < 8;i++)
      {
         labels << new QLabel(this);
      }

      labels[7] =  ui->bit_0 ;
      labels[6]=   ui->bit_1 ;
      labels[5]=   ui->bit_2 ;
      labels[4]=   ui->bit_3 ;
      labels[3]=   ui->bit_4 ;
      labels[2]=   ui->bit_5 ;
      labels[1]=   ui->bit_6 ;
      labels[0]=   ui->bit_7 ;


      ui->hexdisplay_1 -> setPalette(Qt::red);
      ui->hexdisplay_2 -> setPalette(Qt::red);
      ui->decDisplay_1 -> setPalette(Qt::blue );

}

void Dialog::sendDatagram(int8_t num){

    {



        QByteArray datagram ;
        QDataStream out(&datagram, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_1);
        out << num ;
        udpSocket->writeDatagram(datagram, QHostAddress::LocalHost, 4000);

    }


}



void Dialog::updateVal(int num)

{

    uint8_t  number = static_cast<uint8_t>(num) ;
    ulong uMSB ;
    ulong uLSB ;
    char indexmax = 0; // for mesuring the length of the string

    std::string binary = std::bitset<8>(number).to_string(); //to binary


    //  create two strings to hold binary nibbles
    std::string MSB = binary.substr(0, binary.length()/2);
    std::string LSB =binary.substr(binary.length()/2);

    QString binnumber =QString::number(num,10) ;

    QString QMSB(QString::fromUtf8(MSB.c_str())); // convert back to Qstring object
    QString QLSB(QString::fromUtf8(LSB.c_str())); // convert back to Qstring object

    // create the hex conversion for both nibble
    std::bitset<4>DMSB(MSB) ;
    uMSB = DMSB.to_ulong() ;

    std::bitset<4>DLSB(LSB) ;
    uLSB = DLSB.to_ulong() ;


    /*

    qDebug()  << "Convert to Int    = " << binnumber << '\n';
    qDebug()  << "Binary number is " << QString::fromUtf8(binary.c_str());
    qDebug()  << "msb is " << QString::fromUtf8(MSB.c_str());
    qDebug()  << "Msb dec is " << QString::number(uMSB,10) ;
    qDebug()  << "Msb hex is " << QString::number(uMSB,16) ;
    qDebug()  << "lsb is " << QString::fromUtf8(LSB.c_str());
    qDebug()  << "lsb dec is " << QString::number(uLSB,10) ;
    qDebug()  << "lsb hex is " << QString::number(uLSB,16) ;
    qDebug()  << "Length of  binary string is " <<  binary.length();

    */

    binnumber =  QString::fromUtf8(binary.c_str());

     // assign length of string to indexmax
    indexmax = static_cast<char>(binary.length()) ;

    for (uint8_t x = 0 ; x < indexmax ; x++ )
    {
        labels[x]->setText(binnumber.at(x)) ;

    }
    ui->hexdisplay_1->display(QString::number(uLSB,16) );
    ui->hexdisplay_2->display(QString::number(uMSB,16) );


    ui->decDisplay_1->display(num);

   sendDatagram(static_cast<uint8_t>(num)) ;

}




Dialog::~Dialog()
{
    delete ui;
}

