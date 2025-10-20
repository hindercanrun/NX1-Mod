#pragma once

struct FxEffectDef;
struct TracerDef;
struct LaserDef;

namespace Assets
{
	enum weapType_t : int
	{
		WEAPTYPE_BULLET = 0x0,
		WEAPTYPE_GRENADE = 0x1,
		WEAPTYPE_PROJECTILE = 0x2,
		WEAPTYPE_RIOTSHIELD = 0x3,

		WEAPTYPE_NUM = 0x4,
	};

	enum weapClass_t : int
	{
		WEAPCLASS_RIFLE = 0x0,
		WEAPCLASS_SNIPER = 0x1,
		WEAPCLASS_MG = 0x2,
		WEAPCLASS_SMG = 0x3,
		WEAPCLASS_SPREAD = 0x4,
		WEAPCLASS_PISTOL = 0x5,
		WEAPCLASS_MINI = 0x6,
		WEAPCLASS_GRENADE = 0x7,
		WEAPCLASS_ROCKETLAUNCHER = 0x8,
		WEAPCLASS_TURRET = 0x9,
		WEAPCLASS_THROWINGKNIFE = 0xA,
		WEAPCLASS_NON_PLAYER = 0xB,
		WEAPCLASS_NON_PLAYER_SPREAD = 0xC,
		WEAPCLASS_ITEM = 0xD,

		WEAPCLASS_NUM = 0xE,
	};

	enum PenetrateType : int
	{
		PENETRATE_TYPE_NONE = 0x0,
		PENETRATE_TYPE_SMALL = 0x1,
		PENETRATE_TYPE_MEDIUM = 0x2,
		PENETRATE_TYPE_LARGE = 0x3,

		PENETRATE_TYPE_COUNT = 0x4,
	};

	enum weapInventoryType_t : int
	{
		WEAPINVENTORY_PRIMARY = 0x0,
		WEAPINVENTORY_OFFHAND = 0x1,
		WEAPINVENTORY_ITEM = 0x2,
		WEAPINVENTORY_ALTMODE = 0x3,
		WEAPINVENTORY_EXCLUSIVE = 0x4,
		WEAPINVENTORY_SCAVENGER = 0x5,
		WEAPINVENTORY_ALTAMMOMODE = 0x6,

		WEAPINVENTORYCOUNT = 0x7,
	};

	enum weapFireType_t : __int32
	{
		WEAPON_FIRETYPE_FULLAUTO = 0x0,
		WEAPON_FIRETYPE_CONTINUOUS = 0x1,
		WEAPON_FIRETYPE_SINGLESHOT = 0x2,
		WEAPON_FIRETYPE_BURSTFIRE2 = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE3 = 0x4,
		WEAPON_FIRETYPE_BURSTFIRE4 = 0x5,
		WEAPON_FIRETYPE_DOUBLEBARREL = 0x6,

		WEAPON_FIRETYPECOUNT = 0x7,

		WEAPON_FIRETYPE_BURSTFIRE_FIRST = 0x3,
		WEAPON_FIRETYPE_BURSTFIRE_LAST = 0x5,
		WEAPON_FIRETYPE_BURSTFIRE_FIRST_COUNT = 0x2,
	};

	enum OffhandClass : int
	{
		OFFHAND_CLASS_NONE = 0x0,
		OFFHAND_CLASS_FRAG_GRENADE = 0x1,
		OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
		OFFHAND_CLASS_FLASH_GRENADE = 0x3,
		OFFHAND_CLASS_THROWINGKNIFE = 0x4,
		OFFHAND_CLASS_GAS = 0x5,
		OFFHAND_CLASS_EMP = 0x6,
		OFFHAND_CLASS_LIDAR = 0x7,
		OFFHAND_CLASS_OTHER = 0x8,

		OFFHAND_CLASS_COUNT = 0x9,
	};

	enum weapStance_t : int
	{
		WEAPSTANCE_STAND = 0x0,
		WEAPSTANCE_DUCK = 0x1,
		WEAPSTANCE_PRONE = 0x2,

		WEAPSTANCE_NUM = 0x3,
	};

	enum activeReticleType_t : int
	{
		VEH_ACTIVE_RETICLE_NONE = 0x0,
		VEH_ACTIVE_RETICLE_PIP_ON_A_STICK = 0x1,
		VEH_ACTIVE_RETICLE_BOUNCING_DIAMOND = 0x2,

