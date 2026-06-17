#pragma once
#include <fstream>
#include <filesystem>
#include <stack>

namespace Wwise {
	class Writer {
	public:
		template<typename T>
		void Write(const T& value, size_t size = sizeof(T))
		{
			stream.write(reinterpret_cast<const char*>(&value), size);
		}

		template<typename T>
		Writer& operator<<(const T& value)
		{
			Write(value);
			return *this;
		}

		void CloseFile();
		long Tell();
		void PushCurrentPos();
		void PopLastPos();
		void Seek(long address);
		Writer() = default;
		Writer(const std::filesystem::path& file_path);
	private:
		std::ofstream stream;
		std::stack<long> savedPositions;
	};
}