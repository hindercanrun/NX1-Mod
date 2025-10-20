#pragma once

// make the compiler happy
struct SndVfCurve;
struct SndLpfCurve;

namespace Assets
{
	struct tWAVEFORMATEX
	{
		unsigned short wFormatTag;
		unsigned short nChannels;
		unsigned int nSamplesPerSec;
		unsigned int nAvgBytesPerSec;
		unsigned short nBlockAlign;
		unsigned short wBitsPerSample;
		unsigned short cbSize;
	};

	struct XMA2WAVEFORMATEX
	{
		tWAVEFORMATEX wfx;
		unsigned short NumStreams;
		unsigned int ChannelMask;
		unsigned int SamplesEncoded;
		unsigned int BytesPerBlock;
		unsigned int PlayBegin;
		unsigned int PlayLength;
		unsigned int LoopBegin;
		unsigned int LoopLength;
		unsigned char LoopCount;
		unsigned char EncoderVersion;
		unsigned short BlockCount;
	};

	struct XMA2DataAligned
	{
	  unsigned char* p_audioData;
	  unsigned int audioBytes;
	};

	struct XA2SeekTable
	{
		unsigned int* p_seekData;
		unsigned int seekBytes;
	};

	struct PlatSound
	{
		XMA2DataAligned data;
		XMA2WAVEFORMATEX format;
		XA2SeekTable seekTable;
	};

	struct PrimedInfo
	{
		unsigned int crc;
		unsigned int dataSizeLoaded;
		unsigned int dataSizeStreamed;
		unsigned char format;
	};

	struct StreamFileNameRaw
	{
		const char* p_dir;
		const char* p_name;
	};

	struct StreamFileNamePacked
	{
		unsigned int offset;
		unsigned int length;
	};

	union StreamFileInfo
	{
		StreamFileNameRaw raw;
		StreamFileNamePacked packed;
	};

	struct StreamFileName
	{
		unsigned int fileIndex;
		StreamFileInfo info;
	};

	struct LoadedSound
	{
		const char* p_name;
		PlatSound sound;
		PrimedInfo info;
		StreamFileName streamFilename;
	};

	struct StreamedSound
	{
		StreamFileName filename;
		unsigned int totalMsec;
		unsigned char compressed;
	};

	union SoundFileRef
	{
		LoadedSound* loadSnd;
		StreamedSound streamSnd;
	};

	struct SoundFile
	{
		unsigned char type;
		unsigned char exists;
		SoundFileRef ref;
	};

	struct SpeakerLevels
	{
		unsigned int speaker;
		int numLevels;
		float levels[2];
	};

	struct ChannelMap
	{
		int speakerCount;
		SpeakerLevels speakers[6];
	};

	struct SpeakerMap
	{
		bool isDefault;
		const char* p_name;
		ChannelMap channelMaps[2][2];
	};

	struct SndDuckMap
	{
		const char* p_name;
		float duckAmount;
		int attack;
		int sustain;
		int release;
		unsigned long long entChannelMask;
	};

	struct SndAlias
	{
		const char* p_aliasName;
		const char* p_subtitle;
		const char* p_secondaryAliasName;
		const char* p_chainAliasName;
		const char* p_mixerGroup;
		SoundFile* p_soundFile;
		int sequence;
		float volMin;
		float volMax;
		float pitchMin;
		float pitchMax;
		float distMin;
		float distMax;
		float velocityMin;
		int flags;
		float masterSlavePercentage;
		float probability;
		float lfeVol;
		float centerPercentage;
		int startDelay;
		SndVfCurve* p_volumeFalloffCurve;
		SndLpfCurve* p_lpfCurve;
		float envelopMin;
		float envelopMax;
		float envelopPercentage;
		SpeakerMap* p_speakerMap;
		short adsrSettingIndex;
		char instanceLimit;
		float reverbSend;
		SndDuckMap* p_duckMap;
	};

	struct SndAliasList
	{
		const char* p_aliasName;
		SndAlias* p_head;
		int count;
	};
}
