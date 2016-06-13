#include "main.h"

double mid=0, stdev=0;

int k=0;

int main (int argc, char** argv){

    QApplication app(argc, argv);
    QFile fileIn("flow"),fileOut("IMG");

    if (!fileIn.open(QIODevice::ReadOnly)) {
        cout<<"Not faund file In\n";
        return 0;
    }
    QStringList list;

    while (!fileIn.atEnd()){

        QByteArray  line = fileIn.readLine();

        list<<line;
    }

    QStringList filter;

    filter = list.filter(QRegExp("ifIndex|port|pkts|bytes|pr|masklen"));  //("(^[iosdpbt]{1;1})"); //.*\\d+)");

    QStringList abc;

    for (int i=0; i< filter.size(); i++){
        QRegExp RX ("(\\d+)");
        int pos=0;

        //cout<<filter.at(i).toStdString()<<"\n";

        while ((pos = RX.indexIn(filter.at(i), pos)) != -1) {
                  abc<<RX.cap(1);
                  pos += RX.matchedLength();
        }

    }

    k= abc.size();
    int values [k];

    qDebug()<<"ABC\n";
    for (int i=0; i< abc.size(); i++){

        values [i]=abc.at(i).toInt();
        //cout <<abc.at(i).toStdString()<<"  ";
        //qDebug()<<values[i];
    }

    int height=36,width=k/height;

    QImage image1 (width, height, QImage::Format_ARGB32_Premultiplied);
    QImage image2 (width, height, QImage::Format_RGB32);
    QImage image3 (width, height, QImage::Format_Mono);
  //  QImage image4 (width, height, QImage::Format_);

    qDebug()<<"\nwidth="<<width<<" height="<<height<<" k="<<k;

    normalization(values);

    for (int y = 0; y < height; y++) {
           for (int x = 0; x < width-2; x++) {
              /* QRgb argb = qRgb( values[x+y]+10,  // red
                                 values[x+y+1]+10,  // green
                                 values[x+y+2]+10); // blue*/
               QRgb argb = qRgb( values[x+y],  // red
                                 values[x+y+1],  // green
                                 values[x+y+2]); // blue
               //qDebug()<<"\nx="<<x<<" y="<<y<<"     "<<values[x+y]+10<< values[x+y+1]+10<<values[x+y+2]+10<<"\n";
               image1.setPixel(x, y, argb);
               image2.setPixel(x, y, argb);
               //qDebug()<<"pixel x="<<x<<" y="<<y<<"   "<<image2.pixel(x,y);
               //image3.setPixel(x,y,5);

           }
       }

    // QLabel i2("<H1>Format_RGB16</H1>"),i1("<H1>Format_ARGB32"),i3;
    QLabel i2,i1,i3;

    i1.setPixmap(QPixmap::fromImage(image1));
    i1.show();

    i2.setPixmap(QPixmap::fromImage(image2));
    i2.show();

    //i3.setPixmap(QPixmap::fromImage(image3));
    //i3.show();

    return app.exec();
}

void  standeviat(int* mas){
    double sum=0;

    for (int i=0; i<k;i++){

        sum+=mas[i];
    }
    mid=sum/k;
    cout<<"midle\n"<<mid;
    sum=0;
    for (int i=0; i<k;i++){

        sum=sum+(mas[i]-mid)*(mas[i]-mid);
    }

    stdev=sqrt(sum/k-1);
    return;
}

void normalization (int *mas){

    for (int i=0;i<k;i+=9){

        mas[i]=(mas[i]*254)/65535;
        mas[i+1]=(mas[i+1]*254)/65535;
        mas[i+2]=(mas[i+2]*254)/65535;
        mas[i+3]=(mas[i+3]*254)/65535;
        mas[i+4]=(mas[i+4]*254)/4294967295;
        mas[i+5]=(mas[i+5]*254)/4294967295;
        mas[i+6]=(mas[i+6]*254)/142;

    }

    return;
}
