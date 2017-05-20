#ifndef READDATA_H
#define READDATA_H



#include <QFile>
#include <QString>
#include <stdlib.h>
#include <QTextStream>


typedef struct
{
    int  Date;
    int  Time;
    char SecID[16];
    char SecName[32];
    long Deal;
    long Vol;
    long Amt;
}FSJL;

typedef struct
{
    double deal_Start;
    double deal_Max;
    double deal_Min;
    double vol_Max;
    double vol_Min;
    double deal_rate;
}INFO;


class ReadData
{
public:
    ReadData();
    ~ReadData();
    ReadData(char* SecID,char* Date);
    bool ReadFSJL();
    void GetFSJLINFO();
    FSJL fsjl[241];
    INFO info;
private:
    QFile*    file = nullptr;
    char szSecID[16];
    char szDate[20];

};

#endif // READDATA_H
