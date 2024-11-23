#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPainter>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // this->setLayout(ui->verticalLayout);
    this->setFixedSize(875,472);
    setWindowFlag(Qt::FramelessWindowHint);
    //新建一个菜单组件
    menuQuit = new QMenu(this);

    menuQuit->setStyleSheet("QMenu::item {color:white}");
    //为菜单组件添加一个动作
    QAction *openAct = new QAction(QIcon(":/res/close.png"), tr("close"), this);
    menuQuit->addAction(openAct);
    //用户选择菜单项并点击后回调函数,退出程序
    connect(menuQuit,&QMenu::triggered,this,[=]{
        this->close();
    });
    ///由QNetworkAccessManager发起get请求
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,[](){
        // qDebug() << "manager finish!";

    });
    //指定请求的url地址

    // QUrl urlItBoy("http://t.weather.itboy.net");
    // QUrl urlTianQi("http://gfeljm.tianqiapi.com/api?unescape=1&version=v62&appid=42655488&appsecret=fmL5uHM8");
    strUrl = "http://gfeljm.tianqiapi.com/api?unescape=1&version=v9&appid=42655488&appsecret=fmL5uHM8";
    QUrl urlTianQi(strUrl);
    // QNetworkRequest resI(urlItBoy);
    // QNetworkRequest res(urlTianQi);
    QNetworkRequest res(urlTianQi);
    reply = manager->get(res);
    //QNetworkRequest网络请求后进行数据读取
    connect(manager,&QNetworkAccessManager::finished,this,&Widget::readHttpReply);

    mWeekList << ui->labelDate0 << ui->labelDate1 << ui->labelDate2 << ui->labelDate3
              << ui->labelDate4 << ui->labelDate5 << ui->labelDate6;
    mDateList << ui->labelDate00 << ui->labelDate11 << ui->labelDate22 << ui->labelDate33
              << ui->labelDate44 << ui->labelDate55 << ui->labelDate66;
    mIconList << ui->labelWeatherIcon0 << ui->labelWeatherIcon1 << ui->labelWeatherIcon2 << ui->labelWeatherIcon3
              << ui->labelWeatherIcon4 << ui->labelWeatherIcon5 << ui->labelWeatherIcon6;
    mWeaTypeList << ui->lbWeatherTypeDate0 << ui->lbWeatherTypeDate1 << ui->lbWeatherTypeDate2 << ui->lbWeatherTypeDate3
                 << ui->lbWeatherTypeDate4 << ui->lbWeatherTypeDate5 << ui->lbWeatherTypeDate6;
    mAirqList << ui->labelairq0 << ui->labelairq1 << ui->labelairq2<< ui->labelairq3
              << ui->labelairq4 << ui->labelairq5 << ui->labelairq6;
    mFxList << ui->labelFX0 << ui->labelFX1 << ui->labelFX2 << ui->labelFX3
            << ui->labelFX4 << ui->labelFX5 << ui->labelFX6;
    mFlList << ui->labelFL0 << ui->labelFL1 << ui->labelFL2 << ui->labelFL3
            << ui->labelFL4 << ui->labelFL5 << ui->labelFL6 ;

    //根据keys,设置icon的路径
    // mTypeMap.insert("暴雪",":/res/type/BaoXue.png");
    mTypeMap.insert("暴雨",":/res/baoyu.png");

    // mTypeMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    mTypeMap.insert("大暴雨",":/res/dabaoyu.png");
    mTypeMap.insert("大风转晴",":/res/dafeng_qing.png");
    // mTypeMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    // mTypeMap.insert("大到暴雪",":/res/type/DaDaoBaoXue.png");
    mTypeMap.insert("大雪",":/res/daxue.png");
    mTypeMap.insert("大雨",":/res/dayu.png");
    // mTypeMap.insert("冻雨",":/res/type/DongYu.png");
    mTypeMap.insert("多云",":/res/duoyun.png");
    // mTypeMap.insert("浮沉",":/res/type/Fuchen.png");
    mTypeMap.insert("多云转晴",":/res/duoyun_qing.png");
    mTypeMap.insert("多云转小雨",":/res/xiaoyu.png");
    mTypeMap.insert("风",":/res/feng.png");
    mTypeMap.insert("雷阵雨",":/res/leizhenyu.png");
    // mTypeMap.insert("雷阵雨伴有冰",":/res/type/LeiZhenYuBanYouBingBao.png");
    mTypeMap.insert("霾",":/res/mai.png");
    // mTypeMap.insert("强沙尘暴",":/res/type/QiangShaChenBao.png");
    mTypeMap.insert("晴",":/res/qing.png");
    mTypeMap.insert("晴转大风",":/res/qing_dafeng.png");
    mTypeMap.insert("晴转多云",":/res/qing_duoyun.png");
    mTypeMap.insert("晴转雪",":/res/qing_xue.png");
    mTypeMap.insert("晴转阴",":/res/qing_yin.png");
    mTypeMap.insert("晴转雨",":/res/qing_yu.png");
    mTypeMap.insert("晴转雨夹雪",":/res/qing_yujiaxue.png");
    mTypeMap.insert("沙尘暴",":/res/shachenbao.png");
    mTypeMap.insert("特大暴雨",":/res/tedabaoyu.png");
    mTypeMap.insert("undefined",":/res/undefined.png");
    mTypeMap.insert("雾",":/res/wu.png");
    // mTypeMap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");
    mTypeMap.insert("小到中雨",":/res/yu.png");
    mTypeMap.insert("小雪",":/res/xiaoxue.png");
    mTypeMap.insert("小雨",":/res/xiaoyu.png");
    mTypeMap.insert("小到中雨转小雨",":/res/xiaoyu.png");
    mTypeMap.insert("小雨转晴",":/res/qing.png");
    mTypeMap.insert("雪",":/res/xue.png");
    mTypeMap.insert("雪转晴",":/res/xue_qing.png");
    // mTypeMap.insert("扬沙",":/res/type/YangSha.png");
    mTypeMap.insert("阴转晴",":/res/yin_qing.png");
    mTypeMap.insert("阴",":/res/yintian.png");
    mTypeMap.insert("雨",":/res/yu.png");
    mTypeMap.insert("小雨转小到中雨",":/res/yu.png");
    mTypeMap.insert("雨转晴",":/res/yu_qing.png");
    mTypeMap.insert("雨夹雪",":/res/yujiaxue.png");
    // mTypeMap.insert("阵雪",":/res/type/ZhenXue.png");
    // mTypeMap.insert("阵雨",":/res/type/ZhenYu.png");
    // mTypeMap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    mTypeMap.insert("中到大雨",":/res/dayu.png");
    // mTypeMap.insert("中雪",":/res/type/ZhongXue.png");
    mTypeMap.insert("中雨",":/res/yu.png");

    ui->widget0404->installEventFilter(this);
    ui->widget0405->installEventFilter(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        //qDebug() << "right Mouse Clicked!";
        menuQuit->exec(QCursor::pos());
    }
    //鼠标当前位置event->globaLPos（);,
    //窗口当前位置this->pos（)窗口新位置event->globalPos（）-mOffset
    if(event->button() == Qt::LeftButton){
        mOffset = event->globalPos() - this->pos();
    }
}

