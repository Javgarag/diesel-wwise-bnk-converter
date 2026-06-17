#include "music_segment.h"

namespace Wwise {
    MusicMarker::MusicMarker(Reader& reader) {
        reader.Read(&id);
        reader.Read(&position);
        if (VERSION < BankVersion::V2022) {
            string_size = reader.Read<uint32_t>();
            marker_name.emplace();
            for (uint32_t i = 0; i < string_size; i++) {
                marker_name.value().push_back(reader.Read<char>());
            }
        }
        else {
            marker_name_null_terminated = reader.ReadNullTerminatedString();
        }
    }

    void MusicMarker::Convert(Writer& writer) {
        writer << id;
        writer << position;

        if (CONVERT_VERSION == BankVersion::V2022) {
            // convert string to null-terminated
            for (uint32_t i = 0; i < string_size.value(); i++) {
                writer << marker_name.value()[i];
            }
            writer << (uint8_t)0; // terminator
        }
        else {
            writer << string_size.value();
            for (uint32_t i = 0; i < string_size; i++) {
                writer << marker_name.value()[i];
            }
        }
    }

    HIRCMusicSegment::HIRCMusicSegment(Reader& reader) 
        : item_base(reader),
        node_params(reader)
    {
        reader.Read(&duration);
        reader.Read(&num_markers);
        for (uint32_t i = 0; i < num_markers; i++) {
            markers.push_back(MusicMarker(reader));
        }
    }

    void HIRCMusicSegment::Convert(Writer& writer) {
        item_base.Convert(writer);

        node_params.Convert(writer);
        writer << duration;
        writer << num_markers;
        for (uint32_t i = 0; i < num_markers; i++) {
            markers[i].Convert(writer);
        }

        item_base.UpdateSize(writer);
    }
    
}