#pragma once
#define export extern "C" __declspec(dllexport)
#include <Windows.h>
#include <WinUser.h>

using namespace System;
using namespace System::IO;
using namespace System::Reflection;

void DllMain();
static Assembly^ LoadFromSameFolder(Object^ sender, ResolveEventArgs^ args);
export void Multiply(int* op1, int* op2, int* result, int* success, const char** message);