		VEH_ACTIVE_RETICLE_COUNT = 0x3,
	};

	enum weaponIconRatioType_t : int
	{
		WEAPON_ICON_RATIO_1TO1 = 0x0,
		WEAPON_ICON_RATIO_2TO1 = 0x1,
		WEAPON_ICON_RATIO_4TO1 = 0x2,

		WEAPON_ICON_RATIO_COUNT = 0x3,
	};

	enum ammoCounterClipType_t : int
	{
		AMMO_COUNTER_CLIP_NONE = 0x0,
		AMMO_COUNTER_CLIP_MAGAZINE = 0x1,
		AMMO_COUNTER_CLIP_SHORTMAGAZINE = 0x2,
		AMMO_COUNTER_CLIP_SHOTGUN = 0x3,
		AMMO_COUNTER_CLIP_ROCKET = 0x4,
		AMMO_COUNTER_CLIP_BELTFED = 0x5,
		AMMO_COUNTER_CLIP_ALTWEAPON = 0x6,

		AMMO_COUNTER_CLIP_COUNT = 0x7,
	};

	enum weapOverlayReticle_t : int
	{
		WEAPOVERLAYRETICLE_NONE = 0x0,
		WEAPOVERLAYRETICLE_CROSSHAIR = 0x1,

		WEAPOVERLAYRETICLE_NUM = 0x2,
	};

	enum WeapOverlayInteface_t : int
	{
		WEAPOVERLAYINTERFACE_NONE = 0x0,
		WEAPOVERLAYINTERFACE_JAVELIN = 0x1,
		WEAPOVERLAYINTERFACE_TURRETSCOPE = 0x2,

		WEAPOVERLAYINTERFACECOUNT = 0x3,
	};

	enum weapProjExposion_t : int
	{
		WEAPPROJEXP_GRENADE = 0x0,
		WEAPPROJEXP_ROCKET = 0x1,
		WEAPPROJEXP_FLASHBANG = 0x2,
		 WEAPPROJEXP_NONE = 0x3,
		WEAPPROJEXP_DUD = 0x4,
		WEAPPROJEXP_SMOKE = 0x5,
		WEAPPROJEXP_HEAVY = 0x6,
		WEAPPROJEXP_BOUNCE = 0x7,

		WEAPPROJEXP_NUM = 0x8,
	};

	enum WeapStickinessType : int
	{
		WEAPSTICKINESS_NONE = 0x0,
		WEAPSTICKINESS_ALL = 0x1,
		WEAPSTICKINESS_ALL_ORIENT = 0x2,
		WEAPSTICKINESS_GROUND = 0x3,
		WEAPSTICKINESS_GROUND_WITH_YAW = 0x4,
		WEAPSTICKINESS_KNIFE = 0x5,

		WEAPSTICKINESS_COUNT = 0x6,
	};

	enum guidedMissileType_t : int
	{
		MISSILE_GUIDANCE_NONE = 0x0,
		MISSILE_GUIDANCE_SIDEWINDER = 0x1,
		MISSILE_GUIDANCE_HELLFIRE = 0x2,
		MISSILE_GUIDANCE_JAVELIN = 0x3,
		MISSILE_GUIDANCE_AIRBURSTGRENADE = 0x4,

		MISSILE_GUIDANCE_COUNT = 0x5,
	};

	enum airBurstGrenadeHUD_t : int
	{
		AIR_BURST_GRENADE_HUD_NONE = 0x0,
		AIR_BURST_GRENADE_HUD_FULL = 0x1,
		AIR_BURST_GRENADE_HUD_LITE = 0x2,

		AIR_BURST_GRENADE_HUD_COUNT = 0x3,
	};

