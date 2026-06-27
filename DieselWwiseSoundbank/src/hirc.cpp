#include "hirc.h"
#include <string>

namespace Wwise {
	auto print_verbose = [](std::string s) {
		if (VERBOSE_MODE) {
			std::cout << s;
		}
	};

	HIRC::HIRC(Reader& reader) {
		print_verbose("Reading: HIRC (Wwise objects)\n");
		section_info = Section(reader);
		reader.Read(&num_items);

		// for every item, insert its variant into "items".
		for (uint32_t i = 0; i < num_items; i++) {
			reader.PushCurrentPos();
			uint8_t item_type = reader.Read<uint8_t>();
			print_verbose("\tItem #" + std::to_string(i + 1) + ": ");
			reader.PopLastPos();

			if (VERSION != BankVersion::V2022) {
				switch ((HIRCItemTypeOld)(item_type)) {
				case HIRCItemTypeOld::Attenuation:
					print_verbose("Attenuation\n");
					items.push_back(HIRCAttenuation(reader));
					break;
				case HIRCItemTypeOld::Sound:
					print_verbose("Sound\n");
					items.push_back(HIRCSound(reader));
					break;
				case HIRCItemTypeOld::Action:
					print_verbose("Action\n");
					items.push_back(HIRCActionBase(reader));
					break;
				case HIRCItemTypeOld::Event:
					print_verbose("Event\n");
					items.push_back(HIRCEvent(reader));
					break;
				case HIRCItemTypeOld::RandomOrSequenceContainer:
					print_verbose("Random / Sequence Container\n");
					items.push_back(HIRCRandomSequenceController(reader));
					break;
				case HIRCItemTypeOld::ActorMixer:
					print_verbose("Actor Mixer\n");
					items.push_back(HIRCActorMixer(reader));
					break;
				case HIRCItemTypeOld::LayerContainer:
					print_verbose("Layer Container\n");
					items.push_back(HIRCLayerContainer(reader));
					break;
				case HIRCItemTypeOld::SwitchContainer:
					print_verbose("Switch Container\n");
					items.push_back(HIRCSwitchContainer(reader));
					break;
				case HIRCItemTypeOld::FxShareSet:
					print_verbose("FX Share Set\n");
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeOld::FxCustom:
					print_verbose("FX Custom\n");
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeOld::MusicTrack:
					print_verbose("Music Track\n");
					items.push_back(HIRCMusicTrack(reader));
					break;
				case HIRCItemTypeOld::MusicSegment:
					print_verbose("Music Segment\n");
					items.push_back(HIRCMusicSegment(reader));
					break;
				case HIRCItemTypeOld::MusicRandomOrSequence:
					print_verbose("Music Random / Sequence Container\n");
					items.push_back(HIRCMusicRandomSequenceController(reader));
					break;
				case HIRCItemTypeOld::MusicSwitch:
					print_verbose("Music Switch\n");
					items.push_back(HIRCMusicSwitch(reader));
					break;
				case HIRCItemTypeOld::Bus:
					print_verbose("Audio Bus\n");
					items.push_back(HIRCBus(reader));
					break;
				case HIRCItemTypeOld::AuxiliaryBus:
					print_verbose("Auxiliary Bus\n");
					items.push_back(HIRCBus(reader));
					break;
				default:
					print_verbose("Unknown! will be unable to convert successfully\n");
					items.push_back(HIRCUnknown(reader));
				}
			}
			else {
				switch ((HIRCItemTypeNew)(item_type)) {
				case HIRCItemTypeNew::Attenuation:
					print_verbose("Attenuation\n");
					items.push_back(HIRCAttenuation(reader));
					break;
				case HIRCItemTypeNew::Sound:
					print_verbose("Sound\n");
					items.push_back(HIRCSound(reader));
					break;
				case HIRCItemTypeNew::Action:
					print_verbose("Action\n");
					items.push_back(HIRCActionBase(reader));
					break;
				case HIRCItemTypeNew::Event:
					print_verbose("Event\n");
					items.push_back(HIRCEvent(reader));
					break;
				case HIRCItemTypeNew::RandomOrSequenceContainer:
					print_verbose("Random / Sequence Container\n");
					items.push_back(HIRCRandomSequenceController(reader));
					break;
				case HIRCItemTypeNew::ActorMixer:
					print_verbose("Actor Mixer\n");
					items.push_back(HIRCActorMixer(reader));
					break;
				case HIRCItemTypeNew::LayerContainer:
					print_verbose("Layer Container\n");
					items.push_back(HIRCLayerContainer(reader));
					break;
				case HIRCItemTypeNew::SwitchContainer:
					print_verbose("Switch Container\n");
					items.push_back(HIRCSwitchContainer(reader));
					break;
				case HIRCItemTypeNew::FxShareSet:
					print_verbose("FX Share Set\n");
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeNew::FxCustom:
					print_verbose("FX Custom\n");
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeNew::MusicTrack:
					print_verbose("Music Track\n");
					items.push_back(HIRCMusicTrack(reader));
					break;
				case HIRCItemTypeNew::MusicSegment:
					print_verbose("Music Segment\n");
					items.push_back(HIRCMusicSegment(reader));
					break;
				case HIRCItemTypeNew::MusicRandomOrSequence:
					print_verbose("Music Random / Sequence Container\n");
					items.push_back(HIRCMusicRandomSequenceController(reader));
					break;
				case HIRCItemTypeNew::MusicSwitch:
					print_verbose("Music Switch\n");
					items.push_back(HIRCMusicSwitch(reader));
					break;
				case HIRCItemTypeNew::AudioBus:
					print_verbose("Audio Bus\n");
					items.push_back(HIRCBus(reader));
					break;
				case HIRCItemTypeNew::AuxiliaryBus:
					print_verbose("Auxiliary Bus\n");
					items.push_back(HIRCBus(reader));
					break;
				case HIRCItemTypeNew::AudioDevice:
					print_verbose("Audio Device\n");
					items.push_back(HIRCAudioDevice(reader));
					break;
				default:
					print_verbose("Unknown! will be unable to convert successfully\n");
					items.push_back(HIRCUnknown(reader));
				}
			}
		}
	}

