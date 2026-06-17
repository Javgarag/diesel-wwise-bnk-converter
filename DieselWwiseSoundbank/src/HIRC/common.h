#pragma once
#include "../globals.h"
#include "../reader.h"
#include "../writer.h"

#include <optional>
#include <variant>
#include <vector>
#include <array>

namespace Wwise {
	struct HIRCItemGeneric {
		uint8_t type;

		uint32_t size;
		long size_position = -1;

		size_t data_start;
		uint32_t item_id;

		void Convert(Writer& writer);
		void UpdateSize(Writer& writer);
		HIRCItemGeneric(Reader& reader);
	};

	struct HIRCUnknown {
		HIRCItemGeneric item_base;

		HIRCUnknown(Reader& reader);
	};

	// RTPC

	struct RTPCGraphPoint {
		float gp_from;
		float gp_to;
		CurveInterpolation interpolation;

		void Convert(Writer& writer);
		RTPCGraphPoint() = default;
		RTPCGraphPoint(Reader& reader);
	};

	struct RTPCGraph {
		uint16_t num_points;
		std::vector<RTPCGraphPoint> points;

		void Convert(Writer& writer);
		RTPCGraph() = default;
		RTPCGraph(Reader& reader);
	};

	struct RTPC {
		uint32_t id;

		// > 2013
		std::variant<RTPCType2015, RTPCType2022> rtpc_type;
		std::variant<RTPCAccum2015, RTPCAccum2022> rtpc_accum;

		std::variant<uint32_t, uint8_t> param_id;
		uint32_t rtpc_curve_id;

		CurveScaling scaling;
		RTPCGraph rtpc_graph;

		void Convert(Writer& writer);
		RTPC(Reader& reader);
	};

	struct InitialRTPC {
		uint16_t num_rtpc;
		std::vector<RTPC> rtpcs;

		void Convert(Writer& writer);
		InitialRTPC() = default;
		InitialRTPC(Reader& reader);
	};

	// End RTPC

	// Sound

	struct Plugin {
		PluginType type;
		PluginCompany company;

		void Convert(Writer& writer);
		Plugin(Reader& reader);
	};

	struct SourceBitsOld {
		bool is_language_specific : 1;
		bool has_source : 1;
		bool externally_supplied : 1;
		unsigned char : 5;
	};

	struct SourceBitsNew {
		bool is_language_specific : 1;
		bool prefetch : 1;
		unsigned char : 1;
		bool non_cachable : 1;
		unsigned char : 3;
		bool has_source : 1;
	};

	struct SourceData {
		Plugin plugin;
		std::variant<SourceTypeOld, SourceTypeNew> source_type;
		uint32_t source_id;

		uint32_t file_id = 0; // removed in 2015+
		uint32_t file_offset = 0;
		uint32_t in_memory_media_size = 0;

		std::variant<SourceBitsOld, SourceBitsNew> source_bits;

		// depending on plugin:
		uint32_t plugin_params_size = 0;
		std::vector<unsigned char> plugin_param_data;

		void Convert(Writer& writer);
		SourceData(Reader& reader);
	};

	// End Sound

	// Start Base-Parameters

	struct FXChunkFXParams {
		uint8_t fx_index;
		uint32_t fx_id;
		uint8_t is_share_set;
		uint8_t is_rendered;

		void Convert(Writer& writer);
		FXChunkFXParams(Reader& reader);
	};

	struct FXChunkMetadata {
		uint8_t fx_index;
		uint32_t fx_id;
		uint8_t is_share_set;

		FXChunkMetadata(Reader& reader);
	};

	struct ParameterNodeFXParams {
		uint8_t is_override_parent_fx;
		uint8_t num_fx;
		std::optional<uint8_t> bits_fx_bypass;
		std::optional<std::vector<FXChunkFXParams>> fx_chunks;

		void Convert(Writer& writer);
		ParameterNodeFXParams(Reader& reader);
	};

	struct ParameterNodeMetadataParams {
		uint8_t is_override_parent_fx;
		uint8_t num_fx;
		std::optional<uint8_t> bits_fx_bypass;
		std::optional<std::vector<FXChunkMetadata>> fx_chunks;

		ParameterNodeMetadataParams(Reader& reader);
	};

	struct ParameterNodeByBitVector {
		bool priority_override_parent : 1;
		bool priority_apply_dist_factor : 1;
		bool override_midi_events_behavior : 1;
		bool override_midi_note_tracking : 1;
		bool enable_midi_note_tracking : 1;
		bool is_midi_break_loop_on_note_off : 1;
		unsigned char : 2;
	};

	struct PropertyBundle {
		uint8_t num_properties;
		std::variant<std::vector<AkPropID_2013>, std::vector<AkPropID_2015>, std::vector<AkPropID_2022>> property_ids;
		std::vector<float> property_values; // unions, since stuff like Volume is stored as float

