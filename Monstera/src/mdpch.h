#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>


#include <Monstera/Core/Core.h>

#include "Monstera/Core/Log.h"

#include "Monstera/Debug/Instrumentor.h"

// Could use platform specific headers like this

#ifdef MD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

