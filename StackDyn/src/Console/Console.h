#pragma once

#include <iostream>
#include <string>
#include <windows.h>

#include "Block.h"
#include "Stack.h"
#include "Handover.h"
#include "Crane.h"


class Console
{
private:
	void Draw();
	void CreateArrivalStack();

public:

	Console();
	~Console();

};

