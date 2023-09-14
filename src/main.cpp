namespace EnemyFriendlyFire
{
	struct CheckValidTarget
	{
		static bool Thunk(RE::Actor*, RE::TESObjectREFR&)
		{
			return true;
		}
		[[maybe_unused]] static inline REL::Relocation<decltype(Thunk)> func;

		static inline std::size_t idx = 0x162;
	};

	void Install()
	{
		stl::write_vfunc<RE::Actor, CheckValidTarget>();

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
	data.UsesSigScanning(true);
	//data.UsesAddressLibrary(true);
	data.HasNoStructUse(true);
	//data.IsLayoutDependent(true);
	data.CompatibleVersions({ SFSE::RUNTIME_SF_1_7_29 });

	return data;
}();

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
