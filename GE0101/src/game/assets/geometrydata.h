#pragma once
#include "../../graphics/mesh.h"
#include <string>
#include <vector>

class GeometryData
{
	std::vector<Mesh*>			_data;
public:
	GeometryData();
	~GeometryData();
	void loadGeometry(const std::string& filepath);
	void pushGeometry(Mesh* mesh);
	void popGeometry(const std::string& name);
	const Mesh* getGeometry(const std::string& name) const;
};