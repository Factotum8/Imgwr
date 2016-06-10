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


    QStringList abc;

    for (int i=0; i< list.size(); i++){
        QRegExp RX("(\\d+)"); //("(^T*\\d+)")
        int pos=0;
        //cout<<list.at(i).toStdString()<<"\n";


        while ((pos = RX.indexIn(list.at(i), pos)) != -1) {
                  abc<<RX.cap(1);
                  pos += RX.matchedLength();
        }

    }

    k= abc.size();
    int values [k];

    //cout<<"ABC\n";
    for (int i=0; i< abc.size(); i++){

        values [i]=abc.at(i).toInt();
        //qDebug()<<values[i];
    }

    int width=100, height=k/width;

    QImage image1 (width, height, QImage::Format_ARGB32);
    QImage image2 (width, height, QImage::Format_RGB16);
    QImage image3 (width, height, QImage::Format_Mono);
  //  QImage image4 (width, height, QImage::Format_);

    //qDebug()<<"\nwidth="<<width<<" height="<<height<<" k="<<k;
    for (int y = 0; y < height; y++) {
           for (int x = 0; x < width-2; x++) {
               QRgb argb = qRgb( values[x+y],  // red
                                 values[x+y+1],  // green
                                 values[x+y+2]); // blue
               //qDebug()<<"\nx="<<x<<" y="<<y<<values[x+y]<< values[x+y+1]<<values[x+y+2]<<"\n";
               image1.setPixel(x, y, argb);
               image2.setPixel(x, y, argb);

               image3.setPixel(x,y,5);

           }
       }


    QLabel i2("<H1>Format_RGB16</H1>"),i1("<H1>Format_ARGB32"),i3;

    i1.setPixmap(QPixmap::fromImage(image1));
    i1.show();

    i2.setPixmap(QPixmap::fromImage(image2));
    i2.show();

    i3.setPixmap(QPixmap::fromImage(image3));
    i3.show();

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
