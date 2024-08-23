#include "objLoader.hpp"

void loadOBJ(
	const char * path,
	std::vector<Vec3>& out_vertices,
	std::vector<Vec2>& out_uvs,
	std::vector<Vec3>& out_normals
) {

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vec3> temp_vertices;
	std::vector<Vec2> temp_uvs;
	std::vector<Vec3> temp_normals;

	std::ifstream file(path, std::ios::in);
	if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + path);
    }
	std::string line;
	while (std::getline(file, line)) {
		if (line.substr(0,2) == "v ") {
			std::istringstream iss(line.substr(2));
			float x, y, z;

			if (iss >> x >> y >> z) {
				temp_vertices.push_back(Vec3(x, y, z));
			} else {
				throw std::runtime_error(std::string("Wrong vertice format: ") + line);
			}
		}
		else if (line.substr(0,3) == "vt ") {
			std::istringstream iss(line.substr(3));
			float x, y;
			if (iss >> x >> y) {
				temp_uvs.push_back(Vec2(x, y));
			} else {
				throw std::runtime_error(std::string("Wrong uv format: ") + line);
			}
		}
		else if (line.substr(0,3) == "vn ") {
			std::istringstream iss(line.substr(3));
			float x, y, z;
			if (iss >> x >> y >> z) {
				temp_normals.push_back(Vec3(x,y,z));
			} else {
				throw std::runtime_error(std::string("Wrong normal format: ") + line);
			}
		}
		else if (line.substr(0,2) == "f ") {
			std::istringstream iss(line.substr(2));
			std::string vertexDef;

			while(iss >> vertexDef) {
				unsigned int vIndex = 0, vtIndex = 0, vnIndex = 0;
				char separator;

				std::istringstream vertexStream(vertexDef);
				if (vertexStream >> vIndex) {
					vertexIndices.push_back(vIndex);
					if (vertexStream.peek() == '/') {
						vertexStream.get(separator);
						if (vertexStream.peek() != '/') {
							if (vertexStream >> vtIndex) {
								uvIndices.push_back(vtIndex);
							} else {
								throw std::runtime_error(std::string("Wrong face format: ") + vertexDef);
							}
						}
						if (vertexStream.peek() == '/') {
							vertexStream.get(separator);
							if (vertexStream >> vnIndex) {
								normalIndices.push_back(vnIndex);
							} else {
								throw std::runtime_error(std::string("Wrong face format: ") + vertexDef);
							}
						}
					}
				} else {
					throw std::runtime_error(std::string("Wrong face format: ") + vertexDef);
				}
			}
		}
		else {
			continue;
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices.size() > i ? uvIndices[i] : 0;
		unsigned int normalIndex = normalIndices.size() > i ? normalIndices[i] : 0;

		if (vertexIndex > temp_vertices.size()) {
			throw std::runtime_error(std::string("Vertex index out of bounds."));
		}
		Vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);

		if (uvIndex > 0 && uvIndex <= temp_uvs.size()) {
			Vec2 uv = temp_uvs[uvIndex - 1];
			out_uvs.push_back(uv);
		}
		
		if (normalIndex > 0 && normalIndex <= temp_normals.size()) {
			Vec3 normal = temp_normals[normalIndex -1];
			out_normals.push_back(normal);
		}
	}
	file.close();
	return ;
}