/*
	A52 / AC-3 Decompression Codec
	2004, Shepmaster <shepmaster@applesolutions.com>
	
	Uses code from the liba52 project and the CoreAudio SDK.
*/

#if !defined(__ACShepA52Decoder_h__)
#define __ACShepA52Decoder_h__

//=============================================================================
//	Includes
//=============================================================================

#include "ACShepA52Codec.h"
#include "a52.h"

//=============================================================================
//	ACShepA52Decoder
//
//	This class decodes A/52 and AC-3 data.
//	We support 16- and 32-bit signed integer, as well as floating point.
//=============================================================================

class ACShepA52Decoder
:
	public ACShepA52Codec
{

//	Construction/Destruction
public:
					ACShepA52Decoder(OSType theSubType);
	virtual			~ACShepA52Decoder();

	virtual void	Initialize(const AudioStreamBasicDescription* inInputFormat, const AudioStreamBasicDescription* inOutputFormat, const void* inMagicCookie, UInt32 inMagicCookieByteSize);
	virtual void	Uninitialize();
	virtual void	Reset();

// 	Information Gathering
public:
	UInt32 ParseCookieAtom(const uint8_t* inAtom, UInt32 inAtomMaxSize);
	void ParseCookie(const uint8_t* inMagicCookie, UInt32 inMagicCookieByteSize);
	virtual void 	GetPropertyInfo(AudioCodecPropertyID inPropertyID, UInt32& outPropertyDataSize, Boolean& outWritable);
	virtual void	GetProperty(AudioCodecPropertyID inPropertyID, UInt32& ioPropertyDataSize, void* outPropertyData);
	virtual void 	SetProperty(AudioCodecPropertyID inPropertyID, UInt32 inPropertyDataSize, const void* inPropertyData);

//	Format Information
public:
	virtual void	SetCurrentInputFormat(const AudioStreamBasicDescription& inInputFormat);
	virtual void	SetCurrentOutputFormat(const AudioStreamBasicDescription& inOutputFormat);
	virtual UInt32	GetVersion() const;

//	Output Data Operations
public:
	virtual void	AppendInputData(const void* inInputData, UInt32& ioInputDataByteSize, UInt32& ioNumberPackets, const AudioStreamPacketDescription* inPacketDescription);
	virtual UInt32	ProduceOutputPackets(void* outOutputData, UInt32& ioOutputDataByteSize, UInt32& ioNumberPackets, AudioStreamPacketDescription* outPacketDescription);


//	Implementation
private:
	void	UpgradeOldPrefs();
	void	DetermineStreamParameters();
	UInt32  SyncA52Stream(UInt32 &bytes_to_read, Byte *input_data, int &a52_flags, int &a52_samplerate, int &a52_bitrate, bool shouldResync);
	UInt32  AppendPacket(const void* inInputData, UInt32 inInputDataSize, UInt32 bufferStartOffset, UInt32 offset, UInt32& packetSize);		
	void getChannelMap(int a52_flags, int chanMap[6]);
	template <class outPtr, class inPtr>
	UInt32 InterleaveSamples(void *output_data_untyped, UInt32 output_data_offset, sample_t *output_samples, int a52_flags);

	a52_state_t *decoder_state;
	
	UInt32  kIntPCMOutFormatFlag;
	UInt32  kFloatPCMOutFormatFlag;
	
	UInt32  total_frames;
	UInt32  total_bytes;
	
	bool	firstInput;
	int		fullChannelMap[6];
	AudioChannelLayoutTag	layoutTag;
	
	//For badly packetized data
	UInt32	remainingBytesFromLastFrame;
	Byte	beginningOfIncompleteHeader[6];
	UInt32	beginningOfIncompleteHeaderSize;
	
	//Prefs
	int		TwoChannelMode;
	double	dynamicRangeCompression;
	bool	passthrough;
};

#endif
