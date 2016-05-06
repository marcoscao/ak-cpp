#ifndef AK_GEN_CURRENT_SETTINGS_VISITOR_H__
#define AK_GEN_CURRENT_SETTINGS_VISITOR_H__

#icnlude "
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

	class GenVisitor : public Visitor {
	public:
		void visit( SourcesOp & ) { ; }
		void visit( VerboseOp & ) { ; }

	};


   class CurrentSettingsVisitor : public ak::GenVisitor {
   public:

	  void visit( SourcesOp const & op) 
	  {
		  buffer_ << "sources: ";
		  for( auto i : op ) {
			buffer_ << i << endl << "        ";
		  }
	  }

	  void visit( VerboseOp const & )
	  {
		  buffer_ << "verbose: ";
		  if( op.has_entered_user( ) )
			  buffer_ << "YES" << endl;
		  else
			  buffer_ << "NO" << endl;
	  }

	 

   private:
		std::streamtring buffer_;
   };


} }


#endif

