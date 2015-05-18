/*
**	DeSR
**	src/Token.i
**  ----------------------------------------------------------------------
**  Copyright (c) 2008  Giuseppe Attardi (attardi@di.unipi.it).
**  ----------------------------------------------------------------------
**
**  This file is part of Tanl.
**
**  Tanl is free software; you can redistribute it and/or modify it
**  under the terms of the GNU General Public License, version 3,
**  as published by the Free Software Foundation.
**
**  Tanl is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**  ----------------------------------------------------------------------
*/

%{
#include "Token.h"
%}

%include std_string.i
%include std_vector.i

%include RefCountable.h

using namespace std;

%feature("unref") std::vector<Tanl::Token*> "for (int i=0; i < $this->size(); i++) delete (*$this)[i]; delete $this;"

%template(VectorToken) std::vector<Tanl::Token*>;

namespace Tanl {

typedef unsigned		AttributeId;
typedef vector<TokenLink>	TokenLinks;

struct AttributeIndex //: public IXE::Text::WordIndex
{
  AttributeId		insert(const char* name);
  vector<char const*>	names;
};

struct Language
{
  Language(char const*);
};

%newobject Corpus::create;
%newobject Corpus::sentenceReader;
%newobject Corpus::toString;

class Sentence;
class SentenceReader;

class Corpus
{
public:
  Corpus(Language const&);
  static Corpus*	create(Language const& lang, char const* inputFormat);
  static Corpus*	create(char const* lang, char const* inputFormat);
  SentenceReader*	sentenceReader(std::istream* is);
  std::string		toString(Sentence const& sent) const; 

  AttributeIndex	index;
};

struct Attributes
{
  Attributes(AttributeIndex* attributeIndex);
  string const*	get(char const* name) const;
  AttributeId	index(char const* key);
  void		insert(char const* key, char const* value);
  void		insert(char const* key, int value);
};

struct TokenLink
{
  TokenLink(int head = -1, char const* label = "");

  int		head;
  string	label;
};

struct Tag
{
  Tag(const string& xmlTag);
  const string	open() const;
  const string	close() const;

  string	name;

#ifdef SWIGJAVA
%rename(set) __setitem__;
%rename(get) __getitem__;
#endif

  %extend {
    string __getitem__(const std::string& key) { return (*self)[key]; }
    void __setitem__(const std::string& key, const std::string& val) {
	  (*self)[key] = val;
    }
  }
};

#ifdef SWIGPYTHON
// Has to go before the class declaration
%feature("ref") Context "$self->incRef();"
%feature("unref") Context "$self->Dispose();"
#endif
#ifdef SWIGJAVA
// FIXME: has no effect
%delobject Context::Dispose;
#endif

struct Context : public RefCountable
{
  Context(const string& xmlTag, Context* parent = 0);

  Tag		tag;
  Context*	parent;

#ifdef SWIGPYTHON
  %extend {
     bool operator ==(void* other) { return $self == other; }
     bool operator !=(void* other) { return $self != other; }
  }
#endif
#ifdef SWIGJAVA

%typemap(javacode) Context %{
  public boolean equals(Object obj) {
    if (obj instanceof $javaclassname)
      return (($javaclassname)obj).swigCPtr == this.swigCPtr;
    return false;
  }
  public int hashCode() {
     return (int)swigCPtr;
  }
%}
#endif
};

%newobject Token::context;
%newobject Token::__repr__;
%newobject Token::__getitem__;

class Token
{
public:
  Token(string form, Corpus& corpus, Context* context = 0);
  Token(string form, AttributeIndex* index, Context* context = 0);
  Token(string form, Attributes& attributes, TokenLinks& links, Context* context = 0);
  int		attrIndex(char const* name);

  string	form;
  Attributes	attributes;
  TokenLinks	links;
  //Context*	context; // access through method below

  %extend {
    Context* context() {
       if ($self->context)
          $self->context->incRef(); // needed to avoid destruction.
       return $self->context;
    }
  }

#ifdef SWIGJAVA
%rename(toString) __repr__;
%rename(setAttribute) __setitem__;
%rename(getAttribute) __getitem__;
#endif

  %extend {

     const char* __repr__() {
       static char tmp[1024];
       char* end = tmp + sprintf(tmp, "<token");
       for (Tanl::Attributes::const_iterator fit = $self->attributes.begin();
	    fit != $self->attributes.end(); ++fit)
	 // iterator returns pointer to value
	 end += sprintf(end, " %s=\"%s\"", (*fit).first, (*fit).second->c_str());
       sprintf(end, " />");
       return strdup(tmp);
     }

     void __setitem__(const char* key, const char* val) {
       $self->attributes.insert(key, val);
     }

     void __setitem__(const char* key, int val) {
       $self->attributes.insert(key, val);
     }

     const char* __getitem__(const char* key) {
       const std::string* item = $self->attributes.get(key);
       return item ? strdup(item->c_str()) : 0;
     }
  }
};

%newobject TreeToken::__repr__;

struct TreeToken
{
  TreeToken(int id, Token* token);

  Token*		token;
  unsigned		id;
  vector<TreeToken*>	left;  ///< list of left child tokens
  vector<TreeToken*>	right; ///< list of right child tokens

  std::string const&	form();
  std::string const*	get(char const* key);
  void			set(char const* key, char const* value);

  int			linkHead(int i = 0) const;
  std::string const&	linkLabel(unsigned i = 0) const;

#ifdef SWIGJAVA
%rename(toString) __repr__;
%rename(getAttribute) __getitem__;
#endif

  %extend {
    const char* __repr__() {
      char tmp[1024];
      char* end = tmp + sprintf(tmp, "<token");
      for (Tanl::Attributes::const_iterator fit = $self->token->attributes.begin();
	   fit != $self->token->attributes.end(); ++fit)
	end += sprintf(end, " %s=\"%s\"", (*fit).first, (*fit).second->c_str());
      sprintf(end, " />");
      return strdup(tmp);
    }

    string __getitem__(const char* key) { return *$self->token->get(key); }
  }
};

} // namespace Tanl

%newobject std::vector<Tanl::Token*>::__repr__;

#ifdef SWIGJAVA
%rename(toString) std::vector<Tanl::Token*>::__repr__;
#endif

%extend std::vector<Tanl::Token*> {
  const char* __repr__() {
    std::stringstream ss;
    ss << "[";
    for (std::vector<Tanl::Token*>::const_iterator fit = $self->begin();
	 fit != $self->end(); ++fit) {
      if (fit != $self->begin())
         ss << ", ";
      ss << **fit;
    }
    ss << "]";
    return strdup(ss.str().c_str());
  }
}
