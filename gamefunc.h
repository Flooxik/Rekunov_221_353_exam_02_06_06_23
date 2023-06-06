#ifndef FUNCTIONFORGAME_H
#define FUNCTIONFORGAME_H

#include <QAbstractItemModel>
#include "db.h"
#include <QString>

QByteArray parsing (QString data_from_client,int desc);

QByteArray start_game(QString login, int desc);
QByteArray move(QString row, QString col, int desc);
QByteArray stop_game(int desc);
QByteArray check_stat(int desc);

#endif // FUNCTIONFORGAME_H