		void Convert(Writer& writer);
		void AddNewProperty(int propId, float propValue);

		PropertyBundle() = default;
		PropertyBundle(Reader& reader);
	};

	struct RangedProperty {
		float min; // union too
		float max;

		void Convert(Writer& writer);
		RangedProperty() = default;
		RangedProperty(Reader& reader);
	};

	struct RangedModifierPropertyBundle {
		uint8_t num_properties;
		std::variant<std::vector<AkPropID_2013>, std::vector<AkPropID_2015>, std::vector<AkPropID_2022>> property_ids;
		std::vector<RangedProperty> property_values;

		void Convert(Writer& writer);
		RangedModifierPropertyBundle() = default;
		RangedModifierPropertyBundle(Reader& reader);
	};

	struct ParameterNodeInitialParams {
		PropertyBundle property_bundle;
		RangedModifierPropertyBundle ranged_modifier_property_bundle;

		void Convert(Writer& writer);
		ParameterNodeInitialParams() = default;
		ParameterNodeInitialParams(Reader& reader);
	};

	struct BitPositioning2013 {
		bool positioning_info_override_parent : 1;
		bool has_listener_relative_routing : 1;
		unsigned char : 6;
	};

	struct BitPositioning2015 {
		bool positioning_info_override_parent : 1;
		bool unknown2d_next_flag : 1;
		bool unknown2d : 1;
		bool is_3d_positioning_available : 1; // has_3d
		unsigned char : 3;
	};

	struct BitPositioning2022 {
		bool positioning_info_override_parent : 1;
		bool has_listener_relative_routing : 1; // has_3d
		SpeakerPanningType panner_type : 2;
		unsigned char : 1;
		ThreeDPositionType position_3d_type : 2;
		unsigned char : 1;
	};

	struct PathVertex {
		float x;
		float y;
		float z;
		int32_t duration;

		void Convert(Writer& writer);
		PathVertex() = default;
		PathVertex(Reader& reader);
	};

	struct PathListItemOffset {
		uint32_t vertices_offset;
		uint32_t num_vertices;

		void Convert(Writer& writer);
		PathListItemOffset() = default;
		PathListItemOffset(Reader& reader);
	};

	struct AutomationParam3D {
		float fXRange;
		float fYRange;

		// + 2013
		float fZRange;

		void Convert(Writer& writer);
		AutomationParam3D() = default;
		AutomationParam3D(Reader& reader);
	};

	struct Bits3D2015 {
		SpatializationMode spatialization_mode : 1;
		unsigned char : 2;
		bool hold_emitter_pos_and_orient : 1;
		bool hold_listener_orient : 1;
		unsigned char : 3;
	};

	struct Bits3D2022 {
		SpatializationMode spatialization_mode : 2; // adds PositionAndOrientation
		unsigned char : 1;
		bool enable_attenuation : 1;
		bool hold_emitter_pos_and_orient : 1; // default false
		bool hold_listener_orient : 1; // default false
		bool enable_diffraction : 1; // default false (introduced 2017+)
		unsigned char : 1;
	};

	struct PositioningParams {
		std::variant<BitPositioning2013, BitPositioning2015, BitPositioning2022> bits_positioning;

		// if it has positioning by overriding parent:

		// START 2013
		std::optional<uint8_t> is_2d_positioning_available;
		std::optional<uint8_t> is_3d_positioning_available;

		// if 2d positioning
		std::optional<uint8_t> positioning_enable_panner;
		// if 3d positioning
		std::optional<PositioningType> type;
		std::optional<uint32_t> attenuation_id;
		std::optional<uint8_t> is_spatialized; // "enable spatialization"

		// if type = Positioning2D "game defined";
		std::optional<uint8_t> is_dynamic; // "update at each frame"
		// else "user defined"
		std::optional<uint8_t> is_looping;
		std::optional<uint8_t> follow_orientation; // "follow listener orientation"
		// END 2013

		std::optional<std::variant<uint8_t, uint32_t>> path_mode; // AkPathMode
		std::optional<int32_t> transition_time;

		// 2015, 2022
		std::optional<std::variant<Bits3D2015, Bits3D2022>> bits_3d;

		// common to all versions, only if 3d positioning:
		std::optional<uint32_t> num_vertices;
		std::vector<PathVertex> vertices;

		std::optional<uint32_t> num_playlist_items;
		std::vector<PathListItemOffset> playlist_items;
		std::vector<AutomationParam3D> automation_params_3d;

		void Convert(Writer& writer);
		PositioningParams() = default;
		PositioningParams(Reader& reader);
	};

