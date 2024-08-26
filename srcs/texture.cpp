// #include "texture.hpp"

// GLuint loadBMP(const char *imagepath) {
// 	unsigned char header[54];
// 	unsigned int dataPos;
// 	unsigned int imageSize;
// 	unsigned int width, height;
// 	unsigned char *data;

// 	std::ifstream file(imagepath, std::ios::binary);
//     if (!file.is_open()) {
//         throw std::runtime_error(std::string("Failed to open file: ") + imagepath);
//     }

// 	file.read(reinterpret_cast<char*>(header), 54);
// 	if (file.gcount() != 54) {
// 		throw std::runtime_error(std::string("Not a correct BMP file: Couldn't read the header!"));
// 	}

// 	if (header[0] != 'B' || header[1] != 'M') {
//         throw std::runtime_error("Not a correct BMP file: Incorrect header signature!");
//     }

// 	int headerField = 0;
// 	std::memcpy(&headerField, &header[0x1E], sizeof(int));
// 	if (headerField != 0) {
// 		throw std::runtime_error(std::string("Not a correct BMP file: header[0x1E] is not 0!"));
// 	}

// 	int bpp = 0;
// 	std::memcpy(&bpp, &header[0x1C], sizeof(int));
// 	if (bpp != 24) {
// 		throw std::runtime_error(std::string("Not a correct BMP file: bpp is not 24!"));
// 	}

// 	std::memcpy(&dataPos, &header[0x0A], sizeof(int));
//     std::memcpy(&imageSize, &header[0x22], sizeof(int));
//     std::memcpy(&width, &header[0x12], sizeof(int));
//     std::memcpy(&height, &header[0x16], sizeof(int));

// 	if (imageSize == 0) {
// 		imageSize = width * height * 3;
// 	}
// 	if (dataPos == 0) {
// 		dataPos = 54;
// 	}

// 	data = new unsigned char [imageSize];
// 	file.read(reinterpret_cast<char*>(data), imageSize);
// 	file.close();

// 	GLuint textureID;
// 	glGenTextures(1, &textureID);

// 	glBindTexture(GL_TEXTURE_2D, textureID);
// 	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

// 	delete[] data;

// 	// Poor filtering, or ...
// 	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
// 	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 

// 	// ... nice trilinear filtering ...
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 	// ... which requires mipmaps. Generate them automatically.
// 	glGenerateMipmap(GL_TEXTURE_2D);

// 	return textureID;
// }

#include "texture.hpp"
// #include <vector>
// #include <stdexcept>
// #include <fstream>
// #include <cstring>

GLuint loadBMP(const char *imagepath) {
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    unsigned int width, height;
    std::vector<unsigned char> data;

    std::ifstream file(imagepath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open file: ") + imagepath);
    }

    file.read(reinterpret_cast<char*>(header), 54);
    if (file.gcount() != 54) {
        throw std::runtime_error("Not a correct BMP file: Couldn't read the header!");
    }

    if (header[0] != 'B' || header[1] != 'M') {
        throw std::runtime_error("Not a correct BMP file: Incorrect header signature!");
    }

    int headerField = *reinterpret_cast<int*>(&header[0x1E]);
    if (headerField != 0) {
        throw std::runtime_error("Not a correct BMP file: header[0x1E] is not 0!");
    }

    int bpp = *reinterpret_cast<int*>(&header[0x1C]);
    if (bpp != 24) {
        throw std::runtime_error("Not a correct BMP file: bpp is not 24!");
    }

    dataPos = *reinterpret_cast<int*>(&header[0x0A]);
    imageSize = *reinterpret_cast<int*>(&header[0x22]);
    width = *reinterpret_cast<int*>(&header[0x12]);
    height = *reinterpret_cast<int*>(&header[0x16]);

    if (imageSize == 0) {
        imageSize = width * height * 3;
    }
    if (dataPos == 0) {
        dataPos = 54;
    }

    data.resize(imageSize);
    file.seekg(dataPos, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), imageSize);
    file.close();

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}