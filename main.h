#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <cmath>
#include <math.h>

#include <QApplication>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QString>
#include <QTextStream>

#include "funct.h"



using namespace std;

void parsin_input       ( int argc, char **argv          );
void preprocesing       ( flow *mas                      );
void infile             ( flow *mas                      );
void init_mas           ( flow *mas, QStringList *pnumb  );
void regexp_str         (                                );
void regexp_numb        ( QStringList *pnumb             );
void zcontribution      ( flow *mas                      );
void setPixel           ( QImage *img, flow *values, int width, int height);

TYPEMETRIC norm_65535   ( TYPEMETRIC var                 );
TYPEMETRIC round_m      ( TYPEMETRIC var                 );


#endif // MAIN_H
