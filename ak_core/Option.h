#ifndef AK_OPTION_H__
#define AK_OPTION_H__

#include "ParseOptionsBase.h"
#include <string>

namespace ak {

class Option {
   template<typename> friend class factory;

public:
   Option()
   : registered_id_( 0 )
   {
   }
   
   int registered_id() const
   {
      return registered_id_;
   }

   //! "verbose,v"  
   virtual std::string cmdline_id() = 0;

   //! "verbose"
   virtual std::string name();

   //! "verbose desc"
   virtual std::string description();

   virtual ParseOptionsBase::StorageType * storage_type();

   virtual void execute();


private:
   int registered_id_;

   /*
    * Set automatically by factory
    */
   void set_registered_id( int id )
   {
      registered_id_ = id;
   }

};


class UserOption : public Option {
public:
};


class SystemOption : public Option {
   public:
};


}

#endif



