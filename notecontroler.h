#ifndef NOTECONTROLER_H
#define NOTECONTROLER_H

#include <note.h>
#include <qsqldatabase.h>



class NoteControler
{
public:
    NoteControler(QSqlDatabase& db);
    QSqlDatabase db;
    bool Serialize(Note& note);
    bool Update(Note& note, int id);
    bool Delete(int id);
};

#endif // NOTECONTROLER_H
