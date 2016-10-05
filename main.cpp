#include "main.h"

/*
o input ifIndex
1 output ifIndex
2 src port
3 dst port
4 pkts
5 bytes
6 protocol
7 src masklen
8 dst masklen
*/

int main (int argc, char** argv){

    QApplication app(argc, argv);

    //qsrand((unsigned)time(0));

    if (!fileIn.open(QIODevice::ReadOnly)) {
        cout<<"Not faund file In\n";
        return 0;
    }
    QStringList numb,*pnumb=&numb;

    regexp_str();

    regexp_numb(pnumb);

    count_numb= numb.size();

    count_metric=count_numb/9;

    flow values [count_metric];




    init_mas(values,pnumb);

    int width=1400;

    int height=700;

    QImage image1 (width, height+1, QImage::Format_ARGB32_Premultiplied);
    QImage image2 (width, height+1, QImage::Format_RGB32);

    qDebug()<<"\nwidth="<<width<<" height="<<height<<" count_numb="<<count_numb<<" count_metric="<<count_metric;


    preprocesing(values);

    zcontribution(values);

    infile(values);


    for (int i = 0; i <count_numb/9; i++) {
        QRgb argb;
        argb = qRgb(
                    round(values[i].bts),              // red
                    round(values[i].inptIn),           // green
                    round(values[i].outpIn));          // blue

        //qDebug()<<values[i+2]+values[i+3]+values[i+4]<<"   "<<values[i+5]+values[i+7]+values[i+8];


        image1.setPixel(round(values[i].srcp+values[i].dstp+values[i].pkts),round(values[i].prot+values[i].srcmask+values[i].dstmask), argb);
        image2.setPixel(round(values[i].srcp+values[i].dstp+values[i].pkts),round(values[i].prot+values[i].srcmask+values[i].dstmask), argb);
        //cout<<" pixel("<<x+y*width<<","<<x+y*width+1<<","<<x+y*width+2<<")";

    }

    QLabel i2,i1;

    i2.setWindowTitle("Format_RGB16");
    i1.setWindowTitle("Format_ARGB32");

    i1.setPixmap(QPixmap::fromImage(image1));
    i1.show();

    i2.setPixmap(QPixmap::fromImage(image2));
    //i2.show();


    fileIn.close();
    return app.exec();
}


