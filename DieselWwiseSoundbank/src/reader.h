#pragma once
#include "ak_types.h"
#include <cstdint>
#include <fstream>
#include <stack>

namespace Wwise {
	class Reader {
	public:
		template<typename T>
		void Read(T* value, size_t size = sizeof(T))
		{
			stream.read(reinterpret_cast<char*>(value), size);
		}

		template<typename T>
		T Read(size_t size = sizeof(T))
		{
			T value;
			stream.read(reinterpret_cast<char*>(&value), size);
			return value;
		}

		template<typename T>
		size_t SearchAddress(T pattern)
		{
			PushCurrentPos();
			stream.seekg(0, std::ios::end);
			std::streamsize size = stream.tellg();
			PopLastPos();

			PushCurrentPos();
			stream.seekg(0);

			while (true)
			{
				size_t pos = stream.tellg();

				T current;

				if (pos > (size - sizeof(current))) {
					break;
				}

				Read(&current);
				if (current == pattern)
				{
					PopLastPos();
					return pos;
				}
				stream.seekg(pos + 1);
			}

			PopLastPos();

			return 0;
		}

		size_t Tell();
		void PushCurrentPos();
		void PopLastPos();
		void Seek(size_t address);
		void CloseFile();

		Reader() = default;
		Reader(const std::filesystem::path& file_path);
	private:
		std::ifstream stream;
		std::stack<size_t> savedPositions;
	};
}