//鼠标左键按下后的移动,导致这个事件被调用,设置窗口的新位置
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - mOffset);
}

bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widget0404 && event->type() == QEvent::Paint){
        drawTempLineHigh();
        return true;
    }
    if(watched == ui->widget0405 && event->type() == QEvent::Paint){
        drawTempLineLow();
    }
    return QWidget::eventFilter(watched,event);
}

void Widget::parseWeatherJsonData(QByteArray rawData){
    QJsonDocument jsonObj = QJsonDocument::fromJson(rawData);
    if(!jsonObj.isNull() && jsonObj.isObject()){
        QJsonObject objRoot = jsonObj.object();
        //解析日期
        QString date = objRoot["date"].toString();
        QString week = objRoot["week"].toString();
        ui->labelCurrentDate->setText(date + "  " + week);

        ui->labelWeatherIcon->setPixmap(mTypeMap[objRoot["wea"].toString()]);

        //解析城市名称
        QString city = objRoot["city"].toString();
        ui->labelCity->setText(city + "市");
        //解析天气类型
        QString wea = objRoot["wea"].toString();
        ui->labelweatherType->setText(wea);
        //解析当前温度
        QString currentTem = objRoot["tem"].toString();
        ui->labelTmp->setText(currentTem + "℃");
        ui->labelTempRange->setText(objRoot["tem2"].toString() + "~" + objRoot["tem1"].toString());
        //感冒指数
        ui->labelGanmao->setText("感冒指数：" + objRoot["air_tips"].toString());
        //风向
        QString win = objRoot["win"].toString();
        ui->labelFXType->setText(win);
        //风速
        QString winSpeed = objRoot["win_speed"].toString();
        ui->labelFL->setText(winSpeed);
        //PM2.5
        QString pm25Data = objRoot["air_pm25"].toString();
        ui->labelPM25Data->setText(pm25Data);
        //湿度
        QString shiduData = objRoot["humidity"].toString();
        ui->labelShiduData->setText(shiduData);
        //空气质量
        QString airLevelData = objRoot["air_level"].toString();
        ui->labelAirqData->setText(airLevelData);
    }
}

