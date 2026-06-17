#include "ak_types.h"

namespace Wwise {
    // Type Conversion
    RTPCType2022 ConvertType(RTPCType2015 t) {
        switch (t) {
        case RTPCType2015::GameParameter:
            return RTPCType2022::GameParameter;
        case RTPCType2015::MIDIParameter:
            return RTPCType2022::Modulator;
        case RTPCType2015::Modulator:
            return RTPCType2022::Modulator;
        }
    }

    RTPCAccum2022 ConvertType(RTPCAccum2015 t) {
        switch (t) {
        case RTPCAccum2015::Additive:
            return RTPCAccum2022::Additive;
        case RTPCAccum2015::Multiply:
            return RTPCAccum2022::Multiply;
        case RTPCAccum2015::Exclusive:
            return RTPCAccum2022::Exclusive;
        }
    }

    SourceTypeNew ConvertType(SourceTypeOld t) {
        switch (t) {
        case SourceTypeOld::Bank:
            return SourceTypeNew::Bank;
        case SourceTypeOld::Streaming:
            return SourceTypeNew::Streaming;
        case SourceTypeOld::PrefetchStreaming:
            return SourceTypeNew::PrefetchStreaming;
        }
    }

    AkPropID_2015 ConvertType(AkPropID_2013 t) {
        switch (t)
        {
        case AkPropID_2013::Volume:                  return AkPropID_2015::Volume;
        case AkPropID_2013::LFE:                     return AkPropID_2015::LFE;
        case AkPropID_2013::Pitch:                   return AkPropID_2015::Pitch;
        case AkPropID_2013::LPF:                     return AkPropID_2015::LPF;
        case AkPropID_2013::BusVolume:               return AkPropID_2015::BusVolume;
        case AkPropID_2013::Priority:                return AkPropID_2015::Priority;
        case AkPropID_2013::PriorityDistanceOffset:  return AkPropID_2015::PriorityDistanceOffset;
        case AkPropID_2013::Loop:                    return AkPropID_2015::Loop;
        case AkPropID_2013::FeedbackVolume:          return AkPropID_2015::FeedbackVolume;
        case AkPropID_2013::FeedbackLPF:             return AkPropID_2015::FeedbackLPF;
        case AkPropID_2013::MuteRatio:               return AkPropID_2015::MuteRatio;
        case AkPropID_2013::PAN_LR:                  return AkPropID_2015::PAN_LR;
        case AkPropID_2013::PAN_FR:                  return AkPropID_2015::PAN_FR;
        case AkPropID_2013::CenterPCT:               return AkPropID_2015::CenterPCT;
        case AkPropID_2013::DelayTime:               return AkPropID_2015::DelayTime;
        case AkPropID_2013::TransitionTime:          return AkPropID_2015::TransitionTime;
        case AkPropID_2013::Probability:             return AkPropID_2015::Probability;
        case AkPropID_2013::DialogueMode:            return AkPropID_2015::DialogueMode;
        case AkPropID_2013::UserAuxSendVolume0:      return AkPropID_2015::UserAuxSendVolume0;
        case AkPropID_2013::UserAuxSendVolume1:      return AkPropID_2015::UserAuxSendVolume1;
        case AkPropID_2013::UserAuxSendVolume2:      return AkPropID_2015::UserAuxSendVolume2;
        case AkPropID_2013::UserAuxSendVolume3:      return AkPropID_2015::UserAuxSendVolume3;
        case AkPropID_2013::GameAuxSendVolume:       return AkPropID_2015::GameAuxSendVolume;
        case AkPropID_2013::OutputBusVolume:         return AkPropID_2015::OutputBusVolume;
        case AkPropID_2013::OutputBusLPF:            return AkPropID_2015::OutputBusLPF;
        case AkPropID_2013::InitialDelay:            return AkPropID_2015::InitialDelay;
        case AkPropID_2013::HDRBusThreshold:         return AkPropID_2015::HDRBusThreshold;
        case AkPropID_2013::HDRBusRatio:             return AkPropID_2015::HDRBusRatio;
        case AkPropID_2013::HDRBusReleaseTime:       return AkPropID_2015::HDRBusReleaseTime;
        case AkPropID_2013::HDRBusGameParam:         return AkPropID_2015::HDRBusGameParam;
        case AkPropID_2013::HDRBusGameParamMin:      return AkPropID_2015::HDRBusGameParamMin;
        case AkPropID_2013::HDRBusGameParamMax:      return AkPropID_2015::HDRBusGameParamMax;
        case AkPropID_2013::HDRActiveRange:          return AkPropID_2015::HDRActiveRange;
        case AkPropID_2013::MakeUpGain:              return AkPropID_2015::MakeUpGain;
        case AkPropID_2013::LoopStart:               return AkPropID_2015::LoopStart;
        case AkPropID_2013::LoopEnd:                 return AkPropID_2015::LoopEnd;
        case AkPropID_2013::TrimInTime:              return AkPropID_2015::TrimInTime;
        case AkPropID_2013::TrimOutTime:             return AkPropID_2015::TrimOutTime;
        case AkPropID_2013::FadeInTime:              return AkPropID_2015::FadeInTime;
        case AkPropID_2013::FadeOutTime:             return AkPropID_2015::FadeOutTime;
        case AkPropID_2013::FadeInCurve:             return AkPropID_2015::FadeInCurve;
        case AkPropID_2013::FadeOutCurve:            return AkPropID_2015::FadeOutCurve;
        case AkPropID_2013::LoopCrossfadeDuration:   return AkPropID_2015::LoopCrossfadeDuration;
        case AkPropID_2013::CrossfadeUpCurve:        return AkPropID_2015::CrossfadeUpCurve;
        case AkPropID_2013::CrossfadeDownCurve:      return AkPropID_2015::CrossfadeDownCurve;
        }
    }

