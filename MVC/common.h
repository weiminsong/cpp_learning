// common.h
// https://helloacm.com/model-view-controller-explained-in-c/
#pragma once //thif will will be included only once in one compiler, same as ifndef
#include <string>
using namespace std;
typedef void (*DataChangeHandler)(string newData);
