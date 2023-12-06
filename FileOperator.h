#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Serializer {
public:
	struct dataChunk {
		void* data;
		int sizeInBytes;
	};
	std::vector<dataChunk> dataChunks;

	virtual void Write(std::string name) = 0;
	virtual void Read(std::string name) = 0;

	void Serialize(std::string& name) {
		std::ofstream outputFile(name, std::ios::binary);
		if (outputFile.is_open()) {
			for (dataChunk dc: dataChunks) {
				outputFile.write((const char*)dc.data, dc.sizeInBytes);
			}
			outputFile.close();
		}
		else {
			std::cout << "Error opening file to be written in!\n";
		}
	}
	void Deserialize(std::string& name) {
		std::ifstream inputFile(name, std::ios::binary);
		if (inputFile.is_open()) {
			for (dataChunk dc : dataChunks) {
				inputFile.read((char*)dc.data, dc.sizeInBytes);
			}
			inputFile.close();
		}
		else {
			std::cout << "Error opening file to be read from!\n";
		}
	}
};