void Widget::parseWeatherJsonDataNew(QByteArray rawData)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
    if(!jsonDoc.isNull() && jsonDoc.isObject()){
        QJsonObject jsonRoot = jsonDoc.object();
        days[0].mCity = jsonRoot["city"].toString();
        //方式1
        // QJsonObject jsonAqi = jsonRoot["aqi"].toObject();
        // days[0].mTips = jsonAqi["air_tips"].toString();
        // days[0].mPm25 = jsonAqi["pm25"].toString();
        //方式2
        days[0].mTips = jsonRoot["aqi"].toObject()["air_tips"].toString();
        days[0].mPm25 = jsonRoot["aqi"].toObject()["pm25"].toString();
        if(jsonRoot.contains("data") && jsonRoot["data"].isArray()){
            QJsonArray weaArray = jsonRoot["data"].toArray();
            for(int i = 0; i < weaArray.size(); i++){
                QJsonObject obj = weaArray[i].toObject();
                // qDebug() << obj["date"].toString() << obj["wea"].toString();
                days[i].mDate = obj["date"].toString();
                days[i].mWeek = obj["week"].toString();
                days[i].mWeaType = obj["wea"].toString();
                days[i].mTemp = obj["tem"].toString();
                days[i].mTempLow = obj["tem2"].toString();
                days[i].mTempHigh = obj["tem1"].toString();
                days[i].mTips = obj["index"].toArray()[3].toObject()["desc"].toString();
                days[i].mFx = obj["win"].toArray()[0].toString();
                days[i].mFl = obj["win_speed"].toString();
                days[i].mShiDu = obj["humidity"].toString();
                days[i].mAirq = obj["air_level"].toString();
            }
        }
    }
    updateUI();
}

