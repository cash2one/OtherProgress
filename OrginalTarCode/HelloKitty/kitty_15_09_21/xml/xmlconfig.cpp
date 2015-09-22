#include "xmlconfig.h"

namespace config
{
	xmltest_t _xmltest;
	info_collect_config_t _info_collect_config;
	new_user_init_t _new_user_init;
	redis_config_t _redis_config;
	redis_config_local_t _redis_config_local;
	new_massive_config_t _new_massive_config;
	test_config_t _test_config;

	void init(const config::ReadXmlFunc &func)
	{
		Fir::XMLParser xml;
		_xmltest.load(xml, func(xml, "xmltest.xml"));
		_info_collect_config.load(xml, func(xml, "info_collect_config.xml"));
		_new_user_init.load(xml, func(xml, "new_user_init.xml"));
		_redis_config.load(xml, func(xml, "redis_config.xml"));
		_redis_config_local.load(xml, func(xml, "redis_config_local.xml"));
		_new_massive_config.load(xml, func(xml, "new_massive_config.xml"));
		_test_config.load(xml, func(xml, "test_config.xml"));
	}

	const xmltest_t &xmltest()
	{
		return _xmltest;
	}
	const info_collect_config_t &info_collect_config()
	{
		return _info_collect_config;
	}
	const new_user_init_t &new_user_init()
	{
		return _new_user_init;
	}
	const redis_config_t &redis_config()
	{
		return _redis_config;
	}
	const redis_config_local_t &redis_config_local()
	{
		return _redis_config_local;
	}
	const new_massive_config_t &new_massive_config()
	{
		return _new_massive_config;
	}
	const test_config_t &test_config()
	{
		return _test_config;
	}
}

