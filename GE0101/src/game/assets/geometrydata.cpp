#include "geometrydata.h"
#include "../../defs.h"

GeometryData::GeometryData()
{
	_data.reserve(30);
}

void GeometryData::loadGeometry(const std::string& filepath)
{
	Mesh* mesh = new Mesh(filepath);
	pushGeometry(mesh);
}

void GeometryData::pushGeometry(Mesh* mesh)
{
	if (!mesh)
	{
		WARN("Could not push Mesh to Geometry Data - nullptr exception");
		return;
	}
	_data.push_back(mesh);
}

GeometryData::~GeometryData()
{
	for (auto& mesh : _data)
	{
		delete mesh;
	}
	_data.clear();
}

void GeometryData::popGeometry(const std::string& name)
{
	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		if (_data[i]->getName() == name)
		{
			delete _data[i];
			_data[i] = nullptr;
			MSG("Deleted Mesh: " << name);
			return;
		}
	}
	WARN("Could not pop " << name << " - No such Mesh in Geometry Data");
}