	struct AuxParamsByBitVector {
		bool override_game_aux_sends : 1;
		bool use_game_aux_sends : 1;
		bool override_user_aux_sends : 1;
		bool has_aux : 1;
		bool override_reflections_aux_bus : 1; // false by default on older stuff 
		unsigned char : 3;
	};

	struct AuxParams {
		// 2013
		uint8_t override_game_aux_sends;
		uint8_t use_game_aux_sends;
		uint8_t override_user_aux_sends;
		uint8_t has_aux;

		// > 2013
		AuxParamsByBitVector by_bit_vector;
		std::array<uint32_t, 4> aux_id;

		// 2022
		uint32_t reflections_aux_bus;

		void Convert(Writer& writer);
		AuxParams() = default;
		AuxParams(Reader& reader);
	};

	struct AdvSettingsByBitVector1 {
		bool kill_newest : 1;
		bool use_virtual_behavior : 1;
		unsigned char : 1;
		bool ignore_parent_max_num_inst : 1;
		bool is_vvoices_opt_override_parent : 1;
		unsigned char : 3;
	};

	struct AdvSettingsByBitVector2 {
		bool override_hdr_envelope : 1;
		bool override_analysis : 1;
		bool normalize_loudness : 1;
		bool enable_envelope : 1;
		unsigned char : 4;
	};

	struct AdvSettingsParams {
		// 2013
		uint8_t kill_newest;
		uint8_t use_virtual_behavior;
		uint8_t is_global_limit;
		uint8_t is_max_num_inst_override_parent;
		uint8_t is_vvoices_opt_override_parent;
		uint8_t override_hdr_envelope;
		uint8_t override_analysis;
		uint8_t normalize_loudness;
		uint8_t enable_envelope;

		// > 2013
		AdvSettingsByBitVector1 by_bit_vector_1;
		AdvSettingsByBitVector2 by_bit_vector_2;

		// Both
		uint8_t virtual_queue_behavior; // AkVirtualQueueBehavior
		uint16_t max_num_instance;
		uint8_t below_threshold_behavior; // AkBelowThresholdBehavior

		void Convert(Writer& writer);
		AdvSettingsParams() = default;
		AdvSettingsParams(Reader& reader);
	};

	struct State {
		uint32_t state_id;
		uint32_t state_instance_id;

		void Convert(Writer& writer);
		State(Reader& reader);
	};

	struct StateGroup {
		uint32_t state_group_id; // hashable
		uint8_t state_sync_type;
		std::variant<uint16_t, uint32_t> num_states; // depends on versioning
		std::vector<State> states;

		void Convert(Writer& writer);
		StateGroup(Reader& reader);
	};

	struct StatePropertyNew {
		uint32_t property_id; //AkRTPC_ParameterID
		uint8_t accum_type; //AkRtpcAccum

		// 2022
		uint8_t in_Db;

		void Convert(Writer& writer);
		StatePropertyNew(Reader& reader);
	};

	struct ParameterNodeStateChunkOld {
		uint32_t num_state_groups;
		std::vector<StateGroup> groups;

		void Convert(Writer& writer);
		ParameterNodeStateChunkOld() = default;
		ParameterNodeStateChunkOld(Reader& reader);
	};

	struct ParameterNodeStateChunkNew {
		uint8_t num_state_props;
		std::vector<StatePropertyNew> state_props;

		uint8_t num_state_groups;
		std::vector<StateGroup> state_groups;

		void Convert(Writer& writer);
		ParameterNodeStateChunkNew() = default;
		ParameterNodeStateChunkNew(Reader& reader);
	};

	struct BaseParams {
		ParameterNodeFXParams initial_fx_params;

		// 2022
		std::optional<ParameterNodeMetadataParams> metadata_params;

		// > 2013
		std::optional<uint8_t> override_attachment_params;

		uint32_t override_bus_id;
		uint32_t direct_parent_id;

		// == 2013
		std::optional<uint8_t> priority_override_parent;
		std::optional<uint8_t> priority_apply_dist_factor;

		// > 2013
		std::optional<ParameterNodeByBitVector> by_bit_vector;

		ParameterNodeInitialParams parameter_node_initial_params;
		PositioningParams positioning_params;
		AuxParams auxiliary_params;
		AdvSettingsParams adv_settings_params;

		std::variant<ParameterNodeStateChunkOld, ParameterNodeStateChunkNew> state_chunk;
		InitialRTPC initial_rtpc;

		// < 2022 (if feedback in bank)
		std::optional<uint32_t> feedback_bus_id;

		void Convert(Writer& writer);
		BaseParams(Reader& reader);
	};

	// End Base-Parameters

	// Other Shared

	struct Children {
		uint32_t num_children;
		std::vector<uint32_t> child_ids;

		void Convert(Writer& writer);
		Children() = default;
		Children(Reader& reader);
	};
}