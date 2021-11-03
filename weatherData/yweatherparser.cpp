#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "yweatherparser.h"

YWeatherParser::YWeatherParser(QObject *parent)
    : QObject{parent}
{
    qDebug() << __FUNCTION__;
}

YWeatherParser::~YWeatherParser(){
    qDebug() << __FUNCTION__;
}

void
YWeatherParser::getCurrentWeather(){
    qDebug() << __FUNCTION__;
    QFile f;
    QString fName("../../data/tmp/3e3893af8a3ae9250e9d84a2992aa4b2358e98c6d9429876b3d5f7c832a9933b");

    f.setFileName(fName);
    if (f.exists()){
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&f);
        while (!in.atEnd()) {
            QString line = in.readLine();
            processLine(&line);
        }

    } else {
        qWarning() << "File not found" << fName;
    }
}

void
YWeatherParser::processLine(QString* line){
    //qDebug() << __FUNCTION__;
    if (line->indexOf("Kiev, Ukraine") > 0){
        qint32 posFullTimeBegin = line->indexOf("As of");
        qint32 posFullTimeEnd = line->indexOf("EET",posFullTimeBegin);
        if ((posFullTimeBegin>0) & (posFullTimeEnd>posFullTimeBegin)){
            qDebug()<< "Full Time" << line->sliced(posFullTimeBegin+6,(posFullTimeEnd-posFullTimeBegin-1-6)) << posFullTimeBegin << posFullTimeEnd;
        }
    }//if data from Kiev
}
