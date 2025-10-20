#pragma once

namespace Assets
{
	enum VehicleType : int
	{
		VEH_WHEELS_4 = 0x0,
		VEH_TANK = 0x1,
		VEH_TANK_WHEELS_4 = 0x2,
		VEH_PLANE = 0x3,
		VEH_BOAT = 0x4,
		VEH_ARTILLERY = 0x5,
		VEH_HELICOPTER = 0x6,
		VEH_SNOWMOBILE = 0x7,
		VEH_LUNAR_ROVER = 0x8,

		VEH_TYPE_COUNT = 0x9,
	};

	enum VehicleAxleType : int
	{
		VEH_AXLE_FRONT = 0x0,
		VEH_AXLE_REAR = 0x1,
		VEH_AXLE_ALL = 0x2,

		VEH_AXLE_COUNT = 0x3,
	};

	struct VehiclePhysDef
	{
		int physicsEnabled;
		const char* physPresetName;
		const PhysPreset *physPreset;
		const char* accelGraphName;
		VehicleAxleType steeringAxle;
		VehicleAxleType powerAxle;
		VehicleAxleType brakingAxle;
		float topSpeed;
		float reverseSpeed;
		float maxVelocity;
		float maxPitch;
		float maxRoll;
		float suspensionTravelFront;
		float suspensionTravelRear;
		float suspensionStrengthFront;
		float suspensionDampingFront;
		float suspensionStrengthRear;
		float suspensionDampingRear;
		float frictionBraking;
		float frictionCoasting;
		float frictionTopSpeed;
		float frictionSide;
		float frictionSideRear;
		float velocityDependentSlip;
		float rollStability;
		float rollResistance;
		float pitchResistance;
		float yawResistance;
		float uprightStrengthPitch;
		float uprightStrengthRoll;
		float targetAirPitch;
		float airYawTorque;
		float airPitchTorque;
		float minimumMomentumForCollision;
		float collisionLaunchForceScale;
		float wreckedMassScale;
		float wreckedBodyFriction;
		float minimumJoltForNotify;
		float slipThresholdFront;
		float slipThresholdRear;
		float slipFricScaleFront;
		float slipFricScaleRear;
		float slipFricRateFront;
		float slipFricRateRear;
		float slipYawTorque;
	};

	struct VehicleDef
	{
		const char* name;
		VehicleType type;
		const char* useHintString;
		int health;
		int quadBarrel;
		float texScrollScale;
		float topSpeed;
		float accel;
		float rotRate;
		float rotAccel;
		float maxBodyPitch;
		float maxBodyRoll;
		float collisionRadius;
		int enableReticleColoring;
		float fakeBodyAccelPitch;
		float fakeBodyAccelRoll;
		float fakeBodyVelPitch;
		float fakeBodyVelRoll;
		float fakeBodySideVelPitch;
		float fakeBodyPitchStrength;
		float fakeBodyRollStrength;
		float fakeBodyPitchDampening;
		float fakeBodyRollDampening;
		float fakeBodyBoatRockingAmplitude;
		float fakeBodyBoatRockingPeriod;
		float fakeBodyBoatRockingRotationPeriod;
		float fakeBodyBoatRockingFadeoutSpeed;
		float boatBouncingMinForce;
		float boatBouncingMaxForce;
		float boatBouncingRate;
		float boatBouncingFadeinSpeed;
		float boatBouncingFadeoutSteeringAngle;
		float collisionDamage;
		float collisionSpeed;
		float killcamOffset[3];
		int playerProtected;
		int bulletDamage;
		int armorPiercingDamage;
		int grenadeDamage;
		int projectileDamage;
		int projectileSplashDamage;
		int heavyExplosiveDamage;
		int hasSplitShrouds;
		float shroudTravelUp;
		float shroudTravelDown;
		VehiclePhysDef vehPhysDef;
		float boostDuration;
		float boostRechargeTime;
		float boostAcceleration;
		float suspensionTravel;
		float maxSteeringAngle;
		float steeringLerp;
		float minSteeringScale;
		float minSteeringSpeed;
		int camLookEnabled;
		float camLerp;
		float camPitchInfluence;
		float camRollInfluence;
		float camFovIncrease;
		float camFovOffset;
		float camFovSpeed;
		const char* turretWeaponName;
		WeaponCompleteDef* turretWeapon;
		float turretHorizSpanLeft;
		float turretHorizSpanRight;
		float turretVertSpanUp;
		float turretVertSpanDown;
		float turretRotRate;
		SndAliasList* turretSpinSnd;
		SndAliasList* turretStopSnd;
		int trophyEnabled;
		int trophyIsTurret;
		float trophyRadius;
		float trophyInactiveRadius;
		int trophyAmmoCount;
		float trophyReloadTime;
		float trophyMaximumAngle;
		unsigned short trophyTags[4];
		Material* compassFriendlyIcon;
		Material* compassEnemyIcon;
		int compassIconWidth;
		int compassIconHeight;
		Material* nx_compassFriendlyIcon;
		Material* nx_compassEnemyIcon;
		int nx_compassIconWidth;
		int nx_compassIconHeight;
		SndAliasList* idleLowSnd;
		SndAliasList* idleHighSnd;
		SndAliasList* engineLowSnd;
		SndAliasList* engineHighSnd;
		float engineSndSpeed;
		SndAliasList* engineStartUpSnd;
		int engineStartUpLength;
		SndAliasList* engineShutdownSnd;
		SndAliasList* engineIdleSnd;
		SndAliasList* engineSustainSnd;
		SndAliasList* engineRampUpSnd;
		int engineRampUpLength;
		SndAliasList* engineRampDownSnd;
		int engineRampDownLength;
		SndAliasList* suspensionSoftSnd;
		float suspensionSoftCompression;
		SndAliasList* suspensionHardSnd;
		float suspensionHardCompression;
		SndAliasList* collisionSnd;
		float collisionBlendSpeed;
		SndAliasList* speedSnd;
		float speedSndBlendSpeed;
		const char* surfaceSndPrefix;
		SndAliasList* surfaceSnds[31];
		float surfaceSndBlendSpeed;
		float speedOfSound;
		int useDoppler;
		float slideVolume;
		float slideBlendSpeed;
		float inAirPitch;
	};

	void Dump_VehicleDef(const VehicleDef* vehicleDef);
}
