#include "main.h"
#define    ACCURACY 100



long long unsigned int inptIn_stdev=0,outpIn_stdev,srcp_stdev=0,
               dstp_stdev=0,bts_stdev=0,pkts_stdev=0,
                 prot_stdev=0,srcmask_stdev=0,dstmask_stdev=0;

long long unsigned int inptIn_average=0,outpIn_average,srcp_average=0,
               dstp_average=0,bts_average=0,pkts_average=0,
                prot_average=0,srcmask_average=0,dstmask_average=0;

int k=0;

QFile fileIn("flow"), fileOut("IMG");
QStringList filter,listv;

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

    k= numb.size();

    long int values [k];



    init_mas(values,pnumb);

    //int height=150,width=k/height;
    qDebug()<<"k="<<k<<"\n";
    int width=1200;
    //cin>>width;
    int height=700;

    QImage image1 (width, height+1, QImage::Format_ARGB32_Premultiplied);
    QImage image2 (width, height+1, QImage::Format_RGB32);
    QImage image3 (width, height+1, QImage::Format_Indexed8);

    qDebug()<<"\nwidth="<<width<<" height="<<height<<" k="<<k;

    infile(values);

    preprocesing(values);

    infile(values);

    zcontribution(values);

    infile(values);

 /*   for (int y = 0; y <= height; y++) {
       // cout<<"\ny="<<y<<" ";
           for (int x = 0; x < width-2; x+=3) {
               QRgb argb;
                if (y<height)  {argb = qRgb(
                                     values[x+y*width],              // red
                                     values[x+y*width+1],            // green
                                     values[x+y*width+2]);           // blue
                 }else {
                                argb = qRgb( 0xff,  // red
                                             0xff,  // green
                                             0xff); // blue
                 }
               image1.setPixel(x, y, argb);
               image2.setPixel(x, y, argb);
               //cout<<" pixel("<<x+y*width<<","<<x+y*width+1<<","<<x+y*width+2<<")";

           }
       }*/


    for (int i = 0; i <k; i+=9) {
        QRgb argb;
        argb = qRgb(
                    values[i+6],              // red
                    values[i],               // green
                    values[i+1]);           // blue

        //qDebug()<<values[i+2]+values[i+3]+values[i+4]<<"   "<<values[i+5]+values[i+7]+values[i+8];


        image1.setPixel(values[i+2]+values[i+3]+values[i+4],values[i+5]+values[i+7]+values[i+8], argb);
        image2.setPixel(values[i+2]+values[i+3]+values[i+4],values[i+5]+values[i+7]+values[i+8], argb);
        //cout<<" pixel("<<x+y*width<<","<<x+y*width+1<<","<<x+y*width+2<<")";

    }

    // QLabel i2("<H1>Format_RGB16</H1>"),i1("<H1>Format_ARGB32"),i3;
    QLabel i2,i1,i3;

    i1.setPixmap(QPixmap::fromImage(image1));
    i1.show();

    i2.setPixmap(QPixmap::fromImage(image2));
    i2.show();

 /*   for (int y = 0; y < height; y++) {
           for (int x = 0; x < width; x++) {
               image3.setPixel(x,y,values[y*width+x]);

           }
       }
    QLabel i3;
    i3.setPixmap(QPixmap::fromImage(image3));
    i3.show();*/
    fileIn.close();
    return app.exec();
}

/*void standard_deviation(int* mas){
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
}*/

/*void normalization (int *mas){

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
}*/

