#ifndef WIDGET_H
#define WIDGET_H

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

#include <QMenu>
#include <QNetworkReply>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QLabel>
#include "citycodeutils.h"
#include "day.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Day days[7];
    QList<QLabel *> mDateList;
    QList<QLabel *> mWeekList;
    QList<QLabel *> mIconList;
    QList<QLabel *> mWeaTypeList;
    QList<QLabel *> mAirqList;
    QList<QLabel *> mFxList;
    QList<QLabel *> mFlList;

    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
public slots:
    void readHttpReply(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();

    void on_lineEditCity_returnPressed();

private:
    Ui::Widget *ui;
    QMenu *menuQuit;
    QPoint mOffset;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QString strUrl;
    CityCodeUtils cityCodeUtils;
    QMap<QString,QString> mTypeMap;
    void parseWeatherJsonData(QByteArray rawData);
    void parseWeatherJsonDataNew(QByteArray rawData);
    void updateUI();
    void drawTempLineHigh();
    void drawTempLineLow();

};
#endif // WIDGET_H
