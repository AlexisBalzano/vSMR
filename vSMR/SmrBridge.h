#pragma once
#include <string>

// vSMR's client side of the EuroScope Plugin Bridge.
//
// Deliberately no esbridge.h here: the bridge types, the client shim and its file static
// attach state all live in SMRPlugin.cpp, so exactly one translation unit carries them
// (INTEGRATION.md A2) and the rest of vSMR sees only plain strings.
//
// Every function is a no-op returning false when the bridge DLL is not installed, or when
// Ramp Agent is not loaded. That is a normal configuration, not an error: vSMR draws its
// tags without stand data exactly as it did before.
//
// Main thread only. The bridge ABI requires it (A8), which is satisfied because both
// callers are OnTimer and OnRefresh.
namespace SmrBridge
{
	// Attaches to the bridge and resolves the Ramp Agent fields, retrying on each call.
	// Must be called from OnTimer rather than a constructor: EuroScope's plugin load order
	// follows the user's settings file, so both the bridge and Ramp Agent may load after
	// us (A4, B2.1).
	void Attach();

	// Fill out with the value published for this callsign, or clear it and return false.
	bool StandFor(const char* callsign, std::string& out);
	bool RemarkFor(const char* callsign, std::string& out);
}
