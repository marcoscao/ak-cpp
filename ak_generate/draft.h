
namespace ak {


class Option {
	int id;
	string short_name;
	string large_name;
	string desc;

	virtual void definition() = 0;
	virtual void large_name() = 0;
	virtual void short_name() = 0;
	virtual void string desc() = 0;
	virtual void execute() = 0;
};

class UserOption : public Option {
};

class SystemOption : public Option {
};





template<typename T>
class factory {
public:
	
	/*
	 * Register everything
	 */
	virtual void registrar() = 0;


	void register_item( int id, RegFn ) 
	{
		// add into RegMap
	}

	bool is_registered( int id )
	{
	}

	T * create_op( int id )
	{
		// creates and store into internal map to later delete it
	}

private:
	using RegFn = std::function< T * () >;
	using RegMap = std::unordered_map< int, RegFn > ct_;
	using Instances = std::vector< std::shared_ptr< Option > >;

	static RegMap registered_;
	static InstancssMap instances_;				// stores created instances to later delete
};

template<typename T>
factory<T>::ct_;





class OptionsFactory : public factory< Option > {

public:
	virtual void registrar()
	{
		register_item( SourcesOp::ID, &SourcesOp::create );
		register_item( HelpOp::ID, &HelpOp::create );
	}

};





class AppManager {
public:
	AppManager()
		: factory_()
	{
	}

	void set_options_factory( factory<Option> * f )
	{
		if( f == false )
			throw ak_exception("null factory");

		factory_ = std::shared_ptr< factory<Option> >( f );
		factory_->registrar();
	}

	void initializa() { 
	}

	virtual void add_options() 
	{ 
	}

	void execute()
	{
	}
	
private:
	std::shared_ptr< factory<Option> > factory_;
};



int main(int argc, char** argv )
{
	AppManager app;
	app.set_options_factory( new OptionsFactory() );
	
	app.add_option( SourcesOp::ID );
	app.add_option( HelpOp::ID );

	app.parse_options( argc, argv );

}