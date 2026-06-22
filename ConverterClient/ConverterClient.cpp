#include <iostream>
#include <filesystem>
#include "soundbank.h"
#include "ak_types.h"

std::string find_option_argument(int argc, char* argv[], std::string option) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == option) {
            try {
                return argv[i + 1];
            }
            catch (...) {
                std::cout << "\tUsage: <.bnk input file> [-o output_file] [-v end_version]" << std::endl;
                std::cerr << "Malformed option: " << option << std::endl;
                std::exit(EXIT_FAILURE);
            }
        }
    }

    return "";
}

int main(int argc, char* argv[]) {
#ifdef NDEBUG
    if (argc < 2) {
        std::cerr << "Usage: <.bnk input file> [-o output_file] [-v end_version]" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::filesystem::path path = argv[1];
    Wwise::Soundbank bank(path);

    int version;
    if (find_option_argument(argc, argv, "-v") != "") {
        version = std::stoi(find_option_argument(argc, argv, "-v"));
    }
    else {
        std::cout << "\nVersion to convert to (2015 == '113', 2022 = '145'): ";
        std::cin >> version;
    }

    std::filesystem::path output_path;
    if (find_option_argument(argc, argv, "-o") != "") {
        output_path = find_option_argument(argc, argv, "-o");
    }
    else {
        std::cout << "\nOutput path (with extension): ";
        std::cin >> output_path;
    }

    bank.Convert((Wwise::BankVersion)version, output_path);
#else
    std::filesystem::path path = "D:\\GitHub\\diesel-wwise-bnk-version-converter\\x64\\Debug\\input_soundbank.bnk";
    Wwise::Soundbank bank(path);
    bank.Convert(Wwise::BankVersion::V2022, "D:\\GitHub\\diesel-wwise-bnk-version-converter\\x64\\Debug\\output_soundbank.bnk");
#endif
}