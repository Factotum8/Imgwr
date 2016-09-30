#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <QFile>
#include <stdio.h>
#include <QStringList>
#include <QString>
#include <math.h>

#include <QApplication>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <sstream>
//#include <cmath>
//#include <math.h>
#include <cmath>
#include <QFile>
#include <QTextStream>

//#include <QFileDialog>
using namespace std;
//using std::cout;
//using std::cin;


 int inptIn_stdev=0,outpIn_stdev,srcp_stdev=0,
               dstp_stdev=0,bts_stdev=0,pkts_stdev=0,
                 prot_stdev=0,srcmask_stdev=0,dstmask_stdev=0;

 int inptIn_average=0,outpIn_average,srcp_average=0,
               dstp_average=0,bts_average=0,pkts_average=0,
                prot_average=0,srcmask_average=0,dstmask_average=0;

int k=0;

QFile fileIn("flow"), fileOut("IMG");
QStringList filter,listv;



void stan_deviat   ( double *mas          );
void preprocesing  ( double *mas          );
void infile        ( double *mas          );
void init_mas      ( double *mas,QStringList *pnumb);
void regexp_str    (                      );
void regexp_numb   (QStringList *pnumb    );
void zcontribution (double *mas           );
long double Infbit (                      );


#endif // MAIN_H
