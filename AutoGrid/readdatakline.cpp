#include "readdatakline.h"

#include <QDebug>



ReadDataKLine::ReadDataKLine()
{

}


void ReadDataKLine::ReadData(QString str)
{
    pfile = new QFile(str);

    if( !pfile->open(QFile::ReadOnly) )
        return;

    if( nullptr == pfile)
        return;

    char    line[1024];
    char    *token;
    KLine temp;

    while( pfile->readLine(line,1024)  > 0 )
    {
        token = strtok( line, "'\t'" );
        if( token != NULL )
            temp.time = token;

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.openingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.highestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.lowestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.closeingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.amountOfIncrease = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalVolume = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalAmount = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.turnoverRate = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.volumeAmount = atof(token);


        if(temp.highestBid > m_highestBid)
            m_highestBid = temp.highestBid;
        if(temp.lowestBid < m_lowestBid)
            m_lowestBid = temp.lowestBid;

        if(temp.totalVolume > m_totalVolume)
            m_totalVolume = temp.totalVolume;

        m_kline.push_back(temp);


        //qDebug("%f",temp.openingPrice);
    }
}
