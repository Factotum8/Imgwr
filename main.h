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

//#include <QFileDialog>
using std::cout;
using std::cin;

void normalization (int *mas          );
void stan_deviat   (int *mas          );
void init_mas      (int *mas,QStringList *pnumb);
void regexp_str    (                  );
void regexp_numb   (QStringList *pnumb);
void zcontribution (int *mas          );

#endif // MAIN_H