	struct WeaponDef
	{
		const char* szOverlayName;
		//XModel** gunXModel;
		//XModel* handXModel;
		const char** szXAnimsRightHanded;
		const char** szXAnimsLeftHanded;
		const char* szModeName;
		unsigned short* notetrackSoundMapKeys;
		unsigned short* notetrackSoundMapValues;
		unsigned short* notetrackRumbleMapKeys;
		unsigned short* notetrackRumbleMapValues;
		int playerAnimType;
		weapType_t weapType;
		weapClass_t weapClass;
		PenetrateType penetrateType;
		weapInventoryType_t inventoryType;
		weapFireType_t fireType;
		OffhandClass offhandClass;
		weapStance_t stance;
		FxEffectDef* viewFlashEffect;
		FxEffectDef* worldFlashEffect;
		SndAliasList* pickupSound;
		SndAliasList* pickupSoundPlayer;
		SndAliasList* ammoPickupSound;
		SndAliasList* ammoPickupSoundPlayer;
		SndAliasList* projectileSound;
		SndAliasList* pullbackSound;
		SndAliasList* pullbackSoundPlayer;
		SndAliasList* fireSound;
		SndAliasList* fireSoundPlayer;
		SndAliasList* fireSoundPlayerAkimbo;
		SndAliasList* fireStartSound;
		SndAliasList* fireStartSoundPlayer;
		SndAliasList* fireLoopSound;
		SndAliasList* fireLoopSoundPlayer;
		SndAliasList* fireStopSound;
		SndAliasList* fireStopSoundPlayer;
		SndAliasList* fireLastSound;
		SndAliasList* fireLastSoundPlayer;
		SndAliasList* emptyFireSound;
		SndAliasList* emptyFireSoundPlayer;
		SndAliasList* fireSoundVacuum;
		SndAliasList* fireSoundPlayerVacuum;
		SndAliasList* fireSoundPlayerAkimboVacuum;
		SndAliasList* fireStartSoundVacuum;
		SndAliasList* fireStartSoundPlayerVacuum;
		SndAliasList* fireLoopSoundVacuum;
		SndAliasList* fireLoopSoundPlayerVacuum;
		SndAliasList* fireStopSoundVacuum;
		SndAliasList* fireStopSoundPlayerVacuum;
		SndAliasList* fireLastSoundVacuum;
		SndAliasList* fireLastSoundPlayerVacuum;
		SndAliasList* emptyFireSoundVacuum;
		SndAliasList* emptyFireSoundPlayerVacuum;
		SndAliasList* meleeSwipeSound;
		SndAliasList* meleeSwipeSoundPlayer;
		SndAliasList* meleeHitSound;
		SndAliasList* meleeMissSound;
		SndAliasList* rechamberSound;
		SndAliasList* rechamberSoundPlayer;
		SndAliasList* reloadSound;
		SndAliasList* reloadSoundPlayer;
		SndAliasList* reloadEmptySound;
		SndAliasList* reloadEmptySoundPlayer;
		SndAliasList* reloadStartSound;
		SndAliasList* reloadStartSoundPlayer;
		SndAliasList* reloadEndSound;
		SndAliasList* reloadEndSoundPlayer;
		SndAliasList* rechargeSound;
		SndAliasList* rechargeSoundPlayer;
		SndAliasList* rechargeStartSound;
		SndAliasList* rechargeStartSoundPlayer;
		SndAliasList* rechargeEndSound;
		SndAliasList* rechargeEndSoundPlayer;
		SndAliasList* detonateSound;
		SndAliasList* detonateSoundPlayer;
		SndAliasList* nightVisionWearSound;
		SndAliasList* nightVisionWearSoundPlayer;
		SndAliasList* nightVisionRemoveSound;
		SndAliasList* nightVisionRemoveSoundPlayer;
		SndAliasList* altSwitchSound;
		SndAliasList* altSwitchSoundPlayer;
		SndAliasList* raiseSound;
		SndAliasList* raiseSoundPlayer;
		SndAliasList* firstRaiseSound;
		SndAliasList* firstRaiseSoundPlayer;
		SndAliasList* putawaySound;
		SndAliasList* putawaySoundPlayer;
		SndAliasList* scanSound;
		SndAliasList** bounceSound;
		FxEffectDef* viewShellEjectEffect;
		FxEffectDef* worldShellEjectEffect;
		FxEffectDef* viewLastShotEjectEffect;
		FxEffectDef* worldLastShotEjectEffect;
		Material* laserMaterial;
		Material* laserEndPointMaterial;
		Material* reticleCenter;
		Material* reticleSide;
		int iReticleCenterSize;
		int iReticleSideSize;
		int iReticleMinOfs;
		activeReticleType_t activeReticleType;
		Material* remoteTurretReticleSide;
		Material* remoteTurretLockOnReticle;
		Material* remoteTurretOutOfSightReticle;
		int remoteTurretReticleSideSize;
		int remoteTurretLockOnReticleSize;
		int remoteTurretOutOfSightReticleSize;
		int remoteTurretReticleMinOfs;
		float remoteTurretReticleSidePos;
		bool useRemoteTurretReticle;
		float vStandMove[3];
		float vStandRot[3];
		float strafeMove[3];
		float strafeRot[3];
		float vDuckedOfs[3];
		float vDuckedMove[3];
		float vDuckedRot[3];
		float vProneOfs[3];
		float vProneMove[3];
		float vProneRot[3];
		float fPosMoveRate;
		float fPosProneMoveRate;
		float fStandMoveMinSpeed;
		float fDuckedMoveMinSpeed;
		float fProneMoveMinSpeed;
		float fPosRotRate;
		float fPosProneRotRate;
		float fStandRotMinSpeed;
		float fDuckedRotMinSpeed;
		float fProneRotMinSpeed;
		float vDtpOfs[3];
		float vDtpRot[3];
		float vDtpBob[2];
		float fDtpCycleScale;
		//XModel** worldModel;
		//XModel* worldClipModel;
		//XModel* rocketModel;
		//XModel* knifeModel;
		//XModel* worldKnifeModel;
		Material* hudIcon;
		weaponIconRatioType_t hudIconRatio;
		Material* pickupIcon;
		weaponIconRatioType_t pickupIconRatio;
		Material* ammoCounterIcon;
		weaponIconRatioType_t ammoCounterIconRatio;
		ammoCounterClipType_t ammoCounterClip;
		int iStartAmmo;
		const char* szAmmoName;
		int iAmmoIndex;
		const char* szClipName;
		int iClipIndex;
		int iMaxAmmo;
		int shotCount;
		const char* szSharedAmmoCapName;
		int iSharedAmmoCapIndex;
		int iSharedAmmoCap;
		int damage;
		int playerDamage;
		int iMeleeDamage;
		int iDamageType;
		int iFireDelay;
		int iMeleeDelay;
		int meleeChargeDelay;
		int iDetonateDelay;
		int iRechamberTime;
		int rechamberTimeOneHanded;
		int iRechamberBoltTime;
		int iHoldFireTime;
		int iDetonateTime;
		int iMeleeTime;
		int meleeChargeTime;
		int iReloadTime;
		int reloadShowRocketTime;
		int iReloadEmptyTime;
		int iReloadAddTime;
		int iReloadStartTime;
		int iReloadBulletAnimTime;
		int iReloadStartAddTime;
		int iReloadEndTime;
		int iDropTime;
		int iRaiseTime;
		int iAltDropTime;
		int quickDropTime;
		int quickRaiseTime;
		int iBreachRaiseTime;
		int iEmptyRaiseTime;
		int iEmptyDropTime;
		int sprintInTime;
		int sprintLoopTime;
		int sprintOutTime;
		int stunnedTimeBegin;
		int stunnedTimeLoop;
		int stunnedTimeEnd;
		int nightVisionWearTime;
		int nightVisionWearTimeFadeOutEnd;
		int nightVisionWearTimePowerUp;
		int nightVisionRemoveTime;
		int nightVisionRemoveTimePowerDown;
		int nightVisionRemoveTimeFadeInStart;
		int fuseTime;
		int aiFuseTime;
		int contFireInTime;
		int contFireOutTime;
		float autoAimRange;
		float aimAssistRange;
		float aimAssistRangeAds;
		float aimPadding;
		float enemyCrosshairRange;
		float moveSpeedScale;
		float adsMoveSpeedScale;
		float sprintDurationScale;
		float fAdsZoomInFrac;
		float fAdsZoomOutFrac;
		Material* overlayMaterial;
		Material* overlayMaterialLowRes;
		Material* overlayMaterialEMP;
		Material* overlayMaterialEMPLowRes;
		weapOverlayReticle_t overlayReticle;
		WeapOverlayInteface_t overlayInterface;
		float overlayWidth;
		float overlayHeight;
		float overlayWidthSplitscreen;
		float overlayHeightSplitscreen;
		float fAdsBobFactor;
		float fAdsViewBobMult;
		float fHipSpreadStandMin;
		float fHipSpreadDuckedMin;
		float fHipSpreadProneMin;
		float hipSpreadStandMax;
		float hipSpreadDuckedMax;
		float hipSpreadProneMax;
		float fHipSpreadDecayRate;
		float fHipSpreadFireAdd;
		float fHipSpreadTurnAdd;
		float fHipSpreadMoveAdd;
		float fHipSpreadDuckedDecay;
		float fHipSpreadProneDecay;
		float fHipReticleSidePos;
		float fAdsIdleAmount;
		float fHipIdleAmount;
		float adsIdleSpeed;
		float hipIdleSpeed;
		float fIdleCrouchFactor;
		float fIdleProneFactor;
		float fGunMaxPitch;
		float fGunMaxYaw;
		float adsIdleLerpStartTime;
		float adsIdleLerpTime;
		float swayMaxAngle;
		float swayLerpSpeed;
		float swayPitchScale;
		float swayYawScale;
		float swayHorizScale;
		float swayVertScale;
		float swayShellShockScale;
		float adsSwayMaxAngle;
		float adsSwayLerpSpeed;
		float adsSwayPitchScale;
		float adsSwayYawScale;
		float adsSwayHorizScale;
		float adsSwayVertScale;
		float adsViewErrorMin;
		float adsViewErrorMax;
		//PhysCollmap* physCollmap;
		float dualWieldViewModelOffset;
		weaponIconRatioType_t killIconRatio;
		int iReloadAmmoAdd;
		int iReloadStartAdd;
		int ammoDropStockMin;
		int ammoDropClipPercentMin;
		int ammoDropClipPercentMax;
		int ammoRechargeTime;
		int ammoRechargeAmount;
		int ammoRechargeDelay;
		int iExplosionRadius;
		int iExplosionRadiusMin;
		int iExplosionInnerDamage;
		int iExplosionOuterDamage;
		float damageConeAngle;
		float bulletExplDmgMult;
		float bulletExplRadiusMult;
		int iProjectileSpeed;
		int iProjectileSpeedUp;
		int iProjectileSpeedForward;
		int iProjectileActivateDist;
		float projLifetime;
		float timeToAccelerate;
		float projectileCurvature;
		//XModel* projectileModel;
		weapProjExposion_t projExplosion;
		FxEffectDef* projExplosionEffect;
		FxEffectDef* projDudEffect;
		SndAliasList* projExplosionSound;
		SndAliasList* projDudSound;
		SndAliasList* projExplosionSoundVacuum;
		SndAliasList* projDudSoundVacuum;
		WeapStickinessType stickiness;
		float lowAmmoWarningThreshold;
		float ricochetChance;
		float grenadeAirBurstTraceOffset;
		float grenadeAirBurstTraceRange;
		float grenadeAirBurstExtraDistance;
		float* parallelBounce;
		float* perpendicularBounce;
		FxEffectDef* projTrailEffect;
		FxEffectDef* projBeaconEffect;
		float vProjectileColor[3];
		guidedMissileType_t guidedMissileType;
		float maxSteeringAccel;
		int projIgnitionDelay;
		FxEffectDef* projIgnitionEffect;
		SndAliasList* projIgnitionSound;
		float fAdsAimPitch;
		float fAdsCrosshairInFrac;
		float fAdsCrosshairOutFrac;
		int adsGunKickReducedKickBullets;
		float adsGunKickReducedKickPercent;
		float fAdsGunKickPitchMin;
		float fAdsGunKickPitchMax;
		float fAdsGunKickYawMin;
		float fAdsGunKickYawMax;
		float fAdsGunKickAccel;
		float fAdsGunKickSpeedMax;
		float fAdsGunKickSpeedDecay;
		float fAdsGunKickStaticDecay;
		float fAdsViewKickPitchMin;
		float fAdsViewKickPitchMax;
		float fAdsViewKickYawMin;
		float fAdsViewKickYawMax;
		float fAdsViewScatterMin;
		float fAdsViewScatterMax;
		float fAdsSpread;
		int hipGunKickReducedKickBullets;
		float hipGunKickReducedKickPercent;
		float fHipGunKickPitchMin;
		float fHipGunKickPitchMax;
		float fHipGunKickYawMin;
		float fHipGunKickYawMax;
		float fHipGunKickAccel;
		float fHipGunKickSpeedMax;
		float fHipGunKickSpeedDecay;
		float fHipGunKickStaticDecay;
		float fHipViewKickPitchMin;
		float fHipViewKickPitchMax;
		float fHipViewKickYawMin;
		float fHipViewKickYawMax;
		float fHipViewScatterMin;
		float fHipViewScatterMax;
		float fightDist;
		float maxDist;
		const char* accuracyGraphName[2];
		float (*originalAccuracyGraphKnots[2])[2];
		unsigned short originalAccuracyGraphKnotCount[2];
		int iPositionReloadTransTime;
		float leftArc;
		float rightArc;
		float topArc;
		float bottomArc;
		float accuracy;
		bool preferManualTarget;
		float aiSpread;
		float playerSpread;
		float minTurnSpeed[2];
		float maxTurnSpeed[2];
		float pitchConvergenceTime;
		float yawConvergenceTime;
		float suppressTime;
		float maxRange;
		float fAnimHorRotateInc;
		float fPlayerPositionDist;
		const char* szUseHintString;
		const char* dropHintString;
		int iUseHintStringIndex;
		int dropHintStringIndex;
		float horizViewJitter;
		float vertViewJitter;
		float scanSpeed;
		float scanAccel;
		int scanPauseTime;
		const char* szScript;
		const char* szScriptModelAmmo;
		float fOOPosAnimLength[2];
		int minDamage;
		int minPlayerDamage;
		int closeDamage;
		float fMinCloseDamageRange;
		float fMaxCloseDamageRange;
		float fMaxDamageRange;
		float fMinDamageRange;
		float destabilizationRateTime;
		float destabilizationCurvatureMax;
		int destabilizeDistance;
		float* locationDamageMultipliers;
		const char* fireRumble;
		const char* meleeImpactRumble;
		TracerDef* tracerType;
		LaserDef* laserType;
		float turretScopeZoomRate;
		float turretScopeZoomMin;
		float turretScopeZoomMax;
		float turretOverheatUpRate;
		float turretOverheatDownRate;
		float turretOverheatPenalty;
		SndAliasList* turretOverheatSound;
		FxEffectDef* turretOverheatEffect;
		const char* turretBarrelSpinRumble;
		float turretBarrelSpinSpeed;
		float turretBarrelSpinUpTime;
		float turretBarrelSpinDownTime;
		bool turretBarrelSpinDownAfterEveryShot;
		SndAliasList* turretBarrelSpinMaxSnd;
		SndAliasList* turretBarrelSpinUpSnd[4];
		SndAliasList* turretBarrelSpinDownSnd[4];
		SndAliasList* missileConeSoundAlias;
		SndAliasList* missileConeSoundAliasAtBase;
		float missileConeSoundRadiusAtTop;
		float missileConeSoundRadiusAtBase;
		float missileConeSoundHeight;
		float missileConeSoundOriginOffset;
		float missileConeSoundVolumescaleAtCore;
		float missileConeSoundVolumescaleAtEdge;
		float missileConeSoundVolumescaleCoreSize;
		float missileConeSoundPitchAtTop;
		float missileConeSoundPitchAtBottom;
		float missileConeSoundPitchTopSize;
		float missileConeSoundPitchBottomSize;
		float missileConeSoundCrossfadeTopSize;
		float missileConeSoundCrossfadeBottomSize;
		float laserBeamRadius;
		float laserEndPointRadius;
		bool sharedAmmo;
		bool lockonSupported;
		bool requireLockonToFire;
		bool bigExplosion;
		bool noAdsWhenMagEmpty;
		bool avoidDropCleanup;
		bool inheritsPerks;
		bool showLaserWhileFiring;
		bool useContinuousAudio;
		bool crosshairColorChange;
		bool bRifleBullet;
		bool armorPiercing;
		bool bBoltAction;
		bool disableBob;
		bool overheats;
		bool aimDownSight;
		bool bRechamberWhileAds;
		bool bBulletExplosiveDamage;
		bool bCookOffHold;
		bool bClipOnly;
		bool noAmmoPickup;
		bool adsFireOnly;
		bool cancelAutoHolsterWhenEmpty;
		bool disableSwitchToWhenEmpty;
		bool suppressAmmoReserveDisplay;
		bool ammoRecharges;
		bool laserSightDuringNightvision;
		bool markableViewmodel;
		bool noDualWield;
		bool flipKillIcon;
		bool bNoPartialReload;
		bool bSegmentedReload;
		bool blocksProne;
		bool silenced;
		bool isRollingGrenade;
		bool explodesOnGround;
		bool projExplosionEffectForceNormalUp;
		bool bProjImpactExplode;
		bool stickToPlayers;
		bool hasDetonator;
		bool disableFiring;
		bool timedDetonation;
		bool projectileCrumples;
		bool rotate;
		bool holdButtonToThrow;
		bool freezeMovementWhenFiring;
		bool thermalScope;
		bool xRay;
		bool altModeSameWeapon;
		bool turretBarrelSpinEnabled;
		bool missileConeSoundEnabled;
		bool missileConeSoundPitchshiftEnabled;
		bool missileConeSoundCrossfadeEnabled;
		bool offhandHoldIsCancelable;
		airBurstGrenadeHUD_t airBurstGrenadeHUD;
		int dtpInTime;
		int dtpLoopTime;
		int dtpOutTime;
		float xrayConeAngle;
		float xrayConeLength;
		bool doGibbing;
		float maxGibDistance;
	};

