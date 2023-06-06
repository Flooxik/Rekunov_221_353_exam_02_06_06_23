#include "gamefunc.h"


QByteArray start_game(QString login, int desc)
{
    return Db::getInstance()->start_game(login, desc);
}

QByteArray move(QString row, QString col, int desc){
    return Db::getInstance()->move(row, col, desc);
}

QByteArray stop_game(int desc){
    return Db::getInstance()->stop_game(desc);
}

QByteArray check_stat(int desc){
    return Db::getInstance()->check_stat(desc);
}
QByteArray parsing (QString data_from_client,int desc)
{
    if(data_from_client.contains('&'))
    {

        QStringList data_from_client_list = data_from_client.trimmed().split(QLatin1Char('&'));
        QString login, row, col;
        qDebug() << data_from_client_list;
        if(data_from_client_list.front() == "start_game"){
            data_from_client_list.pop_front();
            login = data_from_client_list.front();
            return start_game(login, desc);
        }else if(data_from_client_list.front()=="move"){
            data_from_client_list.pop_front();
            row = data_from_client_list.front();
            data_from_client_list.pop_front();
            col = data_from_client_list.front();
            return move(row, col, desc);
        }else if(data_from_client_list.front() == "stat"){
            data_from_client_list.pop_front();
            login = data_from_client_list.front();
            return check_stat(desc);
        }else if(data_from_client_list.front() == "stop_game"){
            return stop_game(desc);
        }
    }else{
        return data_from_client.toUtf8();
    }

}
