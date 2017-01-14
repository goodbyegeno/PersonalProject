// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstring>
#include <Windows.h>
#include <chrono>
#include <ctime>

#include <vector>
#include <unordered_map>

//#include <string>

//dx
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <directxmath.h>

// TODO: reference additional headers your program requires here
#include "RenderEngineCommon.h"


//lib

//3rd party lib
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")