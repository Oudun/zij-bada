#ifndef _TEST_H_
#define _TEST_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

/**
 * [Test] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class Zij : public Osp::App::Application {

	public:
		static Osp::App::Application* CreateInstance(void);

	public:
		Zij();
		~Zij();

	public:
		bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
		bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);

};

#endif
