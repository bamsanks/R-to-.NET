#include "tunnel.h"

void DllMain() {
	AppDomain^ currentDomain = AppDomain::CurrentDomain;
	currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(LoadFromSameFolder);
}

static Assembly^ LoadFromSameFolder(Object^ sender, ResolveEventArgs^ args) {
	String^ folderPath = Path::GetDirectoryName(
		Assembly::GetExecutingAssembly()->Location);
	String^ assemblyPath = Path::Combine(
		folderPath, (gcnew AssemblyName(args->Name))->Name + ".dll");

	if (!File::Exists(assemblyPath)) return nullptr;
	Assembly^ assembly = Assembly::LoadFrom(assemblyPath);
	return assembly;
}

export void Multiply(int* op1, int* op2, int* result,
	int* success, const char** message) {
	
	// Assume failed unless we reach the end
	*success = FALSE;

	// Attempt to load .NET DLL (must be in same folder as this DLL)
	Assembly^ assembly;
	try {
		assembly = Assembly::Load("TestDLL");
	} catch (Exception^) {
		*message = "Unable to locate underlying DLL";
		return;
	}

	// Get static class containing the function we want to call
	Type^ exports = assembly->GetType("TestDLL.Exports");
	if (exports == nullptr) {
		*message = "Specified class doesn't exist";
		return;
	}

	// Try to invoke the method from the loaded assembly/class
	try {
		array<Object^>^ params = gcnew array<Object^>(2);
		params[0] = *op1; params[1] = *op2;

		Object^ resultObj = exports->InvokeMember(
			"Multiply", BindingFlags::InvokeMethod, nullptr, exports, params);

		*result = safe_cast<int>(resultObj);
	} catch (Exception^) {
		*message = "Unknown error occurred when calling .NET function";
		return;
	}

	// If we reach here, all is good and nothing to report
	*success = TRUE;
	*message = "";
}