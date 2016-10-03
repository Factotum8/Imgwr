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
#include "funct.h"


using namespace std;




void stan_deviat   ( flow *mas          );
void preprocesing  ( flow *mas          );
void infile        ( flow *mas          );
void init_mas      ( flow *mas,QStringList *pnumb);
void regexp_str    (                      );
void regexp_numb   (QStringList *pnumb    );
void zcontribution (flow *mas           );
long double Infbit (                      );


#endif // MAIN_H
