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

    parsin_input(argc, argv);

    fileIn.setFileName(filename);

    if (!fileIn.open(QIODevice::ReadOnly)) {
        cout<<"\nNot found file with flowdump \n";
        return 0;
    }

    QStringList numb,*pnumb=&numb;

    regexp_str();

    regexp_numb(pnumb);

    count_numb= numb.size();

    count_metric=count_numb/9;

    flow * values =new flow [count_metric];


    init_mas(values,pnumb);

    int width=1400;

    int height=700;

    QImage image1 (width, height+1, QImage::Format_ARGB32);


    qDebug()<<"\nwidth="<<width<<" height="<<height<<" count_numb="<<count_numb<<" count_metric="<<count_metric;


    preprocesing(values);

    zcontribution(values);
/*
    Записывает значения values в файл flow

    infile(values);
*/
    setPixel(&image1,values,width,height);

    QLabel i1;

    i1.setWindowTitle("Format_ARGB32");

    i1.setPixmap(QPixmap::fromImage(image1));

    if (!image1.save(outdir+".bmp","BMP")){

        cout<<"\nFile image don't save\n";
    }

    //i1.show();

    fileIn.close();
    return 0;
            //app.exec();
}


