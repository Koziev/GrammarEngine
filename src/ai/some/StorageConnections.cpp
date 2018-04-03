// 14.01.2011 - добавлен метод Ping, позволяющий периодически дергать подключенные сервера,
//              не позволяя им закрывать коннекты.
// 17.01.2011 - добавлены AttachThread и DetachThread.

#include <lem/oformatter.h>
#include <lem/conversions.h>
#include <lem/solarix/StorageConnections.h>

#include <lem/solarix/StorageConnection_SQLITE.h>

#if defined SOL_MYSQL_DICTIONARY_STORAGE
#include <lem/Solarix/StorageConnection_MySQL.h>
#endif

#if defined SOL_FIREBIRD_DICTIONARY_STORAGE
#include <lem/Solarix/StorageConnection_FireBird.h>
#endif

using namespace Solarix;


StorageConnections::StorageConnections()
{
}

StorageConnections::~StorageConnections()
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif
    return;
}


StorageConnection* StorageConnections::Connect(
    const lem::UFString &provider,
    const lem::UFString &connection_string
)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    for (lem::Container::size_type i = 0; i < cnx_provider.size(); ++i)
    {
        if (cnx_provider[i].eqi(provider) && cnx_string[i] == connection_string)
        {
            cnx[i]->AddRef();
            return cnx[i];
        }
    }

    StorageConnection *new_cnx = CreateConnection(provider, connection_string);
    new_cnx->AddRef();
    cnx.push_back(new_cnx);
    cnx_provider.push_back(provider);
    cnx_string.push_back(connection_string);
    return new_cnx;
}


void StorageConnections::Disconnect(StorageConnection* connection)
{
#if defined LEM_THREADS
    lem::Process::CritSecLocker lock(&cs);
#endif

    // Если соединение больше никем не используется
    if (connection->Release() == 0)
    {
        // то удаляем его
        for (lem::Container::size_type i = 0; i < cnx.size(); ++i)
        {
            if (cnx[i] == connection)
            {
                cnx.Remove(i);
                cnx_provider.Remove(i);
                cnx_string.Remove(i);
                return;
            }
        }

        LEM_STOPIT;
    }

    return;
}

StorageConnection* StorageConnections::CreateConnection(
    const lem::UFString &provider,
    const lem::UFString &connection_string
)
{
    if (provider.eqi(L"SQLite"))
    {
        return new StorageConnection_SQLITE(connection_string);
    }


    lem::FString login;
    lem::FString psw;
    lem::FString db;
    lem::FString host;
    int port = -1;
    int pool_size = 1;

    lem::Collect<lem::UFString> params, params2;
    lem::parse(connection_string, params, L";");
    for (lem::Container::size_type i = 0; i < params.size(); ++i)
    {
        lem::UFString p(params[i]);
        p.trim();
        params2.clear();
        lem::parse(p, params2, L"=");
        if (params2.size() != 2)
        {
            lem::MemFormatter mem;
            mem.printf("Invalid connection string %us: parameter %us", connection_string.c_str(), p.c_str());
            throw lem::E_BaseException(mem.string());
        }

        if (params2.front().eqi(L"login"))
            login = lem::to_utf8(params2[1]);
        else if (params2.front().eqi(L"psw"))
            psw = lem::to_utf8(params2[1]);
        else if (params2.front().eqi(L"db"))
            db = lem::to_utf8(params2[1]);
        else if (params2.front().eqi(L"host"))
            host = lem::to_utf8(params2[1]);
        else if (params2.front().eqi(L"port"))
            port = lem::to_int(params2[1]);
        else if (params2.front().eqi(L"pool_size"))
            pool_size = lem::to_int(params2[1]);
    }

    login.re_clear();
    psw.re_clear();
    db.re_clear();
    host.re_clear();

#if defined SOL_MYSQL_DICTIONARY_STORAGE
    if (provider.eqi(L"MySQL"))
    {
        if (port == -1)
            port = 3306;

        return new StorageConnection_MySQL(login, psw, db, host, port, pool_size);
    }
#endif

#if defined SOL_FIREBIRD_DICTIONARY_STORAGE
    if (provider.eqi(L"FireBird"))
    {
        return new StorageConnection_FireBird(login, psw, db);
    }
#endif

    lem::MemFormatter msg;
    msg.printf("Can not find connection provider for %us %us", provider.c_str(), connection_string.c_str());
    throw lem::E_BaseException(msg.string());
}


// Если нужно периодически пинговать удаленный сервер, чтобы он не обрубил
// соединение по таймауту неактивности клиента.
void StorageConnections::Ping()
{
    for (auto c : cnx)
    {
        c->Ping();
    }

    return;
}