void Widget::updateUI()
{
    QPixmap pixmap;
    //解析日期
    ui->labelCurrentDate->setText(days[0].mDate + "  " + days[0].mWeek);

    ui->labelWeatherIcon->setPixmap(mTypeMap[days[0].mWeaType]);

    //解析城市名称
    ui->labelCity->setText(days[0].mCity + "市");
    //解析天气类型
    ui->labelweatherType->setText(days[0].mWeaType);
    //解析当前温度
    ui->labelTmp->setText(days[0].mTemp + "℃");
    ui->labelTempRange->setText(days[0].mTempLow + "~" + days[0].mTempHigh + "℃");
    //感冒指数
    ui->labelGanmao->setText("穿衣指数：" + days[0].mTips);
    //风向
    ui->labelFXType->setText(days[0].mFx);
    //风速
    ui->labelFL->setText(days[0].mFl);
    //PM2.5
    ui->labelPM25Data->setText(days[0].mPm25);
    //湿度
    ui->labelShiduData->setText(days[0].mShiDu);
    //空气质量
    // QString airLevelData = objRoot["air_level"].toString();
    ui->labelAirqData->setText(days[0].mAirq);
    //七天数据
    for(int i = 0; i < 7; i++){
        QStringList daylist = days[i].mDate.split("-");
        mWeekList[i]->setText(days[i].mWeek);
        mWeekList[0]->setText("今天");
        mDateList[i]->setText(daylist.at(1) + "-" + daylist.at(2));
        //缩放图片大小和label大小能匹配
        int index = days[i].mWeaType.indexOf("转");
        if(index != -1){
            pixmap = mTypeMap[days[i].mWeaType.left(index)];
        }else{
            pixmap = mTypeMap[days[i].mWeaType];
        }
        pixmap = pixmap.scaled(mIconList[i]->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        mIconList[i]->setPixmap(pixmap);
        index= days[i].mWeaType.indexOf("转");
        if(index != -1){
            mWeaTypeList[i]->setText(days[i].mWeaType.left(index));
        }else{
            mWeaTypeList[i]->setText(days[i].mWeaType);
        }
        QString aqi = days[i].mAirq;
        mAirqList[i]->setText(aqi);
        if(aqi == "优"){
            mAirqList[i]->setStyleSheet("background-color: rgb(50, 175, 89);color: rgb(255, 255, 255);border-radius: 8px;");
        }
        if(aqi == "良"){
            mAirqList[i]->setStyleSheet("background-color: rgb(251, 180, 46);color: rgb(255, 255, 255);border-radius: 8px;");
        }
        if(aqi == "轻度污染"){
            mAirqList[i]->setStyleSheet("background-color: rgb(235, 95, 35);color: rgb(255, 255, 255);border-radius: 8px;");
        }
        if(aqi == "中度污染"){
            mAirqList[i]->setStyleSheet("background-color: rgb(201, 53, 64);color: rgb(255, 255, 255);border-radius: 8px;");
        }
        if(aqi == "重度污染"){
            mAirqList[i]->setStyleSheet("background-color: rgb(133, 22, 142);color: rgb(255, 255, 255);border-radius: 8px;");
        }


        mFxList[i]->setText(days[i].mFx);
        index= days[i].mFl.indexOf("转");
        if(index != -1){
            mFlList[i]->setText(days[i].mFl.left(index));
        }else{
            mFlList[i]->setText(days[i].mFl);
        }

    }



    update();
}

void Widget::drawTempLineHigh()
{
    QPainter painter(ui->widget0404);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(Qt::yellow);
    painter.setPen(Qt::yellow);

    int ave;
    int sum = 0;
    int offset = 0;
    int middle = ui->widget0404->height()/2;
    for(int i = 0; i < 7; i++){
        sum += days[i].mTempHigh.toInt();
    }
    ave = sum/7;

    QPoint points[7];
    for(int i = 0; i < 7; i++){
        points[i].setX(mAirqList[i]->x() + mAirqList[i]->width()/2);
        offset = days[i].mTempHigh.toInt() - ave;
        points[i].setY(middle - offset);
        //画出7个点
        painter.drawEllipse(QPoint(points[i]),3,3);
        //画出当天温度
        painter.drawText(points[i].x() - 5,points[i].y() - 10,days[i].mTempHigh + "°");
    }

    for(int i = 0; i < 6; i++){
        painter.drawLine(points[i],points[i+1]);
    }

}

void Widget::drawTempLineLow()
{
    QPainter painter(ui->widget0405);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(QColor(68, 225, 244));
    painter.setPen(QColor(68, 225, 244));

    int ave;
    int sum = 0;
    int offset = 0;
    int middle = ui->widget0405->height()/2;
    for(int i = 0; i < 7; i++){
        sum += days[i].mTempLow.toInt();
    }
    ave = sum/7;

    QPoint points[7];
    for(int i = 0; i < 7; i++){
        points[i].setX(mAirqList[i]->x() + mAirqList[i]->width()/2);
        offset = days[i].mTempLow.toInt() - ave;
        points[i].setY(middle - offset);
        //画出7个点
        painter.drawEllipse(QPoint(points[i]),3,3);
        //画出当天温度
        painter.drawText(points[i].x() - 5,points[i].y() - 10,days[i].mTempLow + "°");
    }

    for(int i = 0; i < 6; i++){
        painter.drawLine(points[i],points[i+1]);
    }
}


void Widget::readHttpReply(QNetworkReply *reply)
{
    int resCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << resCode;
    if(reply->error() == QNetworkReply::NoError && resCode == 200){
        //大多数服务器返回的字符编码格式是utf-8
        QByteArray data = reply->readAll();
        parseWeatherJsonDataNew(data);
        qDebug() << QString::fromUtf8(data);
    }else{
        //qDebug() << reply->errorString();
        QMessageBox::warning(this,"错误","网络请求失败",QMessageBox::Ok);

        // QMessageBox mes;
        // mes.setWindowTitle("错误");
        // mes.setText("网络请求失败");
        // mes.setStyleSheet("QPushButton {color:red}");
        // mes.setStandardButtons(QMessageBox::Ok);
        // mes.exec();

    }

}

// QString getCityCodeFromName(QString name){
//     QFile file(":/city.json");
//     file.open(QIODevice::ReadOnly);
//     QByteArray rawData = file.readAll();
//     file.close();

//     QJsonDocument jsonDoc = QJsonDocument::fromJson(rawData);
//     if(jsonDoc.isArray()){
//         QJsonArray citys = jsonDoc.array();
//         for(QJsonValue value : citys){
//             if(value.isObject()){
//                 QString cityName = value["cityName"].toString();
//                 if(cityName == name){
//                     return value["cityCode"].toString();
//                 }
//             }
//         }
//         return "";
//     }
// }

void Widget::on_pushButton_clicked()
{
    QString cityNameFromUser = ui->lineEditCity->text();
    QString cityCode = cityCodeUtils.getCityCodeFromName(cityNameFromUser);

    if(cityCode != NULL){
        //指定请求的url地址
        strUrl += "&cityid="+ cityCode;
        qDebug() << strUrl;
        manager->get(QNetworkRequest(QUrl(strUrl)));
        // //QNetworkRequest网络请求后进行数据读取
        // connect(manager,&QNetworkAccessManager::finished,this,&Widget::readHttpReply);
    }else{
        QMessageBox::warning(this,"错误","请输入正确的城市名",QMessageBox::Ok);
    }

}


void Widget::on_lineEditCity_returnPressed()
{
    on_pushButton_clicked();
}

