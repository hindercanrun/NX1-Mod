#pragma once

#define TITLE_ID 0x4156089E // nx1

#define BASE_FOLDER "nx1-data"

typedef unsigned int   uInt;  /* 16 bits or more */

typedef void* voidpf;
typedef unsigned char Bytef;

typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void   (*free_func)(voidpf opaque, voidpf address);

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include <xtl.h>
#include <xbox.h>
#include <xgraphics.h>
#include <direct.h>
#include <io.h>
#include <time.h>

#include "Deps\ZLib\zlib.h"

#include "Game\Structs.h"
#include "Game\Symbols.h"

#include "Util\Command.h"
#include "Util\FileSystem.h"
#include "Util\Hook.h"
#include "Util\Print.h"
#include "Util\String.h"

#include "ModulesLoader\ModulesLoader.h"

extern "C"
{
	NTSYSAPI DWORD NTAPI XamGetCurrentTitleId(VOID);
}
