#include "main.h"

#ifndef FUNCT_H
#define FUNCT_H

#define    ACCURACY 100

using namespace std;

QFile fileIn("flow"), fileOut("IMG");
QStringList filter,listv;

 double inptIn_stdev=0,outpIn_stdev,srcp_stdev=0,
dstp_stdev=0,bts_stdev=0,pkts_stdev=0,
prot_stdev=0,srcmask_stdev=0,dstmask_stdev=0;

 double inptIn_average=0,outpIn_average,srcp_average=0,
dstp_average=0,bts_average=0,pkts_average=0,
prot_average=0,srcmask_average=0,dstmask_average=0;

int count_numb=0;
int count_metric=0;

struct flow {

    double inptIn;
    double outpIn;
    double srcp;
    double dstp;
    double pkts;
    double bts;
    double prot;
    double srcmask;
    double dstmask;

};

void zcontribution ( flow *mas){

    for (int i=0;i<count_metric;i++){

        mas[i].srcp=abs(mas[i].srcp-srcp_average)*10/srcp_stdev;
        mas[i].dstp=abs(mas[i].dstp-dstp_average)*10/dstp_stdev;
        mas[i].pkts=abs(mas[i].pkts-pkts_average)*10/pkts_stdev;
        mas[i].bts=abs(mas[i].bts-bts_average)*10/bts_stdev;
        mas[i].srcmask=abs(mas[i].srcmask-srcmask_average)*10/(srcmask_stdev+1);
        mas[i].dstmask=abs(mas[i].dstmask-dstmask_average)*10/(dstmask_stdev+1);

    }

    return;
}

void preprocesing ( flow *mas){

    long int s1, s2 ,s3 ,s4,s5,s6,s7,s8,s9;

    s1=s2=s3=s4=s5=s6=s7=s8=s9=0;

    for (int i=0;i<count_metric;i++){

        mas[i].inptIn=round ((mas[i].inptIn*254)/65535*ACCURACY)/ACCURACY;
        mas[i].outpIn=round((mas[i].outpIn*254)/65535*ACCURACY)/ACCURACY;
        srcp_average+=round(mas[i].srcp*ACCURACY)/ACCURACY;
        dstp_average+=round(mas[i].dstp*ACCURACY)/ACCURACY;
        pkts_average+=round(mas[i].pkts*ACCURACY)/ACCURACY;
        bts_average +=round(mas[i].bts*ACCURACY)/ACCURACY;
        mas[i].prot=round((mas[i].prot*254)/142*ACCURACY)/ACCURACY;
        srcmask_average+=round(mas[i].srcmask*ACCURACY)/ACCURACY;
        dstmask_average+=round(mas[i].dstmask*ACCURACY)/ACCURACY;

        s1+=mas[i].inptIn;
        s2+=mas[i].outpIn;
        s3+=mas[i].srcp;
        s4+=mas[i].dstp;
        s5+=mas[i].pkts;
        s6+=mas[i].bts;
        s7+=mas[i].prot;
        s8+=mas[i].srcmask;
        s9+=mas[i].dstmask;

    }

    qDebug() <<"\n"<<"inptIn="<<s1<<" outpIn="<<s2<<" srcp="<<round(srcp_average)<<" dstp="<<round(dstp_average)<<" pkts="<<pkts_average<<" bts="<<bts_average<<" prot="<<s7<<" srcmask="<<srcmask_average<<" dstmask="<<dstmask_average;

    // average среднее арефметическое

    srcp_average   =srcp_average/count_metric;
    dstp_average   =dstp_average/count_metric;
    pkts_average   =pkts_average/count_metric;
    bts_average    =bts_average/count_metric;
    srcmask_average=srcmask_average/count_metric;
    dstmask_average=dstmask_average/count_metric;

    // stdev стандартное отклонение

    for (int i=0; i<count_metric;i+=9){

        srcp_stdev  +=(mas[i].srcp-srcp_average)*(mas[i].srcp-srcp_average);
        dstp_stdev  +=(mas[i].dstp-dstp_stdev)*(mas[i].dstp-dstp_stdev);
        pkts_stdev  +=(mas[i].pkts-pkts_stdev)*(mas[i].pkts-pkts_stdev);
        bts_stdev   +=(mas[i].bts-bts_stdev)*(mas[i].bts-bts_stdev);
    }

    srcp_stdev=sqrt(srcp_stdev/count_metric-1);
    dstp_stdev=sqrt(dstp_stdev/count_metric-1);
    pkts_stdev=sqrt(pkts_stdev/count_metric-1);
    bts_stdev=sqrt (bts_stdev/count_metric-1);

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

void init_mas ( flow *mas ,QStringList *pnumb){

    int j=0;

    for (int i=0; i< count_metric; i++){

        mas[i].inptIn=pnumb->at(j).toInt();
        j++;
        mas[i].outpIn=pnumb->at(j).toInt();
        j++;
        mas[i].srcp=pnumb->at(j).toInt();
        j++;
        mas[i].dstp=pnumb->at(j).toInt();
        j++;
        mas[i].pkts=pnumb->at(j).toInt();
        j++;
        mas[i].bts=pnumb->at(j).toInt();
        j++;
        mas[i].prot=pnumb->at(j).toInt();
        j++;
        mas[i].srcmask=pnumb->at(j).toInt();
        j++;
        mas[i].dstmask=pnumb->at(j).toInt();
        j++;
        //cout <<abc.at(i).toStdString()<<"  ";
        //qDebug()<<values[i];
    }
    return;
}


void infile ( flow* mas){

    QFile outfile("out");

    if(!outfile.open(QIODevice::WriteOnly | QIODevice::Text)){

        cout<<"Can't open file out data";
    }
    QTextStream infile(&outfile);

    for (int i=0;i<count_metric;i++){

        infile<<"FLOW"<<"\n";

        infile<<"input ifIndex:  "<<round(mas[i].inptIn)<<"\n";
        infile<<"output ifIndex: "<<round(mas[i].outpIn)<<"\n";
        infile<<"src port:       "<<round(mas[i].srcp)<<"\n";
        infile<<"dst port:       "<<round(mas[i].dstp)<<"\n";
        infile<<"pkts:           "<<round(mas[i].pkts)<<"\n";
        infile<<"bytes:          "<<round(mas[i].bts)<<"\n";
        infile<<"protocol:       "<<round(mas[i].pkts)<<"\n";
        infile<<"src masklen:    "<<round(mas[i].srcmask)<<"\n";
        infile<<"dst masklen:    "<<round(mas[i].dstmask)<<"\n";
        infile<<"\n";

    }

    outfile.close();
}
#endif // FUNCT_H
