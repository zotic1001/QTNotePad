#include "note.h"

Note::Note(
    QString name,
    QString author,
    QDateTime create_time,
    QString text,
    QStringList tags)
{
    this->id = 0;
    this->name = name;
    this->author = author;
    this->create_time = create_time;
    this->text = text;
    this->tags = tags;
}

Note::Note()
{
    this->id = 0;
    this->name = "";
    this->author = "";
    this->create_time = QDateTime();
    this->text = "";
    this->tags = QStringList();
}
bool Note::Serialize(QSqlQuery& query) {
    query.prepare("INSERT INTO data (name, author, create_time, text, tags) values (?, ?, ?, ?, ?)");
    query.addBindValue(this->name);
    query.addBindValue(this->author);
    query.addBindValue(this->create_time.toString());
    query.addBindValue(this->text);
    query.addBindValue(this->tags);
    if (!query.exec()) {
      return false;
    }
    return true;
}
bool Note::Update(QSqlQuery& query, int id) {
    query.prepare("UPDATE data SET create_time=?, text=?, tags=? WHERE id=?");
    query.addBindValue(create_time.toString());
    query.addBindValue(text);
    query.addBindValue(tags);
    query.addBindValue(id);
    if (!query.exec()) {
      return false;
    }
    return true;
};
