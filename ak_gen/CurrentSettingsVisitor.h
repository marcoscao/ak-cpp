#ifndef AK_GEN_CURRENT_SETTINGS_VISITOR_H__
#define AK_GEN_CURRENT_SETTINGS_VISITOR_H__

#include "ak_core/ParseOptionsBase.h"
#include "ak_core/Visitor.h"

#include <iostream>
#include <string>
#include <sstream>

namespace ak { namespace gen {


   class GenVisitor : public Visitor {
   public:
       virtual void visit( Option & op ) 
       {
          if( typeid( op ) == typeid( SourcesOp ) )
                visit( static_cast<SourcesOp&>( op ) );
          else if( typeid( op ) == typeid( VerboseOp ) )
                visit( static_cast<VerboseOp&>( op ) );
         }

       virtual void visit( SourcesOp & ) { ; }

       virtual void visit( VerboseOp & ) { ; }
   };



   class CurrentSettingsVisitor : public GenVisitor {
   public:
      CurrentSettingsVisitor( ParseOptionsBase const & pob )
      : pob_( pob )
      {
      }

      virtual void visit( SourcesOp & op) 
      {
         buffer_ << "sources: ";
         for( auto const i : op.get_data() ) {
            buffer_ << i << std::endl << "        ";
         }
      }

      virtual void visit( VerboseOp & op )
      {
         buffer_ << "verbose: ";
         if( pob_.has_user_entered_option( VERBOSE_OP_ID) )
           buffer_ << "YES" << std::endl;
         else
           buffer_ << "NO" << std::endl;
      }

      std::stringstream const & current_settings() const
      {
          return buffer_;
      }

   private:
      std::stringstream buffer_;
      ParseOptionsBase const & pob_;
   };


} }


#endif

