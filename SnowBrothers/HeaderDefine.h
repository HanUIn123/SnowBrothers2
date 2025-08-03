#pragma once
#include <vector>
#include <Windows.h>
#include <ctime>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

//#include <vfw.h>
//#pragma comment(lib, "vfw32.lib")

#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc.lib")

#include <io.h>


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif