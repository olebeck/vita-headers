/**
 * \usergroup{SceNgs}
 * \usage{psp2/ngs.h,SceNgsUser_stub,SCE_SYSMODULE_NGS}
 */


#ifndef _PSP2_NGS_H_
#define _PSP2_NGS_H_

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_NGS_MAX_SYSTEM_CHANNELS (2) // stereo

typedef SceUInt32 SceNgsHRack;
typedef SceUInt32 SceNgsHPatch;
typedef SceUInt32 SceNgsHSynSystem;
typedef SceUInt32 SceNgsHVoice;
typedef SceUInt32 SulphaNgsModuleQueryType;
typedef SceUInt32 SceNgsModuleID;
typedef SceUInt32 SceNgsParamsID;

typedef struct SceNgsVoiceDefinition SceNgsVoiceDefinition;

typedef struct {
    SceNgsHVoice VoiceHandle;
    SceNgsHRack RackHandle;
    SceNgsModuleID ModuleID;
    SceInt32 CallbackData;
    SceInt32 CallbackData2;
    void *Callback;
    void *userdata;
} SceNgsCallbackInfo;

typedef struct {
    SceInt32 maxRacks;
    SceInt32 maxVoices;
    SceInt32 Granularity;
    SceInt32 SampleRate;
    SceInt32 MaxModules;
} SceNgsSystemInitParams;

typedef struct {
    SceInt32 NameOffset;
    SceUInt32 NameLength;
    SceInt32 PresetDataOffset;
    SceUInt32 SizePresetData;
    SceInt32 BypassFlagsOffset;
    SceUInt32 NumBypassFlags;
} SceNgsVoicePreset;

typedef struct {
    SceInt32 StartByteOffset;
    SceInt32 NumBytes;
    SceInt16 StartSkip;
    SceInt16 EndSkip;
    SceInt32 IsSuperPacket;
} SceNgsAT9SkipBufferInfo;

typedef struct {
    void *data;
    SceUInt32 size;
} SceNgsBufferInfo;

typedef struct {
    SceNgsHVoice VoiceSource;
    SceInt32 SourceOutputIndex;
    SceInt32 SourceOutputSubIndex;
    SceNgsHVoice VoiceDestination;
    SceInt32 TargetInputIndex;
} SceNgsPatchSetupInfo;

typedef struct {
    SceFloat32 m[SCE_NGS_MAX_SYSTEM_CHANNELS][SCE_NGS_MAX_SYSTEM_CHANNELS];
} SceNgsVolumeMatrix;

typedef struct {
    SceInt32 OutputChannels;
    SceInt32 InputChannels;
    SceNgsVolumeMatrix vols;
} SceNgsPatchRouteInfo;

typedef struct {
    struct SceNgsVoiceDefinition *voiceDefinition;
    SceInt32 Voices;
    SceInt32 ChannelsPerVoice;
    SceInt32 MaxPatchesPerInput;
    SceInt32 PatchesPerOutput;
    void *userdata;
} SceNgsRackDescription;

typedef struct {
    SceInt32 moduleId;
    SceInt32 chan;
} SceNgsModuleParamHeader;

typedef struct {
    SceUInt32 VoiceState;
    SceUInt32 NumModules;
    SceUInt32 NumInputs;
    SceUInt32 NumOutputs;
    SceUInt32 NumPatchesPerOutput;
    SceUInt32 UpdateCallsActive;
} SceNgsVoiceInfo;


typedef void (* SceNgsCallbackFunc)(const SceNgsCallbackInfo* callback_info);
typedef SceNgsCallbackFunc SceNgsErrorCallback;
typedef SceNgsCallbackFunc SceNgsRackReleaseCallbackFunc;


SceInt32 sceNgsAT9GetSectionDetails(SceInt32 offsetSamples, SceInt32 samples, SceInt32 countConfigData, SceNgsAT9SkipBufferInfo *at9InfoBuffer);

SceInt32 sceNgsModuleGetNumPresets(SceNgsHSynSystem handle, const SceNgsModuleID module, SceUInt32 *numPresets);
SceInt32 sceNgsModuleGetPreset(SceNgsHSynSystem handle, const SceNgsModuleID module, const SceUInt32 preset_index, SceNgsBufferInfo *bufferInfo);

SceInt32 sceNgsPatchCreateRouting(SceNgsPatchSetupInfo *patchInfo, SceNgsHPatch *handle);
SceInt32 sceNgsPatchRemoveRouting(SceNgsHPatch handle);
SceInt32 sceNgsPatchGetInfo(SceNgsHPatch handle, SceNgsPatchRouteInfo *routeInfo, SceNgsPatchSetupInfo *patchSetup);

