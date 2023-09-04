#include "SFSE/Stub.h"

#include "sfse_common/Relocation.h"
#include "sfse_common/SafeWrite.h"

namespace EnemyFriendlyFire
{
	bool CheckValidTarget(std::uintptr_t, std::uintptr_t)
	{
		return true;
	};

	void Install()
	{
		constexpr std::uintptr_t Actor_Vtable = 0x044D6C78;

		const RelocAddr<std::uintptr_t> CheckValidTarget_Address(Actor_Vtable + 0xB10);
		safeWrite64(CheckValidTarget_Address.getUIntPtr(), reinterpret_cast<uintptr_t>(CheckValidTarget));

		INFO("Hooked CheckValidTarget");
	}
}

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};

	data.PluginVersion(Plugin::Version);
	data.PluginName(Plugin::NAME);
	data.AuthorName(Plugin::AUTHOR);
	data.UsesSigScanning(true);
	//data.UsesAddressLibrary(true);
	data.HasNoStructUse(true);
	//data.IsLayoutDependent(true);
	data.CompatibleVersions({ RUNTIME_VERSION_1_7_23 });

	return data;
}();

namespace
{
	void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
	{
		switch (a_msg->type) {
		case SFSE::MessagingInterface::kPostLoad:
			{
				EnemyFriendlyFire::Install();
			}
			break;
		default:
			break;
		}
	}
}

/**
// for preload plugins
void SFSEPlugin_Preload(SFSE::LoadInterface* a_sfse);
/**/

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(SFSEInterface* a_sfse)
{
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif

	SFSE::Init(a_sfse);

	DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));

	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}