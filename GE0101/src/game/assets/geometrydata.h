#pragma once
#include "../../graphics/mesh.h"
#include <string>
#include <vector>

class GeometryData
{
	std::vector<std::shared_ptr<Mesh>>			_data;
public:
	GeometryData();
	~GeometryData();
	void loadGeometry(const std::string& filepath);
	void addGeometry(std::shared_ptr<Mesh> mesh);
	void removeGeometry(const std::string& name);
	const std::shared_ptr<Mesh> getGeometry(const std::string& name) const;
};