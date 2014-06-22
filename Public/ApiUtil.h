#pragma once 

#ifndef _API_UTIL_
#define _API_UTIL_

#include "tinyxml2.h"
#include "ApiTypeDefine.h"

int AssigneFiledInput(FiledInput *filed, const tinyxml2::XMLElement *ele);

int AssigneFiledOutput(FiledOutput *filed, const tinyxml2::XMLElement *ele);

int AssigneFunctionItem(FunctionItem *funcItem, const tinyxml2::XMLElement *ele);

#endif