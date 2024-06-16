#pragma once

#include <string>
#include <optional>

namespace Monstera {

	class FileDialogs
	{
	public:
		static std::optional<std::string> OpenFile(const char* filter); // Returns empty string if cancelled
		static std::optional<std::string> SaveFile(const char* filter); // Returns empty string if cancelled

	};

}