/*
 * Command base class
 *
 * Commands performs operatios such as "Collect Media files", "Save Collected Media", "update Collected Media"
 *
 */

#ifndef AK_CORE_COMMAND_H__
#define AK_CORE_COMMAND_H__

#include "ParseOptionsBase.h"
#include <string>

namespace ak {

   class VisitorCmd;

class Command {
   template<typename> friend class factory;

public:
   Command();
   
   int registered_id() const;

   //! "verbose"
   virtual std::string name();

   virtual void execute( ParseOptionsBase const & ) = 0;

   virtual void accept( VisitorCmd & );

private:
   int registered_id_;

   /*
    * Set automatically by factory
    */
   void set_registered_id_( int id );

};


}

#endif



