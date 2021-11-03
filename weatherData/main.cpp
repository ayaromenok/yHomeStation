#include <QCoreApplication>
#include "yweatherparser.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    YWeatherParser wp;
    wp.getCurrentWeather();

    return a.exec();
}
