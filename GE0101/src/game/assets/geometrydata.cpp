#include "geometrydata.h"
#include "../../defs.h"

GeometryData::GeometryData()
{
	_data.reserve(30);
}

void GeometryData::loadGeometry(const std::string& filepath)
{
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(filepath);
	addGeometry(mesh);
}

void GeometryData::addGeometry(std::shared_ptr<Mesh> mesh)
{
	_data.push_back(mesh);
}

GeometryData::~GeometryData()
{
	_data.clear();
}

void GeometryData::removeGeometry(const std::string& name)
{
	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		if (_data[i]->getName() == name)
		{
			_data.erase(_data.begin() + i);
			MSG("Deleted Mesh: " << name);
			return;
		}
	}
	WARN("Could not remove " << name << " - No such Mesh in Geometry Data");
}

const std::shared_ptr<Mesh> GeometryData::getGeometry(const std::string& name) const
{
	for (auto& mesh : _data)
	{
		if (mesh->getName() == name)
		{
			return mesh;
		}
	}
	ERR("Could not retrieve Mesh: " << name << " - No such Mesh in Geometry Data");
	return nullptr;
}