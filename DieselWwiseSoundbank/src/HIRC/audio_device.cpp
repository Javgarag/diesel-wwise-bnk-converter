#include "audio_device.h"

namespace Wwise {
	HIRCAudioDevice::HIRCAudioDevice(Reader& reader) 
		: item_base(reader),
		fx_base(reader)
	{
		// EffectSlots (+140)
		reader.Read(&count_fx);
		if (count_fx > 0) {
			bits_fx_bypass = reader.Read<uint8_t>();
			fx_chunks.emplace();
			for (uint32_t i = 0; i < count_fx; i++) {
				fx_chunks.value().push_back(FXChunkFXParams(reader));
			}
		}

		// safety padding
		reader.Seek(item_base.data_start + item_base.size);
	}

	void HIRCAudioDevice::CreateDefaults(Writer& writer) {
		HIRCItemGeneric item_base_no_output{};
		item_base_no_output.type = (uint8_t)HIRCItemTypeNew::AudioDevice;
		item_base_no_output.item_id = 2317455096;
		item_base_no_output.Convert(writer);

		Plugin no_output_plugin{};
		no_output_plugin.id = PluginID::No_Output;
		no_output_plugin.Convert(writer);

		writer << (uint32_t)0; // no parameter size

		writer << (uint8_t)0; // num_bank_data 0 
		writer << (uint16_t)0; // num_rtpc 0 
		writer << (uint8_t)0; // num_props 0 
		writer << (uint8_t)0; // num_groups 0 
		writer << (uint16_t)0; // num_values 0 
		writer << (uint8_t)0; // count_fx 0 

		item_base_no_output.UpdateSize(writer);

		HIRCItemGeneric item_base_system{};
		item_base_system.type = (uint8_t)HIRCItemTypeNew::AudioDevice;
		item_base_system.item_id = 3859886410;
		item_base_system.Convert(writer);

		Plugin system_plugin{};
		system_plugin.id = PluginID::System;
		system_plugin.Convert(writer);

		// observed data
		PluginParameters system_parameters{};
		system_parameters.size = 12;
		system_parameters.data = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x01, 0x20, 0x0};
		system_parameters.Convert(writer);

		writer << (uint8_t)0; // num_bank_data 0 
		writer << (uint16_t)0; // num_rtpc 0 
		writer << (uint8_t)0; // num_props 0 
		writer << (uint8_t)0; // num_groups 0 
		writer << (uint16_t)0; // num_values 0 
		writer << (uint8_t)0; // count_fx 0 

		item_base_system.UpdateSize(writer);
	}
}