#include "db.h"

Db * Db::p_instance;
DbDestroyer Db::destroyer;
QSqlDatabase Db::db;
