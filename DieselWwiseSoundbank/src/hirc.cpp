#include "hirc.h"

namespace Wwise {
	HIRC::HIRC(Reader& reader) {
		std::cout << "Reading: HIRC (Wwise objects)" << std::endl;
		section_info = Section(reader);
		reader.Read(&num_items);

		// for every item, insert its variant into "items".
		for (uint32_t i = 0; i < num_items; i++) {
			reader.PushCurrentPos();
			uint8_t item_type = reader.Read<uint8_t>();
			std::cout << "\tItem #" << i + 1 << ": type " << (int)item_type << std::endl;
			reader.PopLastPos();

			if (VERSION != BankVersion::V2022) {
				switch ((HIRCItemTypeOld)(item_type)) {
				case HIRCItemTypeOld::Attenuation:
					items.push_back(HIRCAttenuation(reader));
					break;
				case HIRCItemTypeOld::Sound:
					items.push_back(HIRCSound(reader));
					break;
				case HIRCItemTypeOld::Action:
					items.push_back(HIRCActionBase(reader));
					break;
				case HIRCItemTypeOld::Event:
					items.push_back(HIRCEvent(reader));
					break;
				case HIRCItemTypeOld::RandomOrSequenceContainer:
					items.push_back(HIRCRandomSequenceController(reader));
					break;
				case HIRCItemTypeOld::ActorMixer:
					items.push_back(HIRCActorMixer(reader));
					break;
				case HIRCItemTypeOld::LayerContainer:
					items.push_back(HIRCLayerContainer(reader));
					break;
				case HIRCItemTypeOld::SwitchContainer:
					items.push_back(HIRCSwitchContainer(reader));
					break;
				case HIRCItemTypeOld::FxShareSet:
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeOld::FxCustom:
					items.push_back(HIRCFxShareSet(reader));
					break;
				default:
					std::cout << "\t\tUnknown HIRC Object type!" << std::endl;
					items.push_back(HIRCUnknown(reader));
				}
			}
			else {
				switch ((HIRCItemTypeNew)(item_type)) {
				case HIRCItemTypeNew::Attenuation:
					items.push_back(HIRCAttenuation(reader));
					break;
				case HIRCItemTypeNew::Sound:
					items.push_back(HIRCSound(reader));
					break;
				case HIRCItemTypeNew::Action:
					items.push_back(HIRCActionBase(reader));
					break;
				case HIRCItemTypeNew::Event:
					items.push_back(HIRCEvent(reader));
					break;
				case HIRCItemTypeNew::RandomOrSequenceContainer:
					items.push_back(HIRCRandomSequenceController(reader));
					break;
				case HIRCItemTypeNew::ActorMixer:
					items.push_back(HIRCActorMixer(reader));
					break;
				case HIRCItemTypeNew::LayerContainer:
					items.push_back(HIRCLayerContainer(reader));
					break;
				case HIRCItemTypeNew::SwitchContainer:
					items.push_back(HIRCSwitchContainer(reader));
					break;
				case HIRCItemTypeNew::FxShareSet:
					items.push_back(HIRCFxShareSet(reader));
					break;
				case HIRCItemTypeNew::FxCustom:
					items.push_back(HIRCFxShareSet(reader));
					break;
				default:
					std::cout << "Unknown HIRC Object type!" << std::endl;
					items.push_back(HIRCUnknown(reader));
				}
			}
		}
	}

	void HIRC::Convert(Writer& writer) {
		section_info.Convert(writer);
		writer << num_items;

		// hand off conversion to individual objects

		for (uint32_t i = 0; i < num_items; i++) {
			std::cout << "#" << i + 1 << std::endl << "\t";

			if (i + 1 == 124124) {
				std::cout << "break";
			}

			std::visit(overload{
				[&](HIRCAttenuation& item) {
					std::cout << "Converting Attenuation" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCSound& item) {
					std::cout << "Converting Sound" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCActionBase& item) {
					std::cout << "Converting Action" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCEvent& item) {
					std::cout << "Converting Event" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCRandomSequenceController& item) {
					std::cout << "Converting Random/Sequence Container" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCActorMixer& item) {
					std::cout << "Converting Actor Mixer" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCLayerContainer& item) {
					std::cout << "Converting Layer Container" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCSwitchContainer& item) {
					std::cout << "Converting Switch Container" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCFxShareSet& item) {
					std::cout << "Converting FX Share Set / FX Custom" << std::endl;
					item.Convert(writer);
				},
				[&](HIRCUnknown& item) {
					throw std::exception("Unable to convert unknown item type!");
				},
				[&](auto& item)
				{
					std::cout << "Unhandled type" << std::endl;
				}
			}, items[i]);
		}

		section_info.UpdateSize(writer);
	}
}