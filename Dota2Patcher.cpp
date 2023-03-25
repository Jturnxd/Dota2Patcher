#include "Dota2Patcher.h"
#include <string>

bool Silent = false;

void Patcher::Output(const char* text, ...) {
	if (Silent)
		return;
	std::cout << text << std::endl;
}

void Patcher::SwitchCommand(int USER_INPUT) {
	switch (USER_INPUT) {
	case 1:
		if (Patcher::patch_dota_plus(false))
			Output("[+] Dota Plus Unlocked");
		if (Patcher::patch_sv_cheats(false))
			Output("[+] Sv_cheats Patched");
		if (Patcher::patch_gameinfo(false))
			Output("[+] Gameinfo Patched");
		break;
	case 2:
		if (Patcher::patch_dota_plus(false))
			Output("[+] Dota Plus Unlocked");
		break;
	case 3:
		if (Patcher::patch_sv_cheats(false))
			Output("[+] Sv_cheats Patched");
		break;
	case 4:
		if (Patcher::patch_gameinfo(false))
			Output("[+] Gameinfo Patched");
		break;
	case 5:
		if (Patcher::patch_dota_plus(true))
			Output("[+] Dota Plus Reverted");
		if (Patcher::patch_sv_cheats(true))
			Output("[+] Sv_cheats Reverted");
		if (Patcher::patch_gameinfo(true))
			Output("[+] Gameinfo Reverted");
		break;
	default:
		DrawMenu();
		break;
	}
}

void Patcher::DrawMenu() {
	std::cout << "[Dota2Patcher]" << std::endl;
	std::cout << "\n[Enter number]" << std::endl;
	std::cout << "[1] Patch All" << std::endl;
	std::cout << "[2] Unlock Dota Plus" << std::endl;
	std::cout << "[3] Patch sv_cheats" << std::endl;
	std::cout << "[4] Patch Gameinfo" << std::endl;
	std::cout << "[5] Revert Patches" << std::endl;
	std::cout << "\n>>> ";

	int USER_INPUT;
	std::cin >> USER_INPUT;
	SwitchCommand(USER_INPUT);
}

int main(int argc, char* argv[]) {
	Patcher::CheckUpdate();

    if (!Paths::get_dota_path(&Globals::dota_path)) {
        system("pause");
        return 0;
    }

	if (argc > 1) {
		int Iterator = 1;
		std::string IsSilentFlag = argv[1];

		if (IsSilentFlag == "-s") {
			Silent = true;
			Iterator++;
		}

		for (Iterator; Iterator < argc; Iterator++) {
			std::string ArgStr = argv[Iterator];
			int Arg = std::stoi(ArgStr);
			Patcher::SwitchCommand(abs(Arg));
		}

		if (!Silent)
			system("pause");
		return 0;
	}

    Patcher::DrawMenu();

    system("pause");
    return 0;
}
