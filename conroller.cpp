#include "conroller.h"

NoteController::NoteController(
QSqlDatabase db)
{
    this->db = db;
}

bool NoteController::Serialize(Note &note, QSqlQuery &query)
{
    query.prepare("INSERT INTO data (name, author, create_time, text, tags) values (?, ?, ?, ?, ?)");
    query.addBindValue(note.name);
    query.addBindValue(note.author);
    query.addBindValue(note.create_time.toString());
    query.addBindValue(note.text);
    query.addBindValue(note.tags);
    if (!query.exec()) {
      return false;
    }
    return true;
}

bool NoteController::Update(Note &note, QSqlQuery &query, int id)
{
    query.prepare("UPDATE data SET create_time=?, text=?, tags=? WHERE id=?, name=?, author=?");
    query.addBindValue(note.create_time.toString());
    query.addBindValue(note.text);
    query.addBindValue(note.tags);
    query.addBindValue(id);
    query.addBindValue(note.name);
    query.addBindValue(note.author);
    if (!query.exec()) {
      return false;
    }
    return true;
}
