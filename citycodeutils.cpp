#include "citycodeutils.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

CityCodeUtils::CityCodeUtils() {

}

QString CityCodeUtils::getCityCodeFromName(QString cityName)
{

    if(cityMap.isEmpty()){
        initCityMap();
    }

    QMap<QString,QString>::Iterator it = cityMap.find(cityName);
    if(it == cityMap.end()){
        return "";
    }
    return it.value();

}

void CityCodeUtils::initCityMap()
{
    QFile file(":/city.json");
    file.open(QIODevice::ReadOnly);
    QByteArray rawData = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if(jsonDoc.isArray()){
        QJsonArray citys = jsonDoc.array();
        for(QJsonValue value : citys){
            if(value.isObject()){
                QString cityName = value["cityName"].toString();
                QString cityCode = value["cityCode"].toString();
                cityMap.insert(cityName,cityCode);
            }
        }
    }

}
