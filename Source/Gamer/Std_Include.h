#pragma once

#define TITLE_ID 0x4156089E // nx1

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <io.h>

#include <xtl.h>
#include <xbox.h>
#include <xgraphics.h>

#include "Game/Structs.h"
#include "Game/Symbols.h"

#include "Util/Hook.h"
#include "Util/String.h"

extern "C"
{
	NTSYSAPI DWORD NTAPI XamGetCurrentTitleId(VOID);
}
