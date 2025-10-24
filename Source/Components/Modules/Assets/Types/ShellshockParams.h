#pragma once

namespace Assets
{
	enum ShockViewTypes : int
	{
		SHELLSHOCK_VIEWTYPE_BLURRED = 0,
		SHELLSHOCK_VIEWTYPE_FLASHED = 1,
		SHELLSHOCK_VIEWTYPE_NONE = 2,
	};

	struct ShellShockParams
	{
		const char* p_name;
		int screenBlendBlurredFadeTime;
		int screenBlendBlurredEffectTime;
		int screenBlendFlashWhiteFadeTime;
		int screenBlendFlashShotFadeTime;
		ShockViewTypes screenBlendType;
		int viewFadeTime;
		float viewKickRate;
		float viewKickRadius;
		bool lookControlAffect;
		int lookControlFadeTime;
		float lookControlMouseSensitivity;
		float lookControlMaxPitchSpeed;
		float lookControlMaxYawSpeed;
		bool movementAffect;
		const char* volumeSettingName;
		bool soundAffect;
		const char* soundLoop;
		const char* soundEnd;
		const char* soundEndAbort;
		int soundFadeInTime;
		int soundFadeOutTime;
		float soundDrylevel;
		float soundWetlevel;
		char* soundRoomtype;
		int soundModEndDelay;
		int soundLoopFadeTime;
		int soundLoopEndDelay;
	};

	void Dump_ShellshockParams(const ShellShockParams* shock);
}