	void HIRC::Convert(Writer& writer) {
		section_info.Convert(writer);
		num_items_pos = writer.Tell();
		writer << num_items;

		// hand off conversion to individual objects

		for (uint32_t i = 0; i < num_items; i++) {
			print_verbose("#" + std::to_string(i + 1) + "\n\t");

			std::visit(overload{
				[&](HIRCAttenuation& item) {
					print_verbose("Converting Attenuation\n");
					item.Convert(writer);
				},
				[&](HIRCSound& item) {
					print_verbose("Converting Sound\n");
					item.Convert(writer);
				},
				[&](HIRCActionBase& item) {
					print_verbose("Converting Action\n");
					item.Convert(writer);
				},
				[&](HIRCEvent& item) {
					print_verbose("Converting Event\n");
					item.Convert(writer);
				},
				[&](HIRCRandomSequenceController& item) {
					print_verbose("Converting Random/Sequence Container\n");
					item.Convert(writer);
				},
				[&](HIRCActorMixer& item) {
					print_verbose("Converting Actor Mixer\n");
					item.Convert(writer);
				},
				[&](HIRCLayerContainer& item) {
					print_verbose("Converting Layer Container\n");
					item.Convert(writer);
				},
				[&](HIRCSwitchContainer& item) {
					print_verbose("Converting Switch Container\n");
					item.Convert(writer);
				},
				[&](HIRCFxShareSet& item) {
					print_verbose("Converting FX Share Set / FX Custom\n");
					item.Convert(writer);
				},
				[&](HIRCMusicTrack& item) {
					print_verbose("Converting Music Track\n");
					item.Convert(writer);
				},
				[&](HIRCMusicSegment& item) {
					print_verbose("Converting Music Segment\n");
					item.Convert(writer);
				},
				[&](HIRCMusicRandomSequenceController& item) {
					print_verbose("Converting Music Random / Sequence Container\n");
					item.Convert(writer);
				},
				[&](HIRCMusicSwitch& item) {
					print_verbose("Converting Music Switch\n");
					item.Convert(writer);
				},
				[&](HIRCBus& item) {
					print_verbose("Converting Bus (master/auxiliary)\n");
					if (i == 0 && CONVERT_VERSION == BankVersion::V2022) {
						print_verbose("\tDetected init.bnk bank; inserting default AudioDevices\n");
						HIRCAudioDevice::CreateDefaults(writer);
						this->UpdateItemCount(num_items + 2, writer);
					}
					item.Convert(writer);
				},
				[&](HIRCUnknown& item) {
					print_verbose("ERROR: Unable to convert unknown item type! Report?\n");
					std::exit(EXIT_FAILURE);
				},
				[&](auto& item) {
					print_verbose("Unhandled type\n");
				}
			}, items[i]);
		}

		section_info.UpdateSize(writer);
	}

	void HIRC::UpdateItemCount(uint32_t new_count, Writer& writer) {
		writer.PushCurrentPos();
		writer.Seek(num_items_pos);
		writer << new_count;
		writer.PopLastPos();
	}
}