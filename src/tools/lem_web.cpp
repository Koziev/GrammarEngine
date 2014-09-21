#include <lem/config.h>

#if defined LEM_WINDOWS || defined LEM_DOT_NET
#include <windows.h>
#endif

#include <lem/system_config.h>
#include <lem/registry.h>
#include <lem/network.h>

using namespace lem;
using namespace lem::Network;

lem::FString lem::Network::Web::proxy;
lem::FString lem::Network::Web::locals;     
lem::FString lem::Network::Web::agent;
bool lem::Network::Web::init=false;


// Переопределение конфигурации прокси.
void Web::SetProxy( const FString &cfg )
{
 proxy = cfg;
 locals = "<local>";   
 init = true;
 return;
}


// ***************************************************************
// Инициализация дефолтными значениями (возможно - из реестра).
// ***************************************************************
void Web::Init(void)
{
 if( !init )
  {
   init = true;
   agent = "Mozilla/5.0 (Windows; U; Windows NT 5.1; ru; rv:1.8.1.18) Gecko/20081029 Firefox/2.0.0.18";// "MSIE 5.0";
 
   #if defined LEM_WINDOWS
  
   if( lem::System_Config::IsWin9x() )
    return;

   WinRegistry reg;
   reg.HKCU();

   if( reg.seek_subkey("Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings" ) )
    {
     bool proxy_enable = reg.get_bool( "ProxyEnable" );

     if( proxy_enable )
      {
       proxy = reg.get_string( "ProxyServer" ).c_str();
       locals = reg.get_string( "ProxyOverride" ).c_str();

       if( locals.empty() )
        {
         locals = "<local>";   
        }
      }
    }

   #endif 
  }

 return; 
}


// Выход в интернет через прокси-сервер?
bool Web::Proxy(void)
{
 Init();
 return proxy.empty()==false;
}

const lem::FString& Web::GetAgent(void)
{
 Init();
 return agent;
}

const lem::FString& Web::GetProxy(void)
{
 Init();
 return proxy;
}

const lem::FString& Web::GetLocals(void)
{
 Init();
 return locals;
}

