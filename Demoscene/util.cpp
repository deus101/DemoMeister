#include "util.h"
//#include <iostream>
//#include <fstream>

#include "world.h"
//#include "Rendrer\context.h"


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


	//BOOST_FOREACH(ptree::value_type each, pt)
	BOOST_FOREACH(ptree::value_type each, pt.get_child("DeployEditBuild."))
	{
		//Resource_Paths.insert(boost::filesystem::path(each.second.data()) );
		
		std::cout << each.first.data() << " : " << each.second.data() << std::endl;

		Resource_Paths.insert(each.second.data());
		//Resource_Paths.insert()
	}
	//ptree::value_type& const v,
	//	std::basic_ostream< std::string> >> pt.begin()
	//Resource_Paths.insert(boost::filesystem::path(v.second.data()));
	//Resource_Paths.insert(v.second.data());
	ProjectFolder = pt.get<std::string>("DeployEditBuild.MainProjectPath");
	ProductionName = pt.get<std::string>("DeployEditBuild.ProductionName");
	ProductioFolder = pt.get<std::string>("DeployEditBuild.ProductionFolder");
	
	//boost::filesystem::
	//AssetGlobal = boost::filesystem::path(std::string(ProjectFolder + "/" + ProductioFolder +))
	AssetGlobal = boost::filesystem::path(ProjectFolder);
	AssetGlobal.append("Assets");


	AssetProduction = boost::filesystem::path(ProjectFolder);
	AssetProduction.append("Productions");
	AssetProduction.append(ProductioFolder);
	AssetProduction.append("ProductionVault");



	boost::filesystem::recursive_directory_iterator iter(AssetProduction), eod;

	BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iter, eod)) {
		if (is_directory(i)) {
			std::cout << i.string() << std::endl;

		}
		else if (is_regular_file(i)) {
			std::cout << "--" << i.filename().string() << std::endl;

		}
	}


	//boost::filesystem::recursive_directory_iterator iter(AssetGlobal), eod;
	iter = boost::filesystem::recursive_directory_iterator(AssetGlobal);

	BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iter, eod)) {
		if (is_directory(i)) {
			std::cout << i.string() << std::endl;

		}
		else if (is_regular_file(i)) {
			std::cout << "--" << i.filename().string() << std::endl;

		}
	}



	
}

void DeploymentOrganizer::save()
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

void DeploymentOrganizer::deploy()
{


}

std::string DeploymentOrganizer::FindAndRegister(const std::string & Item)
{
	//if no we are looking for Model Folders most likely
	boost::filesystem::path File(Item);
	//bool HasExtension = boost::filesystem::has_extension() (Item);
	bool HasExtension = File.has_extension();

	std::string FileExtension = boost::filesystem::extension(Item);
		
	

	

	if (Util_CurrentFolder.empty() == true)
	{
		Util_CurrentFolder = AssetProduction;
	}

	//Util_CurrentFolder.append(Item).is_complete()
	//boost::filesystem::path local_Check = Util_CurrentFolder.append(Item);
	
	boost::filesystem::path local_Check( Util_CurrentFolder);
	local_Check.append(Item);
	if (boost::filesystem::exists(local_Check))
	{ 
		return local_Check.string();
	}


	boost::filesystem::recursive_directory_iterator iter(AssetProduction), eod;

	BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iter, eod)) {
		if (is_regular_file(i)) {
			//cout << i.string() << endl;
			if (i.filename().compare(File) == 0)
			{ 
				Util_CurrentFolder = i.parent_path();
				return i.string();
				

			}
		}
	}

	Util_CurrentFolder = AssetGlobal;

	//boost::filesystem::recursive_directory_iterator iter(Util_CurrentFolder), eod;
	iter = boost::filesystem::recursive_directory_iterator(AssetGlobal);

	BOOST_FOREACH(boost::filesystem::path const& i, std::make_pair(iter, eod)) {
		if (is_regular_file(i)) {
			//cout << i.string() << endl;
			if (i.filename().compare(File) == 0)
			{
				Util_CurrentFolder = i.parent_path();
				return i.string();
			}
		}
	}

	return std::string("");
}