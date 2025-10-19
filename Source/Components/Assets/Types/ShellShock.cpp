#include "ShellShock.h"

namespace Assets
{
	void Dump_ShellShock(const ShellShockParams* shock)
	{
		if (!shock) return;

		std::string assetName = shock->p_name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\nx1-data\\dump\\shock\\" + assetName + ".shock";

		std::ostringstream oss;
		oss << std::fixed << std::setprecision(6);

		oss << "screenBlendBlurredFadeTime [" << shock->screenBlendBlurredFadeTime << "]\n";
		oss << "screenBlendBlurredEffectTime [" << shock->screenBlendBlurredEffectTime << "]\n";
		oss << "screenBlendFlashWhiteFadeTime [" << shock->screenBlendFlashWhiteFadeTime << "]\n";
		oss << "screenBlendFlashShotFadeTime [" << shock->screenBlendFlashShotFadeTime << "]\n";
		oss << "screenBlendType [" << shock->screenBlendType << "]\n";
		oss << "viewFadeTime [" << shock->viewFadeTime << "]\n";
		oss << "viewKickRate [" << shock->viewKickRate << "]\n";
		oss << "viewKickRadius [" << shock->viewKickRadius << "]\n";
		oss << "lookControlAffect [" << (shock->lookControlAffect ? 1 : 0) << "]\n";
		oss << "lookControlFadeTime [" << shock->lookControlFadeTime << "]\n";
		oss << "lookControlMouseSensitivity [" << shock->lookControlMouseSensitivity << "]\n";
		oss << "lookControlMaxPitchSpeed [" << shock->lookControlMaxPitchSpeed << "]\n";
		oss << "lookControlMaxYawSpeed [" << shock->lookControlMaxYawSpeed << "]\n";
		oss << "movementAffect [" << ((shock->movementAffect) ? 1 : 0) << "]\n";
		oss << "volumeSettingName [" << ((shock->volumeSettingName) ? shock->volumeSettingName : "") << "]\n";
		oss << "soundAffect [" << ((shock->soundAffect) ? 1 : 0) << "]\n";
		oss << "soundLoop [" << ((shock->soundLoop) ? shock->soundLoop : "") << "]\n";
		oss << "soundEnd [" << ((shock->soundEnd) ? shock->soundEnd : "") << "]\n";
		oss << "soundEndAbort [" << (shock->soundEndAbort ? shock->soundEndAbort : "") << "]\n";
		oss << "soundFadeInTime [" << shock->soundFadeInTime << "]\n";
		oss << "soundFadeOutTime [" << shock->soundFadeOutTime << "]\n";
		oss << "soundDrylevel [" << shock->soundDrylevel << "]\n";
		oss << "soundWetlevel [" << shock->soundWetlevel << "]\n";
		oss << "soundRoomtype [" << (shock->soundRoomtype ? shock->soundRoomtype : "") << "]\n";
		oss << "soundModEndDelay [" << shock->soundModEndDelay << "]\n";
		oss << "soundLoopFadeTime [" << shock->soundLoopFadeTime << "]\n";
		oss << "soundLoopEndDelay [" << shock->soundLoopEndDelay << "]\n";

		std::string data = oss.str();
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), data.c_str(), (int)data.size());
	}
}
