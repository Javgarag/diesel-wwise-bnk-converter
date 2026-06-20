#pragma once
#include "common.h"

namespace Wwise {
	struct BusFlags_2015 {
		bool main_output_hierarchy : 1;
		bool is_background_music : 1;
		unsigned char : 6;
	};

	struct BusFlags2_2015 {
		bool kill_newest : 1;
		bool use_virtual_behavior : 1;
		unsigned char : 6;
	};

	struct BusFlags_2022 {
		bool kill_newest : 1;
		bool use_virtual_behavior : 1;
		bool is_max_num_instance_override_parent : 1;
		bool is_background_music : 1;
		unsigned char : 4;
	};

	struct BusHDRFlags {
		bool is_hdr_bus : 1;
		bool hdr_release_mode_exponential : 1;
		unsigned char : 6;
	};

	struct ChannelFormat { // 2013. PD2 only makes use of front_left and front_right, given the bus even uses this. On 2013, this is only 16 bits.
		bool front_left : 1;
		bool front_right : 1;
		bool front_center : 1;
		bool low_frequency_effects : 1;
		bool back_left : 1;
		bool back_right : 1;
		bool front_left_center : 1;
		bool front_right_center : 1;
		bool back_center : 1;
		bool side_left : 1;
		bool side_right : 1;
		bool top_center : 1;
		bool top_front_left : 1;
		bool top_front_center : 1;
		bool top_front_right : 1;
		bool top_back_left : 1;
		bool top_back_center : 1;
		bool top_back_right : 1;
		unsigned char : 2;
	};

	struct BusChannelConfig {
		uint8_t num_channels : 8; // for 2015, if num_channels != 0, config_type == 1, else 0. corresponds to the literal number of channels used (see ChannelFormat, above)
		unsigned char config_type : 4;
		uint32_t channel_mask : 20; // ChannelFormat
	};

	struct BusDuckInfo {
		uint32_t bus_id;
		float duck_volume;
		int32_t fade_out_time;
		int32_t fade_in_time;
		uint8_t fade_curve;
		std::variant<AkPropID_2013, AkPropID_2015, AkPropID_2022> target_prop_id;

		void Convert(Writer& writer);
		BusDuckInfo() = default;
		BusDuckInfo(Reader& reader);
	};

	struct BusInitialFXParams {
		// EffectSlots (+140)
		uint8_t count_fx;
		std::optional<uint8_t> bits_fx_bypass;
		std::optional<std::vector<FXChunkFXParams>> fx_chunks;

		// +2013
		std::optional<uint32_t> fx_id_0;
		std::optional<uint8_t> is_shareset_0;

		void Convert(Writer& writer);
		BusInitialFXParams() = default;
		BusInitialFXParams(Reader& reader);
	};

	struct BusMetadataParams {
		uint8_t num_fx;
		std::optional<uint8_t> bits_fx_bypass;
		std::optional<std::vector<FXChunkMetadata>> fx_chunks;

		BusMetadataParams(Reader& reader);
	};
	
	struct HIRCBus {
		HIRCItemGeneric item_base;

		uint32_t override_bus_id;
		
		// 2022
		std::optional<uint32_t> device_share_set;
		
		PropertyBundle property_bundle;
		// 2013
		std::optional<uint8_t> positioning_enabled;
		std::optional<uint8_t> positioning_enable_panner;
		std::optional<uint8_t> kill_newest;
		std::optional<uint8_t> use_virtual_behavior;
		std::optional<uint8_t> is_max_num_instances_override_parent;
		std::optional<uint16_t> channel_config_raw; // for extracting number of channels used
		std::optional<uint8_t> unused1;
		std::optional<uint8_t> unused2;
		std::optional<uint8_t> is_hdr_bus;
		std::optional<uint8_t> hdr_release_mode_exponential;

		// 2015
		std::optional<BusFlags2_2015> flags_2_2015;

		// 2022
		std::optional<PositioningParams> positioning_params;
		std::optional<AuxParams> aux_params;
		 
		// 2015 and 2022
		std::optional<std::variant<BusFlags_2015, BusFlags_2022>> flags;
		std::optional<BusHDRFlags> hdr_flags;

		// all
		uint16_t max_num_instances;
		std::variant<ChannelFormat, BusChannelConfig> channel_config; // ChannelFormat for 2013, BusChannelConfig for others

		int32_t recovery_time;
		float max_duck_volume;
		uint32_t num_ducks;
		std::vector<BusDuckInfo> ducks;

		BusInitialFXParams fx_params;

		// +2013
		std::optional<uint8_t> override_attachment_params;
		// 2022
		std::optional<BusMetadataParams> metadata_params;

		InitialRTPC initial_rtpc;

		std::variant<ParameterNodeStateChunkOld, ParameterNodeStateChunkNew> state_chunk;

		void Convert(Writer& writer);
		HIRCBus() = default;
		HIRCBus(Reader& reader);
	};
}