// Copyright 2019 Hujiachuan. All Rights Reserved.

#include "AsyncFuncCaller.h"

#define LOCTEXT_NAMESPACE "FAsyncFuncCallerModule"

void FAsyncFuncCallerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FAsyncFuncCallerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAsyncFuncCallerModule, AsyncFuncCaller)