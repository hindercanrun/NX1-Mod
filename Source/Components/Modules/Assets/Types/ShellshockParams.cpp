namespace Assets
{
	void Dump_ShellshockParams(const ShellShockParams* shellShockParams)
	{
		if (!shellShockParams)
			return;

		std::string assetName = shellShockParams->p_name;
		std::replace(assetName.begin(), assetName.end(), '/', '\\');

		std::string outPath = "game:\\nx1-data\\dump\\shock\\" + assetName + ".shock";

		std::ostringstream oss;
		oss << std::fixed << std::setprecision(6);

		oss << "screenBlendBlurredFadeTime," << shellShockParams->screenBlendBlurredFadeTime << "\n";
		oss << "screenBlendBlurredEffectTime," << shellShockParams->screenBlendBlurredEffectTime << "\n";
		oss << "screenBlendFlashWhiteFadeTime," << shellShockParams->screenBlendFlashWhiteFadeTime << "\n";
		oss << "screenBlendFlashShotFadeTime," << shellShockParams->screenBlendFlashShotFadeTime << "\n";
		oss << "screenBlendType," << shellShockParams->screenBlendType << "\n";
		oss << "viewFadeTime," << shellShockParams->viewFadeTime << "\n";
		oss << "viewKickRate," << shellShockParams->viewKickRate << "\n";
		oss << "viewKickRadius," << shellShockParams->viewKickRadius << "\n";
		oss << "lookControlAffect," << ((shellShockParams->lookControlAffect) ? 1 : 0) << "\n";
		oss << "lookControlFadeTime," << shellShockParams->lookControlFadeTime << "\n";
		oss << "lookControlMouseSensitivity," << shellShockParams->lookControlMouseSensitivity << "\n";
		oss << "lookControlMaxPitchSpeed," << shellShockParams->lookControlMaxPitchSpeed << "\n";
		oss << "lookControlMaxYawSpeed," << shellShockParams->lookControlMaxYawSpeed << "\n";
		oss << "movementAffect," << ((shellShockParams->movementAffect) ? 1 : 0) << "\n";
		oss << "volumeSettingName," << shellShockParams->volumeSettingName << "\n";
		oss << "soundAffect," << ((shellShockParams->soundAffect) ? 1 : 0) << "\n";
		oss << "soundLoop," << shellShockParams->soundLoop << "\n";
		oss << "soundEnd," << shellShockParams->soundEnd << "\n";
		oss << "soundEndAbort," << shellShockParams->soundEndAbort << "\n";
		oss << "soundFadeInTime," << shellShockParams->soundFadeInTime << "\n";
		oss << "soundFadeOutTime," << shellShockParams->soundFadeOutTime << "\n";
		oss << "soundDrylevel," << shellShockParams->soundDrylevel << "\n";
		oss << "soundWetlevel," << shellShockParams->soundWetlevel << "\n";
		oss << "soundRoomtype," << shellShockParams->soundRoomtype << "\n";
		oss << "soundModEndDelay," << shellShockParams->soundModEndDelay << "\n";
		oss << "soundLoopFadeTime," << shellShockParams->soundLoopFadeTime << "\n";
		oss << "soundLoopEndDelay," << shellShockParams->soundLoopEndDelay << "\n";

		std::string data = oss.str();
		Util::FileSystem::WriteFileToDisk(outPath.c_str(), data.c_str(), (int)data.size());
	}
}
