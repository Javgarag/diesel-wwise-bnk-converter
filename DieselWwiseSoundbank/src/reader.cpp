#include "reader.h"
#include "ak_types.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stack>

namespace Wwise {
	Reader::Reader(const std::filesystem::path& file_path)
		: stream(file_path, std::ios::in | std::ios::binary)
	{
		if (!stream.is_open()) {
			throw std::runtime_error("Failed to open file");
		}
	};

	size_t Reader::Tell() {
		return stream.tellg();
	};

	void Reader::PushCurrentPos() {
		savedPositions.push(stream.tellg());
	};

	void Reader::PopLastPos() {
		stream.seekg(savedPositions.top());
		savedPositions.pop();
	};

	void Reader::Seek(size_t address) {
		stream.seekg(address);
	};

	void Reader::CloseFile() {
		stream.close();
	}
};