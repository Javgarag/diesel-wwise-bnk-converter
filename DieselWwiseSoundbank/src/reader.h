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
		size_t SearchAddress(T pattern, long start_pos = 0, Header stop_header = Header::BKHD) // default BKHD will never be encountered since its at the start
		{
			PushCurrentPos();
			stream.seekg(0, std::ios::end);
			std::streamsize size = stream.tellg();
			PopLastPos();

			PushCurrentPos();
			stream.seekg(start_pos);

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
				else if (stop_header != Header::BKHD && current == stop_header) {
					break;
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
		std::string ReadNullTerminatedString();
		void CloseFile();

		Reader() = default;
		Reader(const std::filesystem::path& file_path);
	private:
		std::ifstream stream;
		std::stack<size_t> savedPositions;
	};
}