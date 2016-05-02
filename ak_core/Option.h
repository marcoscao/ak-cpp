#ifndef AK_CORE_OPTION_H__
#define AK_CORE_OPTION_H__

#include "ParseOptionsBase.h"
#include <string>

namespace ak {

   class Visitor;

class Option {
   template<typename> friend class factory;

public:
   Option();
   
   int registered_id() const;

   //! "verbose,v"  
   virtual std::string cmdline_id() = 0;

   //! "verbose"
   virtual std::string name() = 0;

   //! "verbose desc"
   virtual std::string description() = 0;

   virtual ParseOptionsBase::StorageType * storage_type();

   virtual void execute( ParseOptionsBase const & ) = 0;

   virtual void accept( Visitor & );

private:
   int registered_id_;

   /*
    * Set automatically by factory
    */
   void set_registered_id_( int id );

};


class UserOption : public Option {
public:
};


class SystemOption : public Option {
   public:
};


}

#endif



