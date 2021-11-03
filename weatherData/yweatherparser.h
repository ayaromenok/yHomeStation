#ifndef YWEATHERPARSER_H
#define YWEATHERPARSER_H

#include <QObject>

class YWeatherParser : public QObject
{
    Q_OBJECT
public:
    explicit YWeatherParser(QObject *parent = nullptr);
    ~YWeatherParser();
    void getCurrentWeather();
signals:

private:
    void processLine(QString* line);
};

#endif // YWEATHERPARSER_H
