//
// FilesystemConfigurationTest.cpp
//
// $Id: //poco/svn/Util/testsuite/src/FilesystemConfigurationTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "FilesystemConfigurationTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Util/FilesystemConfiguration.h"
#include "Poco/AutoPtr.h"
#include <algorithm>


using Poco::Util::FilesystemConfiguration;
using Poco::Util::AbstractConfiguration;
using Poco::AutoPtr;


FilesystemConfigurationTest::FilesystemConfigurationTest(const std::string& name): CppUnit::TestCase(name)
{
}


FilesystemConfigurationTest::~FilesystemConfigurationTest()
{
}


void FilesystemConfigurationTest::testFilesystemConfiguration()
{
	AutoPtr<FilesystemConfiguration> config = new FilesystemConfiguration("TestConfiguration");
	
	config->setString("logging.loggers.root.channel.class", "ConsoleChannel");
	config->setString("logging.loggers.app.name", "Application");
	config->setString("logging.loggers.app.channel", "c1");
	config->setString("logging.formatters.f1.class", "PatternFormatter");
	config->setString("logging.formatters.f1.pattern", "[%p] %t");
	config->setString("logging.channels.c1.class", "ConsoleChannel");

	assert (config->getString("logging.loggers.root.channel.class") == "ConsoleChannel");
	assert (config->getString("logging.loggers.app.name") == "Application");
	assert (config->getString("logging.loggers.app.channel") == "c1");
	assert (config->getString("logging.formatters.f1.class") == "PatternFormatter");
	assert (config->getString("logging.formatters.f1.pattern") == "[%p] %t");

	config->setString("logging.loggers.app.channel", "c2");
	assert (config->getString("logging.loggers.app.channel") == "c2");
	
	AbstractConfiguration::Keys keys;
	config->keys(keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "logging") != keys.end());

	config->keys("logging", keys);
	assert (keys.size() == 3);
	assert (std::find(keys.begin(), keys.end(), "loggers") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "formatters") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "channels") != keys.end());

	config->keys("logging.formatters", keys);
	assert (keys.size() == 1);
	assert (std::find(keys.begin(), keys.end(), "f1") != keys.end());

	config->keys("logging.formatters.f1", keys);
	assert (keys.size() == 2);
	assert (std::find(keys.begin(), keys.end(), "class") != keys.end());
	assert (std::find(keys.begin(), keys.end(), "pattern") != keys.end());
	
	assert (config->hasProperty("logging.loggers.root.channel.class"));
	config->clear();
	assert (!config->hasProperty("logging.loggers.root.channel.class"));
}


void FilesystemConfigurationTest::setUp()
{
}


void FilesystemConfigurationTest::tearDown()
{
}


CppUnit::Test* FilesystemConfigurationTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("FilesystemConfigurationTest");

	CppUnit_addTest(pSuite, FilesystemConfigurationTest, testFilesystemConfiguration);

	return pSuite;
}
