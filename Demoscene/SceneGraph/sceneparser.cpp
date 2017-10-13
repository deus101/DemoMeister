#include "sceneparser.h"
#include "node.h"

#include "transform.h"
#include "targetNode.h"
#include "modelNode.h"


#include "../tinyxml2.h"

using namespace NS_SG;
using namespace tinyxml2;

using NS_VEC::VEC3;
using NS_VEC::QUAT;



float getFloat(XMLElement *elem, const char *name, float default_val)
{
	const char *ret = elem->Attribute(name);
	if (!ret) return default_val;
	return float(atof(ret));
}

static std::string getString(XMLElement *elem, const char *name, const std::string &defaultString = "")
{
	const char *ret = elem->Attribute(name);
	if (NULL == ret) return defaultString;
	return ret;
}

static VEC3 getVector3(XMLNode *node)
{
	XMLElement *elem = node->ToElement();
	assert(NULL != elem);

	return VEC3(
		getFloat(elem, "x", 0),
		getFloat(elem, "y", 0),
		getFloat(elem, "z", 0)
		);
}

static std::string stripDir(const std::string &file)
{
	std::string::size_type idx = file.rfind('\\'); 
	if (std::string::npos != idx) return file.substr(0, idx + 1);
	else return "";
}

QUAT v3toQ(const VEC3 &v)
{
	return QUAT(
		float(v.X),
		float(v.Y),
		float(v.Z)
		);
}



class SceneParser
{
private:
	const std::string filename;
	const std::string basename;
	composite *composition;

public:
	SceneParser::SceneParser(composite* comp, const std::string filename) : filename(filename), basename(stripDir(filename))
	{
		composition = comp;
	}

	nodePtr loadPrsTransform( XMLElement *xmlElem)
	{
		//objTransform *ret = new objTransform(getString(xmlElem, "name"));
		boost::shared_ptr<NS_SG::objTransform>  ret( new objTransform(getString(xmlElem, "name")));
		ret->setPosition(VEC3(0, 0, 0));
		//ret->setRotation(QUAT::identity());
		//ret->setScale(Vector3(1, 1, 1));

		std::string animFilename = getString(xmlElem, "keys");
		
		if (!animFilename.empty())
		{
			FILE *fp = fopen((basename + animFilename).c_str(), "rb");
			if (NULL == fp) throw std::string("failed to load animation \"") + basename + animFilename + "\"";

			objectAnim animTrack;

			size_t count = 0;
			fread(&count, sizeof(size_t), 1, fp);
			for (size_t i = 0; i < count; ++i)
			{
				float time;
				VEC3 position;
				VEC3 rotation;
				VEC3 scale;

				fread(&time, sizeof(float), 1, fp);
				fread(&position, sizeof(float), 3, fp);
				fread(&rotation, sizeof(float), 3, fp);
				fread(&scale, sizeof(float), 3, fp);

				animTrack.setPosKeyFrame(time, position);
				animTrack.setRotKeyFrame(time, v3toQ(rotation));
				animTrack.setScaleKeyFrame(time, scale);
			}

			composition->addObjectAnime(ret.get(), animTrack);
			fclose(fp);
			fp = NULL;
		}

		XMLNode *curr = xmlElem->FirstChild();
		while (curr) {
			XMLElement *currElem = curr->ToElement();
			if (currElem) {
				const char *val = curr->Value();
				if (strcmp(val, "position") == 0)
					ret->setPosition(getVector3(currElem));
				else if (strcmp(val, "rotation") == 0)
					ret->setRotation(v3toQ(getVector3(currElem) * float(M_PI / 180)));
				else if (strcmp(val, "scale") == 0)
					ret->setScale(getVector3(currElem));
				else if (strcmp(val, "children") == 0)
					getChildren(ret, currElem);
				else
					throw std::string("unknown element \"") + val + std::string("\"");
			}
			curr = curr->NextSibling();
		}

		return ret;
	}

