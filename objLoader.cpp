#include "objLoader.h"

bool objLoad(const char* path) {
	//printf("Loading OBJ file %s...\n", path);

	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec3> out_normals;
	std::vector<glm::vec2> out_uvs;

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::stringstream ss;
	std::ifstream in_file(path);
	std::string line = "";
	std::string prefix = "";
	GLuint temp = 0;

	if (!in_file.is_open()) {
		throw "ERROR COULD NOT OPEN OBJ FILE";
	}

	while (std::getline(in_file, line)) {
		ss.clear();
		ss.str(line);
		ss >> prefix;
		if (prefix == "#" || prefix == "o" || prefix == "s") {
			ss.ignore();
		}else if (prefix == "v") {
			glm::vec3 vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (prefix == "vt") {
			glm::vec2 uv;
			ss >> uv.x >> uv.y;
			uv.y = -uv.y;
			temp_uvs.push_back(uv);
		}
		else if (prefix == "vn") {
			glm::vec3 normal;
			ss >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (prefix == "f") {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int c = 0;
			while (ss >> vertex1 || ss >> vertex2 || ss >> vertex3) {
				if (c == 0) {
					vertexIndices.push_back(vertexIndex[temp]);
				}
				else if (c == 1) {
					uvIndices.push_back(uvIndex[temp]);
				}
				else if (c == 2) {
					normalIndices.push_back(normalIndex[temp]);
				}

				if (ss.peek() == '/') {
					c++;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ') {
					c++;
					ss.ignore(1, ' ');
				}

				if (c > 2) {
					c = 0;
				}
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++) {

			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			glm::vec2 uv = temp_uvs[uvIndex - 1];
			glm::vec3 normal = temp_normals[normalIndex - 1];

			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_uvs.push_back(uv);
			out_normals.push_back(normal);
		}
	}

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, out_vertices.size() * sizeof(glm::vec3), &out_vertices[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, out_normals.size() * sizeof(glm::vec3), &out_normals[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, out_uvs.size() * sizeof(glm::vec2), &out_uvs[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, out_vertices.size());
	glDrawArrays(GL_TRIANGLES, 0, out_normals.size());


	return true;
}