#ifndef AK_CORE_APP_MANAGER_H__
#define AK_CORE_APP_MANAGER_H__

using namespace std;

namespace ak {

   class AppManager {
      
	void initializa() 

    //! Add registered options
	virtual void add_options() 

	void execute()


   };



   class AkGenFactory : public OptionsFactory {
      public:
         virtual void rgister_options();
   };



   
   class AkGenApp : public AppMgr {
public:
	void add_options()
	{
		add_option( UO_SOURCES );

	}
private:
	void register_options_() {
		register_option( UO_SOURCES, SourcesOp );
		register_option( UO_HELP, HelpOp );

	}

};


}

#endif

