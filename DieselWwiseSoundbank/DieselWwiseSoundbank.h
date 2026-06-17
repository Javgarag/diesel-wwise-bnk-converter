#pragma once

#ifdef DIESELWWISESOUNDBANK_EXPORTS
#define DIESELWWISESOUNDBANK_API __declspec(dllexport)
#else
#define DIESELWWISESOUNDBANK_API __declspec(dllimport)
#endif