	enum ImpactType : int
	{
		IMPACT_TYPE_NONE = 0x0,
		IMPACT_TYPE_BULLET_SMALL = 0x1,
		IMPACT_TYPE_BULLET_LARGE = 0x2,
		IMPACT_TYPE_BULLET_HEAVY = 0x3,
		IMPACT_TYPE_BULLET_AP = 0x4,
		IMPACT_TYPE_BULLET_EXPLODE = 0x5,
		IMPACT_TYPE_SHOTGUN = 0x6,
		IMPACT_TYPE_SHOTGUN_EXPLODE = 0x7,
		IMPACT_TYPE_GRENADE_BOUNCE = 0x8,
		IMPACT_TYPE_GRENADE_EXPLODE = 0x9,
		IMPACT_TYPE_ROCKET_EXPLODE = 0xA,
		IMPACT_TYPE_PROJECTILE_DUD = 0xB,
		IMPACT_TYPE_LASER = 0xC,
		IMPACT_TYPE_STREAMGUN = 0xD,
		IMPACT_TYPE_RAILGUN = 0xE,
		IMPACT_TYPE_EXPLODE_SML = 0xF,
		IMPACT_TYPE_EXPLODE_MED = 0x10,
		IMPACT_TYPE_EXPLODE_LRG = 0x11,
		IMPACT_TYPE_VACUUM_BULLET_SMALL = 0x12,
		IMPACT_TYPE_VACUUM_BULLET_LARGE = 0x13,
		IMPACT_TYPE_VACUUM_BULLET_HEAVY = 0x14,
		IMPACT_TYPE_VACUUM_BULLET_AP = 0x15,
		IMPACT_TYPE_VACUUM_BULLET_EXPLODE = 0x16,
		IMPACT_TYPE_VACUUM_SHOTGUN = 0x17,
		IMPACT_TYPE_VACUUM_SHOTGUN_EXPLODE = 0x18,
		IMPACT_TYPE_VACUUM_GRENADE_BOUNCE = 0x19,
		IMPACT_TYPE_VACUUM_GRENADE_EXPLODE = 0x1A,
		IMPACT_TYPE_VACUUM_ROCKET_EXPLODE = 0x1B,
		IMPACT_TYPE_VACUUM_PROJECTILE_DUD = 0x1C,
		IMPACT_TYPE_VACUUM_LASER = 0x1D,
		IMPACT_TYPE_VACUUM_STREAMGUN = 0x1E,
		IMPACT_TYPE_VACUUM_RAILGUN = 0x1F,
		IMPACT_TYPE_VACUUM_EXPLODE_SML = 0x20,
		IMPACT_TYPE_VACUUM_EXPLODE_MED = 0x21,
		IMPACT_TYPE_VACUUM_EXPLODE_LRG = 0x22,

		IMPACT_TYPE_COUNT = 0x23,
	};

	struct WeaponCompleteDef
	{
		const char* szInternalName;
		WeaponDef* weapDef;
		const char* szDisplayName;
		unsigned short* hideTags;
		const char** szXAnims;
		float fAdsZoomFov;
		int iAdsTransInTime;
		int iAdsTransOutTime;
		int iClipSize;
		ImpactType impactType;
		int iFireTime;
		float shotsPerSecondAi;
		weaponIconRatioType_t dpadIconRatio;
		float penetrateMultiplier;
		float fAdsViewKickCenterSpeed;
		float fHipViewKickCenterSpeed;
		const char* szAltWeaponName;
		unsigned int altWeaponIndex;
		int iAltRaiseTime;
		Material* killIcon;
		Material* dpadIcon;
		int fireAnimLength;
		int iFirstRaiseTime;
		int ammoDropStockMax;
		float adsDofStart;
		float adsDofEnd;
		unsigned short accuracyGraphKnotCount[2];
		float (*accuracyGraphKnots[2])[2];
		bool motionTracker;
		bool enhanced;
		bool dpadIconShowsAmmo;
	};
}
