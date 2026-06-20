#pragma once
#include "common.h"

namespace Wwise {
	// Out of the three versions, this only exists on 2022; Wwise needs some of them for conversion of the init.bnk soundbank.
	// When migrating a project two Audio Devices are automatically created:
	//	- "System" with an FNV of 3859886410 and a Plugin ID of 0x00AE0007 "System", with a parameter data section of size 12
	//	- "No_Output" with an FNV of 2317455096 and a Plugin ID of 0x00B50007 "No_Output", with no parameter data section whatsoever (size 0)
	// It's easy enough to append two additional AudioDevices to the start of the object list since their defaults are fully known

	struct HIRCAudioDevice {
		HIRCItemGeneric item_base;
		FXBase fx_base;
		
		// EffectSlots (+140)
		uint8_t count_fx;
		std::optional<uint8_t> bits_fx_bypass;
		std::optional<std::vector<FXChunkFXParams>> fx_chunks;

		HIRCAudioDevice() = default;
		HIRCAudioDevice(Reader& reader);
		static void CreateDefaults(Writer& writer);
	};
}