	std::map<NS_SG::targetTransform*, std::string> targetmap;
	nodePtr loadTargetTransform(XMLElement *xmlElem)
	{
		boost::shared_ptr<NS_SG::targetTransform> ret( new targetTransform(getString(xmlElem, "name")));
		targetmap[ret.get()] = getString(xmlElem, "target");

		XMLNode *curr = xmlElem->FirstChild();
		while (curr) {
			XMLElement *currElem = curr->ToElement();
			if (currElem) {
				const char *val = curr->Value();
				if (strcmp(val, "children") == 0)
					getChildren( ret, currElem);
				else
					throw std::string("unknown element \"") + val + std::string("\"");
			}
			curr = curr->NextSibling();
		}

		return ret;
	}

	nodePtr getCamera(XMLElement *xmlElem)
	{
		std::string fileName = getString(xmlElem, "file");

//		camera *ret = new camera(getString(xmlElem, "name"));
		boost::shared_ptr<NS_SG::camera> ret(new camera(getString(xmlElem, "name")));
		
		ret->setFov(getFloat(xmlElem, "fov", 60.0f));
		ret->setZNear(getFloat(xmlElem, "znear", 0.1f));
		ret->setZFar(getFloat(xmlElem, "zfar", 1000.0f));

		return ret;
	}

	nodePtr loadMesh(XMLElement *xmlElem)
	{
		std::string fileName = getString(xmlElem, "file");
		//GBuffer::
		boost::shared_ptr<NS_SG::modelNode> ret(new modelNode(
			getString(xmlElem, "name"),
			&NS_ENG::model(basename + fileName + ".obj", basename + fileName + ".mtl"),
			&NS_EFF::GeomPacket()
			));

		return ret;
	}

	void getChildren(svakRef graphNode, XMLElement *xmlElem)
	{
		XMLNode *curr = xmlElem->FirstChild();
		while (curr) {
			XMLElement *currElem = curr->ToElement();
			if (currElem) {
				//boost::shared_ptr<NS_SG::node> newChild = NULL;
				nodePtr newChild = NULL;
				const char *val = curr->Value();

				if (strcmp(val, "prs_transform") == 0)
					newChild = loadPrsTransform(currElem);
				else if (strcmp(val, "target_transform") == 0)
					newChild = loadTargetTransform( currElem);
				else if (strcmp(val, "mesh") == 0)
					newChild = loadMesh( currElem);
				else if (strcmp(val, "camera") == 0)
					newChild = getCamera(currElem);
				/*else if (strcmp(val, "point_light") == 0)
					break;
				else if (strcmp(val, "directional_light") == 0)
					break;*/
				else
					throw std::string("unknown element \"") + val + std::string("\"");

				assert(NULL != newChild);
				graphNode.lock()->addChild(newChild.get());
			}
			curr = curr->NextSibling();
		}
	}

};

composite *NS_SG::parseScene(const std::string filename)
{
	//bool Failed = false;
	//composite *composed = new composite(filename);
	boost::shared_ptr<NS_SG::composite> composed(new composite(filename));
	
	tinyxml2::XMLDocument doc;
	
	try
	{
		if (!doc.LoadFile(filename.c_str()))
			std::cout << "shit";
			//throw  std::string(doc.GetErrorStr1());

		SceneParser sceneParser(composed.get(), filename);
	
		XMLElement *xmlRoot = doc.RootElement();
		if (strcmp(xmlRoot->Value(), "scene") != 0) throw std::string( "excpected 'scene'! \n");

		XMLNode *curr = xmlRoot->FirstChild();
		while (curr)
		{
		XMLElement *currElem = curr->ToElement();
		if (currElem)
		{
			if (strcmp(curr->Value(), "children") == 0)
				sceneParser.getChildren(composed, currElem);
			else
				throw curr->Value() + std::string("excpected 'scene'! \n");
		}
		
		}
		curr = curr->NextSibling();
		return composed.get();

	}
	catch (const std::string &str)
	{
		delete composed.get();
		std::cout << "!Failed to parse " + filename + " : " + str + "\n";
	}
}