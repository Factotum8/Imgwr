#include "main.h"

#ifndef FUNCT_H
#define FUNCT_H

#define    ACCURACY 100
#define    TYPEMETRIC double

using namespace std;

QFile       fileIn("flow"), fileOut("IMG");
QStringList filter,listv;

struct flow {

    TYPEMETRIC inptIn;
    TYPEMETRIC outpIn;
    TYPEMETRIC srcp;
    TYPEMETRIC dstp;
    TYPEMETRIC pkts;
    TYPEMETRIC bts;
    TYPEMETRIC prot;
    TYPEMETRIC srcmask;
    TYPEMETRIC dstmask;

};


flow stdev,average;

int count_numb=0;
int count_metric=0;

TYPEMETRIC  norm_65535 (TYPEMETRIC var){

    return (round ((var*254)/65535*ACCURACY)/ACCURACY);

}

TYPEMETRIC round_m (TYPEMETRIC var){

    return (round(var*ACCURACY)/ACCURACY);

}

void zcontribution ( flow *mas){

    for (int i=0;i<count_metric;i++){

        mas[i].srcp=abs(mas[i].srcp-average.srcp)*10/stdev.srcp;
        mas[i].dstp=abs(mas[i].dstp-average.dstp)*10/stdev.dstp;
        mas[i].pkts=abs(mas[i].pkts-average.pkts)*10/stdev.pkts;
        mas[i].bts=abs(mas[i].bts-average.bts)*10/stdev.bts;
        mas[i].srcmask=abs(mas[i].srcmask-average.srcmask)*10/stdev.srcmask;
        mas[i].dstmask=abs(mas[i].dstmask-average.dstmask)*10/stdev.dstmask;

    }

    return;
}


void preprocesing ( flow *mas){

    long int s1, s2 ,s3 ,s4,s5,s6,s7,s8,s9;

    s1=s2=s3=s4=s5=s6=s7=s8=s9=0;

    for (int i=0;i<count_metric;i++){

        mas[i].inptIn=norm_65535(mas[i].inptIn);

        mas[i].outpIn=norm_65535(mas[i].outpIn);

        average.srcp+=round_m(mas[i].srcp);

        average.dstp+=round_m(mas[i].dstp);

        average.pkts+=round_m(mas[i].pkts);

        average.bts +=round_m(mas[i].bts);

        mas[i].prot=(round((mas[i].prot*254)/143*ACCURACY)/ACCURACY);

        average.srcmask+=round_m(mas[i].srcmask);

        average.dstmask+=round_m(mas[i].dstmask);

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

    average.srcp=round_m( average.srcp);
    average.dstp=round_m( average.dstp);
    average.pkts =round_m( average.pkts);
    average.bts=round_m( average.bts);
    average.srcmask=round_m( average.srcmask);
    average.dstmask=round_m( average.dstmask);



    qDebug() <<"\n"<<"inptIn="<<s1<<" outpIn="<<s2<<" srcp="<<round(average.srcp)<<" dstp="<<round(average.dstp)<<" pkts="
                    <<average.pkts<<" bts="<<average.bts<<" prot="<<s7<<" srcmask="<<average.srcmask<<" dstmask="<<average.dstmask;

    // average среднее арефметическое

    average.srcp        =round_m(average.srcp/count_metric);
    average.dstp        =round_m(average.dstp/count_metric);
    average.pkts        =round_m(average.pkts/count_metric);
    average.bts         =round_m(average.bts/count_metric);
    average.srcmask     =round_m(average.srcmask/count_metric);
    average.dstmask     =round_m(average.dstmask/count_metric);

    // stdev стандартное отклонение

    for (int i=0; i<count_metric;i+=9){

        stdev.srcp      +=(mas[i].srcp-average.srcp)*(mas[i].srcp-average.srcp);
        stdev.dstp      +=(mas[i].dstp-average.dstp)*(mas[i].dstp-average.dstp);
        stdev.pkts      +=(mas[i].pkts-average.pkts)*(mas[i].pkts-average.pkts);
        stdev.bts       +=(mas[i].bts-average.bts)*(mas[i].bts-average.bts);
        stdev.srcmask   +=(mas[i].srcmask-average.srcmask)*(mas[i].srcmask-average.srcmask);
        stdev.dstmask   +=(mas[i].dstmask-average.dstmask)*(mas[i].dstmask-average.dstmask);
    }

    stdev.srcp      =round_m(sqrt(stdev.srcp/count_metric-1));
    stdev.dstp      =round_m(sqrt(stdev.dstp/count_metric-1));
    stdev.pkts      =round_m(sqrt(stdev.pkts/count_metric-1));
    stdev.bts       =round_m(sqrt (stdev.bts/count_metric-1));
    stdev.dstmask   =round_m(sqrt(stdev.dstmask/count_metric-1));
    stdev.srcmask   =round_m(sqrt(stdev.srcmask/count_metric-1));

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
