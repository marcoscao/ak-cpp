
#ifndef AK_OPTIONS_FACTORY_H__
#define AK_OPTIONS_FACTORY_H__

#include <memory>

namespace ak {

   class Option;

   class OptionsFactory {
   public:
      using RegFn = std::function< Option * () >;
      using RegMap = std::unordered_map< int, RegFn >;

      OptionsFactory & instance();

      void register_op( int id, RegFn );

      Option * create_op( int id );


   private:
      OptionsFactory();

   };


}

#endif



