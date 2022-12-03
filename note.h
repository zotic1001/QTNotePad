#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>
#include <QSqlQuery>

class Note
{
public:
    int id;
    QString name;
    QString author;
    QDateTime create_time;
    QString text;
    QStringList tags;
    Note(QString name,
         QString author,
         QDateTime create_time,
         QString text,
         QStringList tags);
    Note();
    bool Serialize(QSqlQuery& query);
    bool Update(QSqlQuery& query, int id);
};

#endif // NOTE_H
