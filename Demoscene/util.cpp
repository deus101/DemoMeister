#include "util.h"
#include <iostream>
#include <fstream>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#include <boost/typeof/typeof.hpp>

void EngError(const char* pFileName, unsigned int line, const char* pError)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "%s:%d: %s", pFileName, line, pError);
	MessageBoxA(NULL, msg, NULL, 0);
#else
	fprintf(stderr, "%s:%d: %s\n", pFileName, line, pError);
#endif    
}


void EngFileError(const char* pFileName, unsigned int line, const char* pFileError)
{
#ifdef WIN32
	char msg[1000];
	_snprintf_s(msg, sizeof(msg), "%s:%d: unable to open file `%s`", pFileName, line, pFileError);
	MessageBoxA(NULL, msg, NULL, 0);
#else
	fprintf(stderr, "%s:%d: unable to open file `%s`\n", pFileName, line, pFileError);
#endif    
}


void DeploymentOrganizer::load(const std::string &filename)
{

	HumbleIni = boost::filesystem::path(filename.c_str());
	HumbleIni.remove_leaf();
	HumbleIni.append("DemoMeister.ini");

	HumbleIni.normalize();
	//if (!HumbleIni.is_complete());
	//return;
	bool test = HumbleIni.is_complete();
	// Create empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Load XML file and put its contents in property tree. 
	// No namespace qualification is needed, because of Koenig 
	// lookup on the second argument. If reading fails, exception
	// is thrown.


	boost::property_tree::read_ini(HumbleIni.string(), pt);

	// Get filename and store it in m_file variable. Note that 
	// we specify a path to the value using notation where keys 
	// are separated with dots (different separator may be used 
	// if keys themselves contain dots). If debug.filename key is 
	// not found, exception is thrown.
	

	// Get debug level and store it in m_level variable. This is 
	// another version of get method: if debug.level key is not 
	// found, it will return default value (specified by second 
	// parameter) instead of throwing. Type of the value extracted 
	// is determined by type of second parameter, so we can simply 
	// write get(...) instead of get<int>(...).
	//m_level = pt.get("debug.level", 0);

	//pt.operator!=
	// Iterate over debug.modules section and store all found 
	// modules in m_modules set. get_child() function returns a 
	// reference to child at specified path; if there is no such 
	// child, it throws. Property tree iterator can be used in 
	// the same way as standard container iterator. Category 
	// is bidirectional_iterator.
	//BOOST_FOREACH(ptree::value_type &v, boost::filesystem::path(pt.get_child("MainProjectPath")));
	//boost::property_tree::ptree::value_type &v
	//ptree subtree = (boost::property_tree::ptree) pt;

	//BOOST_FOREACH(ptree::value_type each, pt)
	BOOST_FOREACH(ptree::value_type each, pt.get_child("DeployEditBuild."))
	{
		//Resource_Paths.insert(boost::filesystem::path(each.second.data()) );
		Resource_Paths.insert(each.second.data());

	}
	//ptree::value_type& const v,
	//	std::basic_ostream< std::string> >> pt.begin()
	//Resource_Paths.insert(boost::filesystem::path(v.second.data()));
	//Resource_Paths.insert(v.second.data());
	m_file = pt.get<std::string>("DeployEditBuild.MainProjectPath");
}

void DeploymentOrganizer::save(const std::string &filename)
{

	// Create empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Put log filename in property tree
	//pt.put("debug.filename", m_file);

	// Put debug level in property tree
	//pt.put("debug.level", m_level);

	// Iterate over modules in set and put them in property
	// tree. Note that the add function places new key at the
	// end of list of keys. This is fine in most of the
	// situations. If you want to place item at some other
	// place (i.e. at front or somewhere in the middle),
	// this can be achieved using a combination of the insert
	// and put_value functions
	//BOOST_FOREACH(const std::string &name, m_modules)
	//	pt.add("debug.modules.module", name);

	// Write property tree to XML file
	//write_xml(filename, pt);

}