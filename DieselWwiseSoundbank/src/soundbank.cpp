#include "soundbank.h"
#include <iostream>

// todo: add optionals to auxparams, advsettingsaparams, statechunk, initial_rtpc

namespace Wwise {
	Soundbank::Soundbank(const std::filesystem::path& file_path)
	{
		reader = Reader(file_path);

		// BKHD		
		//std::cout << "Reading: BKHD (soundbank header)" << std::endl;
		bank_header = BKHD(reader);
		if (bank_header.section_info.header != Header::BKHD) {
			std::cerr << "ERROR: File is not a Wwise Soundbank (.bnk)!" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		switch (VERSION) {
		case BankVersion::V2013:
			break;
		case BankVersion::V2015:
			break;
		case BankVersion::V2022:
			break;
		default:
			std::cerr << "ERROR: Unsupported Soundbank version! Supported versions: 2013 (88), 2015 (113), 2022 (145)" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		// STMG (init.bnk)
		//std::cout << "Reading: STMG (global settings)" << std::endl;
		if (long stmg_address = reader.SearchAddress(Header::STMG, reader.Tell(), Header::DIDX)) {
			reader.Seek(stmg_address);
			global_settings = STMG(reader);
		}

		// DIDX
		//std::cout << "Reading: DIDX (data index)" << std::endl;
		if (long didx_address = reader.SearchAddress(Header::DIDX, reader.Tell(), Header::DATA)) {
			reader.Seek(didx_address);
			data_index = DIDX(reader);
		}

		// DATA
		//std::cout << "Reading: DATA (embedded sounds)" << std::endl;
		if (long data_address = reader.SearchAddress(Header::DATA, reader.Tell(), Header::HIRC)) {
			reader.Seek(data_address);
			sound_data = DATA(reader);
		}

		// HIRC
		//std::cout << "Searching for HIRC header..." << std::endl;
		long hirc_address = reader.SearchAddress(Header::HIRC, reader.Tell());
		if (!hirc_address) {
			std::cerr << "ERROR: Soundbank has no readable objects!" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		reader.Seek(hirc_address);
		objects = HIRC(reader);

		// ENVS
		//std::cout << "Searching for ENVS header..." << std::endl;
		if (long envs_address = reader.SearchAddress(Header::ENVS, reader.Tell(), Header::STID)) {
			reader.Seek(envs_address);
			enviroment_settings = ENVS(reader);
		}

		// STID
		//std::cout << "Searching for STID header..." << std::endl;
		if (long stid_address = reader.SearchAddress(Header::STID, reader.Tell())) {
			reader.Seek(stid_address);
			string_mapping = STID(reader);
		}

		reader.CloseFile();
		std::cout << "Successful parsing of version " << (int)VERSION << std::endl;
	};

	bool Soundbank::Convert(BankVersion new_version, const std::filesystem::path& file_path) {
		CONVERT_VERSION = new_version;
		if (CONVERT_VERSION != BankVersion::V2013 && CONVERT_VERSION != BankVersion::V2015 && CONVERT_VERSION != BankVersion::V2022) {
			std::cerr << "ERROR: Unsupported converted version; supported versions: 2013 (88), 2015 (113), 2022 (145)" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		if (CONVERT_VERSION <= VERSION) {
			std::cerr << "ERROR: Conversion version cannot be lower than or equal to the current version!" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		writer = Writer(file_path);

		bank_header.Convert(writer);

		if (global_settings) {
			global_settings.value().Convert(writer);
		}

		if (data_index) {
			data_index.value().Convert(writer);
		}

		if (sound_data) {
			sound_data.value().Convert(writer);
		}

		objects.Convert(writer);

		if (enviroment_settings) {
			enviroment_settings.value().Convert(writer);
		}

		if (string_mapping) {
			string_mapping.value().Convert(writer);
		}

		writer.CloseFile();

		std::cout << "Successful conversion to version " << (int)new_version << std::endl;
		return true;
	}
} 