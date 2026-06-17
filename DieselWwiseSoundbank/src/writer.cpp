#include "writer.h"
#include <filesystem>

namespace Wwise {
	Writer::Writer(const std::filesystem::path& file_path) 
		: stream(file_path, std::ios::out | std::ios::binary)
	{
		if (!stream.is_open()) {
			throw std::runtime_error("Failed to open file");
		}
	}

	long Writer::Tell() {
		return stream.tellp();
	};

	void Writer::PushCurrentPos() {
		savedPositions.push(stream.tellp());
	};

	void Writer::PopLastPos() {
		stream.seekp(savedPositions.top());
		savedPositions.pop();
	};

	void Writer::Seek(long address) {
		stream.seekp(address);
	};

	void Writer::CloseFile() {
		stream.flush();
		stream.close();
	}
}