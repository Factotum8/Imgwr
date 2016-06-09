#include "main.h"


int main (){

    QFile fileIn("flow"),fileOut("IMG");

    if (!fileIn.open(QIODevice::ReadOnly)) {
        cout<<"Not faund file In\n";
        return 0;
    }
    QStringList str,list;

    QRegExp rx("\\d+");

    while (!fileIn.atEnd()){

        QByteArray  line = fileIn.readLine();

        str<<line;
        /*
        QString str  = line.data();
        str.contains("[0-9]");//("(\\d+)");
        cout << str;
       //  QStringList str= line.data();
       //        str.filter([0-9]);*/
    }
    //cout<<str.at(3).toStdString()<<"\n";
    list= str.filter(rx);//"[0-9]+");
    QStringList abc;
    for (int i=0; i< list.size(); i++){
        QRegExp xr("(\\d+)");
        int pos=0;
        cout<<list.at(i).toStdString()<<"\n";
        // = list.at(i);

        while ((pos = rx.indexIn(list.at(i), pos)) != -1) {
                  abc<<xr.cap(1);
                  pos += rx.matchedLength();
        }

    }

    cout<<"ABC\n"<<abc.at(1).toStdString()<<"\n";

   /* QString st = list.last();
    cout<<st.toStdString()<<"\n";
    st= list.first();
    cout<<st.toStdString()<<"\n";
   //cout<<(QString)list.last()<<(QString)list.first();*/
    return 0;
}
