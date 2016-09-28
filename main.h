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
#include <math.h>
#include <QFile>
#include <QTextStream>

//#include <QFileDialog>
using namespace std;
//using std::cout;
//using std::cin;


void stan_deviat   (long *mas          );
void  preprocesing (long *mas          );
void infile(long *mas);
void init_mas      (long *mas,QStringList *pnumb);
void regexp_str    (                  );
void regexp_numb   (QStringList *pnumb);
void zcontribution (long *mas          );
long double Infbit (                  );


#endif // MAIN_H