    AkPropID_2022 ConvertType_2013_to_2022(AkPropID_2013 t) {
        switch (t)
        {
        case AkPropID_2013::Volume:                  return AkPropID_2022::Volume;
        case AkPropID_2013::LFE:                     return AkPropID_2022::LFE;
        case AkPropID_2013::Pitch:                   return AkPropID_2022::Pitch;
        case AkPropID_2013::LPF:                     return AkPropID_2022::LPF;
        case AkPropID_2013::BusVolume:               return AkPropID_2022::BusVolume;
        case AkPropID_2013::Priority:                return AkPropID_2022::Priority;
        case AkPropID_2013::PriorityDistanceOffset:  return AkPropID_2022::PriorityDistanceOffset;
        case AkPropID_2013::Loop:                    return AkPropID_2022::Loop;
        case AkPropID_2013::FeedbackVolume:          return AkPropID_2022::_FeedbackVolume;
        case AkPropID_2013::FeedbackLPF:             return AkPropID_2022::_FeedbackLPF;
        case AkPropID_2013::MuteRatio:               return AkPropID_2022::MuteRatio;
        case AkPropID_2013::PAN_LR:                  return AkPropID_2022::PAN_LR;
        case AkPropID_2013::PAN_FR:                  return AkPropID_2022::PAN_FR;
        case AkPropID_2013::CenterPCT:               return AkPropID_2022::CenterPCT;
        case AkPropID_2013::DelayTime:               return AkPropID_2022::DelayTime;
        case AkPropID_2013::TransitionTime:          return AkPropID_2022::TransitionTime;
        case AkPropID_2013::Probability:             return AkPropID_2022::Probability;
        case AkPropID_2013::DialogueMode:            return AkPropID_2022::DialogueMode;
        case AkPropID_2013::UserAuxSendVolume0:      return AkPropID_2022::UserAuxSendVolume0;
        case AkPropID_2013::UserAuxSendVolume1:      return AkPropID_2022::UserAuxSendVolume1;
        case AkPropID_2013::UserAuxSendVolume2:      return AkPropID_2022::UserAuxSendVolume2;
        case AkPropID_2013::UserAuxSendVolume3:      return AkPropID_2022::UserAuxSendVolume3;
        case AkPropID_2013::GameAuxSendVolume:       return AkPropID_2022::GameAuxSendVolume;
        case AkPropID_2013::OutputBusVolume:         return AkPropID_2022::OutputBusVolume;
        case AkPropID_2013::OutputBusLPF:            return AkPropID_2022::OutputBusLPF;
        case AkPropID_2013::InitialDelay:            return AkPropID_2022::InitialDelay;
        case AkPropID_2013::HDRBusThreshold:         return AkPropID_2022::HDRBusThreshold;
        case AkPropID_2013::HDRBusRatio:             return AkPropID_2022::HDRBusRatio;
        case AkPropID_2013::HDRBusReleaseTime:       return AkPropID_2022::HDRBusReleaseTime;
        case AkPropID_2013::HDRBusGameParam:         return AkPropID_2022::HDRBusGameParam;
        case AkPropID_2013::HDRBusGameParamMin:      return AkPropID_2022::HDRBusGameParamMin;
        case AkPropID_2013::HDRBusGameParamMax:      return AkPropID_2022::HDRBusGameParamMax;
        case AkPropID_2013::HDRActiveRange:          return AkPropID_2022::HDRActiveRange;
        case AkPropID_2013::MakeUpGain:              return AkPropID_2022::MakeUpGain;
        case AkPropID_2013::LoopStart:               return AkPropID_2022::LoopStart;
        case AkPropID_2013::LoopEnd:                 return AkPropID_2022::LoopEnd;
        case AkPropID_2013::TrimInTime:              return AkPropID_2022::TrimInTime;
        case AkPropID_2013::TrimOutTime:             return AkPropID_2022::TrimOutTime;
        case AkPropID_2013::FadeInTime:              return AkPropID_2022::FadeInTime;
        case AkPropID_2013::FadeOutTime:             return AkPropID_2022::FadeOutTime;
        case AkPropID_2013::FadeInCurve:             return AkPropID_2022::FadeInCurve;
        case AkPropID_2013::FadeOutCurve:            return AkPropID_2022::FadeOutCurve;
        case AkPropID_2013::LoopCrossfadeDuration:   return AkPropID_2022::LoopCrossfadeDuration;
        case AkPropID_2013::CrossfadeUpCurve:        return AkPropID_2022::CrossfadeUpCurve;
        case AkPropID_2013::CrossfadeDownCurve:      return AkPropID_2022::CrossfadeDownCurve;
        }
    }

