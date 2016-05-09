#ifndef AK_CORE_OPTION_H__
#define AK_CORE_OPTION_H__

#include "ParseOptionsBase.h"
#include <memory>
#include <string>


namespace ak {

   class Visitor;


class Option {
   template<typename> friend class Factory;

protected:
   Option();

public:
   virtual ~Option() = default;

   int registered_id() const;

   //! "verbose,v"  
   virtual std::string cmdline_id() const = 0;

   //! "verbose"
   virtual std::string name() const = 0;

   //! "verbose desc"
   virtual std::string description() const = 0;

   virtual ParseOptionsBase::StorageType * storage_type();

   //virtual void execute( ParseOptionsBase const & );

   virtual void accept( Visitor & ) = 0;


private:
  int registered_id_;

  void set_registered_id_( int id );
};


class UserOption : public Option {
public:
};


class SystemOption : public Option {
   public:
};


} // end namespace 




/*
 * core Option sub-macros used by the final below AK_... macros to help define classes
 */


/*
 * submacro: Starting Common option class code
 */
#define __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
class CLASS_NAME : public Option { \
    template<typename> friend class factory; \
   friend std::unique_ptr<CLASS_NAME> std::make_unique<CLASS_NAME>(); \
public: \
   \
   /*static const int REGISTERED_ID = ID;*/ \
   static std::unique_ptr<Option> create() { return std::make_unique<CLASS_NAME>(); } \
   virtual std::string cmdline_id() const { return CMDLINE_ID; } \
   virtual std::string name() const { return NAME; } \
   virtual std::string description() const { return DESC; } \
   virtual void execute( ParseOptionsBase const & pob ) { ; } \
   virtual void accept( Visitor & v ) { v.visit( *this ); } 


/*
 * submacro: end common option class code
 */
#define __AK_END_DEFINE_OPTION_CLASS__( CLASS_NAME ) \
private: \
   /*CLASS_NAME() { set_registered_id( ID ); }*/ \
   CLASS_NAME() { ; } \
};


/*
 * submacro: end option class holding variable
 */
#define __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME ) \
public: \
   STORAGE_DATA & get_data() { return storage_data_; } \
   const STORAGE_DATA & get_data() const { return storage_data_; } \
private: \
   STORAGE_DATA storage_data_; \
   /*CLASS_NAME() : storage_data_() { set_registered_id( ID ); } */ \
   CLASS_NAME() : storage_data_() { ; } \
}; 


/*
 * submacro: register option
 */
#define __AK_REGISTER_OPTION_CLASS__( CLASS_NAME, ID ) \
 Factory<Option>::instance().register_item< CLASS_NAME >( ID ); 





/*
 * Below usage final macros
 * -------------------------
 */

/*
 * Final Macro: defines an Option Class without vars
 */
#define AK_DEFINE_OPTION( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
   __AK_END_DEFINE_OPTION_CLASS__( CLASS_NAME ) \
   //__AK_REGISTER_OPTION_CLASS__( CLASS_NAME, ID )


/*
 * Final Macro: defines an Option class with the storage of a unique value
 */
#define AK_DEFINE_OPTION_WITH_UNIQUE_VALUE( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE, VAR_DEFAULT ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
   public: \
      \
      using VALUE_TYPE = VAR_TYPE; \
      using STORAGE_DATA = VALUE_TYPE; \
      /*using STORAGE_FN = ParseOptionsBase::set_unique< VALUE_TYPE >; */\
      \
      virtual ParseOptionsBase::StorageType * storage_type() \
      { \
         return ParseOptionsBase::set_unique< VALUE_TYPE >( &storage_data_, VAR_DEFAULT ); \
      } \
      \
   __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME ) \
   //__AK_REGISTER_OPTION_CLASS__( CLASS_NAME, ID )


/*
 * Final Macro: defines an Option with multiple values
 */
#define AK_DEFINE_OPTION_WITH_MULTIPLE_VALUES( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
   public: \
   \
      using VALUE_TYPE = VAR_TYPE; \
      using STORAGE_DATA = std::vector< VALUE_TYPE >; \
      /*using STORAGE_FN = ParseOptionsBase::set_multiple< VALUE_TYPE >;*/ \
      \
      virtual ParseOptionsBase::StorageType * storage_type() \
      { \
         return ParseOptionsBase::set_multiple< VALUE_TYPE >( &storage_data_ ); \
      } \
      \
   __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME ) \
   //__AK_REGISTER_OPTION_CLASS__( CLASS_NAME, ID )


/*
 * Final Macro: defines an Option with multiple values
 */
#define AK_DEFINE_REQUIRED_OPTION_WITH_MULTIPLE_VALUES( CLASS_NAME, ID, CMDLINE_ID, NAME, DESC, VAR_TYPE ) \
   __AK_START_DEFINE_OPTION_CLASS__( CLASS_NAME, CMDLINE_ID, NAME, DESC ) \
   public: \
   \
      using VALUE_TYPE = VAR_TYPE; \
      using STORAGE_DATA = std::vector< VALUE_TYPE >; \
      /*using STORAGE_FN = ParseOptionsBase::set_multiple< VALUE_TYPE >;*/ \
      \
      virtual ParseOptionsBase::StorageType * storage_type() \
      { \
         return ParseOptionsBase::set_multiple_required< VALUE_TYPE >( &storage_data_ ); \
      } \
      \
   __AK_END_DEFINE_OPTION_CLASS_WITH_VAR__( CLASS_NAME ) \
   //__AK_REGISTER_OPTION_CLASS__( CLASS_NAME, ID )




#endif  // end Option.h





