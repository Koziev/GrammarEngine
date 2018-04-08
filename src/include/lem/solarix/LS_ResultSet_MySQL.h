#if !defined LS_ResultSet_MySQL__H && defined SOL_MYSQL_DICTIONARY_STORAGE
#define LS_ResultSet_MySQL__H

#include <lem/mysql_helpers.h>
#include <lem/process.h>
#include <lem/containers.h>
#include <lem/solarix/LS_ResultSet.h>

namespace Solarix
{
    struct MySQLCnx;

    class LS_ResultSet_MySQL : public LS_ResultSet
    {
    private:
        MySQLCnx *cnx;
        MYSQL_RES *stmt;
        MYSQL_ROW row;

    public:
        LS_ResultSet_MySQL(MySQLCnx *_cnx, MYSQL_RES *h, TransactionGuard *tx);
        virtual ~LS_ResultSet_MySQL();
        virtual bool Fetch();
        virtual int GetInt(int FieldIndex);
        virtual lem::UCString GetUCString(int FieldIndex);
        virtual lem::UFString GetUFString(int FieldIndex);
        virtual lem::FString GetFString(int FieldIndex);
    };
}

#endif
