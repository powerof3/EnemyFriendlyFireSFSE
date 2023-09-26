namespace EnemyFriendlyFire
{
	struct CheckValidTarget
	{
		static bool thunk(RE::Actor*, RE::TESObjectREFR&)
		{
			return true;
		}
		[[maybe_unused]] static inline REL::Relocation<decltype(thunk)> func;
		static inline std::size_t                                       idx = 0x162;
	};

	void Install()
	{
		stl::write_vfunc<RE::Actor, CheckValidTarget>(25);

	    logger::info("Hooked CheckValidTarget");
	}
}

void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
{
	switch (a_msg->type) {
	case SFSE::MessagingInterface::kPostLoad:
		EnemyFriendlyFire::Install();
		break;
	default:
		break;
	}
}

DLLEXPORT constinit auto SFSEPlugin_Version = []() noexcept {
	SFSE::PluginVersionData data{};

	data.PluginVersion(Version::MAJOR);
	data.PluginName(Version::PROJECT);
	data.AuthorName("powerofthree");
	data.UsesAddressLibrary(true);
	//data.UsesSigScanning(true);
	data.IsLayoutDependent(true);
	//data.HasNoStructUse(true);
	data.CompatibleVersions({ SFSE::RUNTIME_LATEST });

	return data;
}();

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
