#ifndef COMPILATION_CONTEXT__H
#define COMPILATION_CONTEXT__H
#pragma once

 #include <lem/ucstring.h>
 #include <lem/noncopyable.h>
 #include <lem/ptr_container.h>

 namespace Solarix
 {

  class DeclaredVar : lem::NonCopyable
  {
   private:
    lem::UCString name;
    int id;
    
   public:
    DeclaredVar( const lem::UCString &Name, int Id ) : name(Name), id(Id) {}

    const lem::UCString & GetName(void) const { return name; }
    int GetId(void) const { return id; }
  };  

  class CompilationContext : lem::NonCopyable
  {
   private:
    const CompilationContext *parent;
    lem::Ptr_NC_Collect<DeclaredVar> vars;
    static int id_seq;

   public:
    CompilationContext(void) { parent=NULL; }
    CompilationContext( const CompilationContext *Parent ) : parent(Parent) {}
   
    bool FindVar( const lem::UCString & Name, bool parents ) const;

    int AddVar( const lem::UCString & Name );

    int GetVarId( const lem::UCString & varname ) const;
  };

 } // namespace Solarix

#endif
