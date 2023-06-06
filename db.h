#ifndef DB_H
#define DB_H

#include <QString>
#include <QVariant>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QByteArray>


class Db;

class DbDestroyer
{
private:
    Db * p_instance;
public:
    ~DbDestroyer() { if (p_instance!=nullptr) delete p_instance;}
    void initialize(Db * p){p_instance = p;}
};


class Db
{
 private:
    static Db * p_instance;
    static DbDestroyer destroyer;
    static QSqlDatabase db;
protected:
    Db()
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("/db/ex");


        if(!db.open())
            qDebug()<<db.lastError().text();
    }
    Db(const Db& )=delete;
    Db& operator = (Db &)=delete;
    ~Db()
    {db.close();}
    friend class DbDestroyer;
public:
    static Db* getInstance(){
        if (!p_instance)
        {
            p_instance = new Db();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }


     QByteArray start_game(QString log, int desc){
         QSqlQuery query;
         query.prepare("SELECT * FROM user where log = :login" );
         query.bindValue(":login", log);
         query.exec();
         if (query.next()){
             return "start_false\n";
         }
         else{
             qDebug()<<log;
             query.prepare("INSERT INTO user (log, stat, now_row, now_col, soc_desc) VALUES (:login, 0, 0, 0, :desc)");
             query.bindValue(":login", log);
             query.bindValue(":desc", desc);
             query.exec();
             return "start_true\n";
         }
     }
     float solve (int x, int y){
         return (x+y)/(x * y);
     }

     bool my_function(int row1, int col1, int row2, int col2){
         if (solve(row1, col1) > solve(row2, col2)){
             return true;
         }
     }
     QByteArray move(QString row, QString col, int desc){
        QSqlQuery query;
        int row_int = row.toInt();
        int col_int = col.toInt();
        query.prepare("UPDATE user SET now_row=:row, now_col=:col WHERE soc_desc=:desc");
        query.bindValue(":row", row_int);
        query.bindValue(":col", col_int);
        query.bindValue(":desc", desc);
        query.exec();
        query.prepare("SELECT * FROM user WHERE soc_desc!=:desc");
        query.bindValue(":desc", desc);
        query.exec();
        query.first();
        if (query.first()){
            QString emeny = query.value(0).toString();
            qDebug() << emeny;

            query.prepare("SELECT now_row from user WHERE log=:login");
            query.bindValue(":login", emeny);
            query.exec();
            query.first();
            int row_enemy = query.value(0).toInt();
            qDebug() << row_enemy;

            query.prepare("SELECT now_col from user WHERE log=:login");
            query.bindValue(":login", emeny);
            query.exec();
            query.first();
            int col_enemy = query.value(0).toInt();
            qDebug() << col_enemy;

            bool match = my_function(row_int, col_int, row_enemy, col_enemy);
            if (match){
                query.prepare("update user SET stat=stat+1 where soc_desc=:desc");
                query.bindValue(":desc", desc);
                query.exec();
                return "First win!";
            }
            else{
                query.prepare("update user SET stat=stat+1 where soc_desc!=:desc"); // login
                query.bindValue(":desc", desc);
                query.exec();
                return "Second win!";
            }

                   }
        return "Соперник не пошёл";
     }

     QByteArray stop_game(int desc){
         QSqlQuery query;
         query.prepare("DELETE FROM user where soc_desc=:desciprtion");
         query.bindValue(":desciprtion", desc);
         query.exec();

         query.clear();
         return "true";
     }

     QByteArray check_stat(int desc){
         QSqlQuery query;
         query.prepare("SELECT stat FROM user WHERE soc_desc=:soc_desc");
         query.bindValue(":soc_desc", desc);
         query.exec();
         query.first();
        int stat_first = query.value(0).toInt();
         query.prepare("SELECT stat FROM user WHERE soc_desc!=:soc_desc");
         query.bindValue(":soc_desc", desc);
         query.exec();
         query.first();
         int stat_second = query.value(0).toInt();
         return "У вас " + QString::number(stat_first).toUtf8()+ ";" + "\r\n" + " У вашего опонента " + QString::number(stat_second).toUtf8();
     }
};


#endif

