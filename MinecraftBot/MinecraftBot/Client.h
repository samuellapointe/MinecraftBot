#pragma once

#include "stdafx.h"
#include "VisualInterface.h"

using namespace std;

namespace MinecraftBot
{
	struct Client
	{
		Client(string username, string password, string ip, int port);
	};
}
