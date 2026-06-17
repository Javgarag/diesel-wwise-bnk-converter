#include <iostream>
#include <filesystem>
#include "soundbank.h"
#include "ak_types.h"

int main()
{
#ifdef NDEBUG
    std::filesystem::path path;
    std::cin >> path;
    Wwise::Soundbank bank(path);
#else
    std::filesystem::path path = "./input_soundbank.bnk";
    Wwise::Soundbank bank(path);
    bank.Convert(Wwise::BankVersion::V2022, "./output_soundbank.bnk");
#endif
}