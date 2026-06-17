#include "actor_mixer.h"

namespace Wwise {
	HIRCActorMixer::HIRCActorMixer(Reader& reader)
		: item_base(reader),
		base_params(reader),
		children(reader)
	{}

	void HIRCActorMixer::Convert(Writer& writer) {
		item_base.Convert(writer);
		base_params.Convert(writer);
		children.Convert(writer);
		item_base.UpdateSize(writer);
	}
}