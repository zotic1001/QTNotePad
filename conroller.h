#ifndef CONROLLER_H
#define CONROLLER_H
#include "note.h"
#include "mainwindow.h"
#include "searchwindow.h"

class NoteController
{
public:
    NoteController(
              QSqlDatabase db);
    NoteController() {};
    QSqlDatabase db;
    bool Serialize(Note& note, QSqlQuery& query);
    bool Update(Note& note, QSqlQuery& query, int id);
    bool Delete(Note& note, QSqlQuery& query, int id);
};

#endif // CONROLLER_H