SceInt32 sceNgsRackGetRequiredMemorySize(SceNgsHSynSystem handle, const SceNgsRackDescription *rackDesc, SceUInt32 *size);
SceInt32 sceNgsRackGetVoiceHandle(SceNgsHRack Rackhandle, const SceUInt32 index, SceNgsHVoice *VoiceHandle);
SceInt32 sceNgsRackInit(SceNgsHSynSystem SystemHandle, const SceNgsBufferInfo *bufferInfo, const SceNgsRackDescription *RackDesc, SceNgsHRack *RackHandle);
SceInt32 sceNgsRackRelease(SceNgsHRack RackHandle, const SceNgsRackReleaseCallbackFunc callback);
SceInt32 sceNgsRackSetParamErrorCallback(SceNgsHSynSystem handle, const SceNgsErrorCallback callback);

SceInt32 sceNgsSystemGetRequiredMemorySize(const SceNgsSystemInitParams* params, SceUInt32* size);
SceInt32 sceNgsSystemInit(void* memory, SceSize memsize, SceNgsSystemInitParams* params, SceNgsHSynSystem* handle);
SceInt32 sceNgsSystemLock(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemRelease(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemSetFlags(SceNgsHSynSystem handle, const SceUInt32 flags);
SceInt32 sceNgsSystemSetParamErrorCallback(SceNgsHSynSystem handle, const SceNgsErrorCallback callback);
SceInt32 sceNgsSystemUnlock(SceNgsHSynSystem handle);
SceInt32 sceNgsSystemUpdate(SceNgsHSynSystem handle);

SceInt32 sceNgsVoiceGetOutputPatch(SceNgsHVoice VoiceHandle, SceInt32 OutputIndex, SceInt32 SubIndex, SceNgsHPatch *PatchHandle);
SceInt32 sceNgsVoiceGetParamsOutOfRange(SceNgsHVoice handle, SceUInt32 module, char *debug);
SceInt32 sceNgsVoiceInit(SceNgsHVoice handle, const SceNgsVoicePreset *preset, const SceUInt32 InitFlags);
SceInt32 sceNgsVoiceKeyOff(SceNgsHVoice handle);
SceInt32 sceNgsVoiceKill(SceNgsHVoice handle);
SceInt32 sceNgsVoicePause(SceNgsHVoice handle);
SceInt32 sceNgsVoicePlay(SceNgsHVoice handle);
SceInt32 sceNgsVoiceResume(SceNgsHVoice handle);
SceInt32 sceNgsVoiceSetFinishedCallback(SceNgsHVoice handle, const SceNgsCallbackFunc callback, void *userdata);
SceInt32 sceNgsVoiceSetModuleCallback(SceNgsHVoice handle, const SceUInt32 module, const SceNgsCallbackFunc callback, void *userdata);
SceInt32 sceNgsVoiceSetPreset(SceNgsHVoice handle, const SceNgsVoicePreset *preset);
SceInt32 sceNgsVoiceLockParams(SceNgsHVoice handle, SceUInt32 module, SceNgsParamsID paramId, SceNgsBufferInfo *paramsBuffer);
SceInt32 sceNgsVoiceUnlockParams(SceNgsHVoice handle, SceUInt32 module);
SceInt32 sceNgsVoiceSetParamsBlock(SceNgsHVoice handle, SceNgsModuleParamHeader *paramData, SceUInt32 size, SceInt32 *errorCounter);
SceInt32 sceNgsVoiceBypassModule(SceNgsHVoice handle, const SceUInt32 module, SceUInt32 flag);
SceInt32 sceNgsVoiceGetStateData(SceNgsHVoice handle, const SceUInt32 module, void *mem, SceUInt32 size);
SceInt32 sceNgsVoiceGetInfo(SceNgsHVoice handle, SceNgsVoiceInfo *info);
SceInt32 sceNgsVoiceGetModuleType(SceNgsHVoice handle, const SceUInt32 module, SceNgsModuleID *moduleType);
SceInt32 sceNgsVoiceGetModuleBypass(SceNgsHVoice handle, const SceUInt32 module, SceUInt32 *bypassFlag);

SceInt32 sceNgsVoicePatchSetVolume(SceNgsHPatch PatchHandle, SceInt32 OutputChannel, SceInt32 InputChannel, SceFloat32 Volume);
SceInt32 sceNgsVoicePatchSetVolumes(SceNgsHPatch PatchHandle, SceInt32 OutputChannel, SceFloat32 *Volumes, SceInt32 CountVols);
SceInt32 sceNgsVoicePatchSetVolumesMatrix(SceNgsHPatch PatchHandle, SceNgsVolumeMatrix *Matrix);

const SceNgsVoiceDefinition* sceNgsVoiceDefGetAtrac9Voice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetCompressorSideChainBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetDelayBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetDistortionBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetEnvelopeBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetEqBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetMasterBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetMixerBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetPauserBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetPitchShiftBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetReverbBuss(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSasEmuVoice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamAtrac9Voice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetScreamVoice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleAtrac9Voice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetSimpleVoice(void);
const SceNgsVoiceDefinition* sceNgsVoiceDefGetTemplate1(void);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_NGS_H_ */