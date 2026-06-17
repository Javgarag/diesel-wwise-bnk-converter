#pragma once
#include "ak_types.h"

namespace Wwise {
	inline BankVersion VERSION;
	inline BankVersion CONVERT_VERSION;
	inline bool FEEDBACK_IN_BANK;

	template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
	template<class... Ts> overload(Ts...) -> overload<Ts...>;
}