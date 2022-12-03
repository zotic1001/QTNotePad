#include "notecontroler.h"


NoteControler::NoteControler(QSqlDatabase& db)
{
    this->db = db;
}

bool NoteControler::Serialize(Note &note)
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("INSERT INTO data (name, author, create_time, text, tags) values (?, ?, ?, ?, ?)");
    query.addBindValue(note.name);
    query.addBindValue(note.author);
    query.addBindValue(note.create_time.toString());
    query.addBindValue(note.text);
    query.addBindValue(note.tags.join(" "));
    if (!query.exec()) {
      return false;
    }
    return true;
}

bool NoteControler::Update(Note &note, int id)
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("UPDATE data SET create_time=?, text=?, tags=? WHERE id=?");
    query.addBindValue(note.create_time.toString());
    query.addBindValue(note.text);
    query.addBindValue(note.tags.join(""));
    query.addBindValue(id);
    if (!query.exec()) {
      return false;
    }
    return true;
}

bool NoteControler::Delete(int id)
{
    QSqlQuery query = QSqlQuery(db);
    query.prepare("delete from data where id=?");
    query.addBindValue(id);
    if (!query.exec()) {
        return false;
    }
    return true;
}