void zcontribution (long int *mas){

    for (int i=0;i<k;i+=9){
//        //qDebug()<<mas[i+2];
//        mas[i+2]=abs(mas[i+2]-(long int)srcp_average)*10/srcp_stdev;
//        //qDebug()<<mas[i+2];
//        mas[i+3]=((double)mas[i+3]-dstp_average)/dstp_stdev;
//        mas[i+4]=((double)mas[i+4]-pkts_average)/pkts_stdev;
//        mas[i+5]=((double)mas[i+5]-bts_average)/bts_stdev;
//        mas[i+7]=((double)mas[i+7]-srcmask_average)/srcmask_stdev;
//        mas[i+8]=((double)mas[i+8]-dstmask_average)/dstmask_stdev;

               mas[i+2]=abs(mas[i+2]-(long int)srcp_average)*10/srcp_stdev;
               mas[i+3]=abs(mas[i+3]-(long int)dstp_average)*10/dstp_stdev;
               mas[i+4]=abs(mas[i+4]-(long int)pkts_average)*10/pkts_stdev;
               mas[i+5]=abs(mas[i+5]-(long int)bts_average)*10/bts_stdev;
               mas[i+7]=abs(mas[i+7]-(long int)srcmask_average)*10/(srcmask_stdev+1);
               mas[i+8]=abs(mas[i+8]-(long int)dstmask_average)*10/(dstmask_stdev+1);

    }

    return;
}
void preprocesing (long int *mas){

    int t=k/9;
    double a=0;

    for (int i=0;i<k;i+=9){

        //mas[i]
        a=round ((double)(mas[i]*254)/65535*ACCURACY)/ACCURACY;
        mas[i+1]=(mas[i+1]*254)/65535;
        srcp_average+=mas[i+2];
        dstp_average+=mas[i+3];
        pkts_average+=mas[i+4];
        bts_average +=mas[i+5];
        mas[i+6]=(mas[i+6]*254)/142;
        srcmask_average+=mas[i+7];
        dstmask_average+=mas[i+8];

    }
    // average среднее арефметическое
    srcp_average   =srcp_average/t;
    dstp_average   =dstp_average/t;
    pkts_average   =pkts_average/t;
    bts_average    =bts_average/t;
    srcmask_average=srcmask_average/t;
    dstmask_average=dstmask_average/t;
    // stdev стандартное отклонение
    for (int i=0; i<k;i+=9){

        srcp_stdev  +=(mas[i+2]-srcp_average)*(mas[i+2]-srcp_average);
        dstp_stdev  +=(mas[i+3]-dstp_stdev)*(mas[i+3]-dstp_stdev);
        pkts_stdev  +=(mas[i+4]-pkts_stdev)*(mas[i+4]-pkts_stdev);
        bts_stdev   +=(mas[i+5]-bts_stdev)*(mas[i+5]-bts_stdev);
    }

    srcp_stdev=sqrt(srcp_stdev/t-1);
    dstp_stdev=sqrt(dstp_stdev/t-1);
    pkts_stdev=sqrt(pkts_stdev/t-1);
    bts_stdev=sqrt (bts_stdev/t-1);

    return;
}

void regexp_str(){
    while (!fileIn.atEnd()){

        QByteArray  line = fileIn.readLine();

        filter<<line;
    }

    listv=filter.filter(QRegExp("ifIndex|port|pkts|bytes|pr|masklen"));  //("(^[iosdpbt]{1;1})"); //.*\\d+)");
}

void regexp_numb(QStringList *pnumb){

    for (int i=0; i< listv.size(); i++){
        QRegExp RX ("(\\d+)");
        int pos=0;

        while ((pos = RX.indexIn(listv.at(i), pos)) != -1) {
                  *pnumb<<RX.cap(1);
                  pos += RX.matchedLength();
        }

    }
    return;
}

void init_mas (long int *mas,QStringList *pnumb){

    for (int i=0; i< k; i++){

            mas[i]=pnumb->at(i).toInt();
            //cout <<abc.at(i).toStdString()<<"  ";
            //qDebug()<<values[i];
    }
    return;
}

/*long double Infbit(){

    long double inf=0;
    void *p=NULL;

    p= new char [sizeof (long double)];

    for (int i=sizeof(inf)-1;i>=0;i--){
        long double j=0;
        (i>2)? (inf | ((long double )*p<<j)):(inf |((long double)0<<j));
    }

    return inf;}*/

void infile (long *mas){

    QFile outfile("out");

    if(outfile.open(QIODevice::WriteOnly | QIODevice::Text)){

        cout<<"Can't open file";
    }
    QTextStream infile(&outfile);

    for (int i=0;i<k;i+=9){
        infile<<"FLOW"<<"\n";

        infile<<"input ifIndex:  "<<mas[i]<<"\n";
        infile<<"output ifIndex: "<<mas[i+1]<<"\n";
        infile<<"src port:       "<<mas[i+3]<<"\n";
        infile<<"dst port:       "<<mas[i+4]<<"\n";
        infile<<"pkts:           "<<mas[i+5]<<"\n";
        infile<<"bytes:          "<<mas[i+6]<<"\n";
        infile<<"protocol:       "<<mas[i+7]<<"\n";
        infile<<"src masklen:    "<<mas[i+8]<<"\n";
        infile<<"dst masklen:    "<<mas[i+9]<<"\n";
        infile<<"dst masklen:    "<<mas[i+9]<<"\n";

    }

    outfile.close();
}
