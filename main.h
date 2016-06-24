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

//#include <QFileDialog>
using namespace std;
//using std::cout;
//using std::cin;

void normalization (long int *mas          );
void stan_deviat   (long int *mas          );
void init_mas      (long int *mas,QStringList *pnumb);
void regexp_str    (                  );
void regexp_numb   (QStringList *pnumb);
void zcontribution (long int *mas          );
long double Infbit (                  );

#endif // MAIN_H
