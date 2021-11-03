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
            qDebug()<< "Full Time" << line->sliced(posFullTimeBegin+6,(posFullTimeEnd-posFullTimeBegin-1-6))
                    << posFullTimeBegin << posFullTimeEnd;
            qint32 posTempEnd = line->indexOf("°",posFullTimeEnd);
            qint32 posTempBegin = line->indexOf(">",posTempEnd-4); //F in range 0...999. \todo - negative range
            if (posTempBegin>0){
                qDebug()<< "Temp in F" << line->sliced(posTempBegin+1,(posTempEnd-posTempBegin-1))
                        << posTempBegin << posTempEnd;
                qint32 posWindEnd = line->indexOf("mph",posTempEnd);
                qint32 posWindBegin = line->indexOf(">",posWindEnd-15); //mph, some <!-- --> before
                if (posTempBegin>0){
                    qDebug()<< "Wind in mph" << line->sliced(posWindBegin+1,(posWindEnd-posWindBegin-2))
                            << posWindBegin << posWindEnd;
                    qint32 posTempFeelEnd = line->indexOf("°",posWindEnd);
                    qint32 posTempFeelBegin = line->indexOf(">",posTempFeelEnd-4); //F in range 0...999. \todo - negative range
                    if (posTempFeelBegin>0){
                        qDebug()<< "Temp feel in F" << line->sliced(posTempFeelBegin+1,(posTempFeelEnd-posTempFeelBegin-1))
                                << posTempFeelBegin << posTempFeelEnd;
                        qint32 posHumidityEnd = line->indexOf("%",posTempFeelEnd);
                        qint32 posHumidityBegin = line->indexOf(">",posHumidityEnd-3); //% in range 0..99
                        if (posHumidityBegin>0){
                            qDebug()<< "Humidity in %" << line->sliced(posHumidityBegin+1,(posHumidityEnd-posHumidityBegin-1))
                                    << posHumidityBegin << posHumidityEnd;
                        }//Humidity
                    }//Temperature/Feel as
                }//Wind
            }//Temperature
        }//if posFullTime
    }//if data from Kiev
}