    AkPropID_2022 ConvertType(AkPropID_2015 t) {
        switch (t)
        {
        case AkPropID_2015::Volume:                  return AkPropID_2022::Volume;
        case AkPropID_2015::LFE:                     return AkPropID_2022::LFE;
        case AkPropID_2015::Pitch:                   return AkPropID_2022::Pitch;
        case AkPropID_2015::LPF:                     return AkPropID_2022::LPF;
        case AkPropID_2015::HPF:                     return AkPropID_2022::HPF;
        case AkPropID_2015::BusVolume:               return AkPropID_2022::BusVolume;
        case AkPropID_2015::Priority:                return AkPropID_2022::Priority;
        case AkPropID_2015::PriorityDistanceOffset:  return AkPropID_2022::PriorityDistanceOffset;
        case AkPropID_2015::FeedbackVolume:          return AkPropID_2022::_FeedbackVolume;
        case AkPropID_2015::FeedbackLPF:             return AkPropID_2022::_FeedbackLPF;
        case AkPropID_2015::MuteRatio:               return AkPropID_2022::MuteRatio;
        case AkPropID_2015::PAN_LR:                  return AkPropID_2022::PAN_LR;
        case AkPropID_2015::PAN_FR:                  return AkPropID_2022::PAN_FR;
        case AkPropID_2015::CenterPCT:               return AkPropID_2022::CenterPCT;
        case AkPropID_2015::DelayTime:               return AkPropID_2022::DelayTime;
        case AkPropID_2015::TransitionTime:          return AkPropID_2022::TransitionTime;
        case AkPropID_2015::Probability:             return AkPropID_2022::Probability;
        case AkPropID_2015::DialogueMode:            return AkPropID_2022::DialogueMode;
        case AkPropID_2015::UserAuxSendVolume0:      return AkPropID_2022::UserAuxSendVolume0;
        case AkPropID_2015::UserAuxSendVolume1:      return AkPropID_2022::UserAuxSendVolume1;
        case AkPropID_2015::UserAuxSendVolume2:      return AkPropID_2022::UserAuxSendVolume2;
        case AkPropID_2015::UserAuxSendVolume3:      return AkPropID_2022::UserAuxSendVolume3;
        case AkPropID_2015::GameAuxSendVolume:       return AkPropID_2022::GameAuxSendVolume;
        case AkPropID_2015::OutputBusVolume:         return AkPropID_2022::OutputBusVolume;
        case AkPropID_2015::OutputBusHPF:            return AkPropID_2022::OutputBusHPF;
        case AkPropID_2015::OutputBusLPF:            return AkPropID_2022::OutputBusLPF;
        case AkPropID_2015::HDRBusThreshold:         return AkPropID_2022::HDRBusThreshold;
        case AkPropID_2015::HDRBusRatio:             return AkPropID_2022::HDRBusRatio;
        case AkPropID_2015::HDRBusReleaseTime:       return AkPropID_2022::HDRBusReleaseTime;
        case AkPropID_2015::HDRBusGameParam:         return AkPropID_2022::HDRBusGameParam;
        case AkPropID_2015::HDRBusGameParamMin:      return AkPropID_2022::HDRBusGameParamMin;
        case AkPropID_2015::HDRBusGameParamMax:      return AkPropID_2022::HDRBusGameParamMax;
        case AkPropID_2015::HDRActiveRange:          return AkPropID_2022::HDRActiveRange;
        case AkPropID_2015::MakeUpGain:              return AkPropID_2022::MakeUpGain;
        case AkPropID_2015::LoopStart:               return AkPropID_2022::LoopStart;
        case AkPropID_2015::LoopEnd:                 return AkPropID_2022::LoopEnd;
        case AkPropID_2015::TrimInTime:              return AkPropID_2022::TrimInTime;
        case AkPropID_2015::TrimOutTime:             return AkPropID_2022::TrimOutTime;
        case AkPropID_2015::FadeInTime:              return AkPropID_2022::FadeInTime;
        case AkPropID_2015::FadeOutTime:             return AkPropID_2022::FadeOutTime;
        case AkPropID_2015::FadeInCurve:             return AkPropID_2022::FadeInCurve;
        case AkPropID_2015::FadeOutCurve:            return AkPropID_2022::FadeOutCurve;
        case AkPropID_2015::LoopCrossfadeDuration:   return AkPropID_2022::LoopCrossfadeDuration;
        case AkPropID_2015::CrossfadeUpCurve:        return AkPropID_2022::CrossfadeUpCurve;
        case AkPropID_2015::CrossfadeDownCurve:      return AkPropID_2022::CrossfadeDownCurve;
        case AkPropID_2015::MidiTrackingRootNote:    return AkPropID_2022::MidiTrackingRootNote;
        case AkPropID_2015::MidiPlayOnNoteType:      return AkPropID_2022::MidiPlayOnNoteType;
        case AkPropID_2015::MidiTransposition:       return AkPropID_2022::MidiTransposition;
        case AkPropID_2015::MidiVelocityOffset:      return AkPropID_2022::MidiVelocityOffset;
        case AkPropID_2015::MidiKeyRangeMin:         return AkPropID_2022::MidiKeyRangeMin;
        case AkPropID_2015::MidiKeyRangeMax:         return AkPropID_2022::MidiKeyRangeMax;
        case AkPropID_2015::MidiVelocityRangeMin:    return AkPropID_2022::MidiVelocityRangeMin;
        case AkPropID_2015::MidiVelocityRangeMax:    return AkPropID_2022::MidiVelocityRangeMax;
        case AkPropID_2015::MidiChannelMask:         return AkPropID_2022::MidiChannelMask;
        case AkPropID_2015::PlaybackSpeed:           return AkPropID_2022::PlaybackSpeed;
        case AkPropID_2015::MidiTempoSource:         return AkPropID_2022::MidiTempoSource;
        case AkPropID_2015::MidiTargetNode:          return AkPropID_2022::MidiTargetNode;
        case AkPropID_2015::AttachedPluginFXID:      return AkPropID_2022::AttachedPluginFXID;
        case AkPropID_2015::Loop:                    return AkPropID_2022::Loop;
        case AkPropID_2015::InitialDelay:            return AkPropID_2022::InitialDelay;
        }
    }
}