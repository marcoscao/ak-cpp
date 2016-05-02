#ifndef AK_GEN_SOURCES_OP_H__
#define AK_GEN_SOURCES_OP_H__

#include "ak_core/FileSystem.h"
#include "ak_core/LogSystem.h"
#include "ak_core/Option.h"
#include "ak_core/ParseOptionsBase.h"

#include <iostream>
#include <string>

namespace ak { namespace gen {

   class SourcesOp : public ak::UserOption {
   public:

      struct stats {
         long files;
         long folders;
         unsigned long size;

         stats() : files(0), folders(0), size(0) {}

         stats operator+( stats const & b )
         {
            files += b.files;
            folders += b.folders;
            size += b.size;

            return *this;
         }
      };


      //! Holds passed source paths through command line
      using SourcesCt = std::vector< std::string >;

      SourcesOp();

      static Option * create();

      virtual std::string cmdline_id();

      virtual std::string name();

      virtual std::string description();

      virtual ParseOptionsBase::StorageType * storage_type();

      virtual void execute( ParseOptionsBase const & );

      //virtual void accept( Visitor & );

      const SourcesCt & sources() const;

   private:
      bool using_verbose_;
      SourcesCt sources_paths_;

      stats traverse_source_path_( FileSystem::f_type const & source_path );
   };


} }


#endif

