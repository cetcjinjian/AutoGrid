#ifndef READDATAKLINE_H
#define READDATAKLINE_H

#include <vector>
#include <QString>
#include <QFile>

typedef struct
{
    QString time;                   //时间
    double openingPrice;            //开盘
    double highestBid;              //最高
    double lowestBid;               //收盘
    double closeingPrice;           //涨幅
    double amountOfIncrease;        //振幅
    double totalVolume;             //总手
    double totalAmount;             //金额
    double turnoverRate;            //换手率
    double volumeAmount;            //成交次数
}KLine;

class ReadDataKLine
{
public:
    ReadDataKLine();
    void ReadData(QString str);
    std::vector<KLine> m_kline;


public:


    QString m_startTime;
    QString m_endTime;

    double m_highestBid = 0;
    double m_lowestBid = 10000;
    double m_totalVolume = 0;

    QFile* pfile = nullptr;

};

#endif // READDATAKLINE_H
