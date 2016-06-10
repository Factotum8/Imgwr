#include "main.h"


int main (){

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

    int k= abc.size(),values [k];

    cout<<"ABC\n";
    for (int i=0; i< abc.size(); i++){

        values [i]=abc.at(i).toInt();
        cout<<values[i]<<"\n";
    }

    int width=500, height=k/width;

    QImage image1 (width, height, QImage::Format_ARGB32);
    QImage image2 (width, height, QImage::Format_RGB16);
    QImage image3 (width, height, QImage::Format_Mono);

    for (int y = 0; y < height; y++) {
           for (int x = 0; x < width-2; x++) {
               QRgb argb = qRgb( values[x+y],  // red
                                 values[x+y+1],  // green
                                 values[x+y+2]; // blue
               image1.setPixel(x, y, argb);
               image2.setPixel(x, y, argb);
           }
       }
    QLabel i2,i1,i3;

    i1.setPixmap(QPixmap::fromImage(i1));
    i1.show();

    i2.setPixmap(QPixmap::fromImage(i2));
    i2.show();

    return 0;
}
