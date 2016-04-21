#ifndef AK_CORE_COMMAND_H__
#define AK_CORE_COMMAND_H__

namespace ak {

   class PO;

   class Command {
   public:
      //Command( Engine & );
      Command();
      ~Command();		

      virtual void execute( PO const & ) = 0;

      //Engine & engine();

      //const Engine & engine() const;

   private:
      //Engine & engine_;

   };

}

#endif

