#pragma once

#include <atlcoll.h>
#include "../AgoraSDK/include/IAgoraRtcEngine.h"
#include "../AgoraSDK/include/IAgoraRtcEngine2.h"
#include "../AgoraSDK/include/IAgoraMediaEngine.h"

#include "AGEngineEventHandler.h"
#include "AGEventDef.h"

// #define ENABLE_CODEC	1

using namespace agora::rtc;
using namespace agora::media;

// 引擎标记位
#define AG_ENGFLAG_ENNETTEST	0x00000001
#define AG_ENGFLAG_ECHOTEST		0x00000002
#define AG_ENGFLAG_SPKPHTEST	0x00000004
#define AG_ENGFLAG_MICPHTEST	0x00000008
#define AG_ENGFLAG_VIDEOTEST	0x00000010

#define AG_ENGFLAG_AGCON		0x00000100	// 自动增益
#define AG_ENGFLAG_NSON			0x00000200	// 降噪
#define AG_ENGFLAG_AECON		0x00000400	// 回声消除

#define APP_ID				_T("YOUR APP ID")

typedef struct _SEI_INFO
{
	UINT	nUID;
	int		nIndex;
	int		x;
	int		y;
	int		nWidth;
	int		nHeight;

} SEI_INFO, *PSEI_INFO, *LPSEI_INFO;

enum VideoRenderType {
	kRenderWindowsD3D = 7, // only for windows
	kRenderWindowsD2D = 8, // only for windows
	kRenderWindowsGDI = 9, // only for windows
};

class CAgoraObject
{
public:
	~CAgoraObject(void);

	void SetNetworkTestFlag(BOOL bEnable);
	BOOL GetNetworkTestFlag();

	void SetEchoTestFlag(BOOL bEnable);
	BOOL GetEchoTestFlag();

	void SetSpeakerphoneTestFlag(BOOL bEnable);
	BOOL GetSpeakerphoneTestFlag();

	void SetMicrophoneTestFlag(BOOL bEnable);
	BOOL GetMicrophoneTestFlag();

	void SetVideoTestFlag(BOOL bEnable);
	BOOL GetVideoTestFlag();

	void SetMsgHandlerWnd(HWND hWnd);
	HWND GetMsgHandlerWnd();

	BOOL SetLogFilePath(LPCTSTR lpLogPath = NULL);
	
	BOOL SetVideoProfile(VIDEO_PROFILE_TYPE nVideoProfileIndex, BOOL bSwitchWidhtHeight = FALSE);
	BOOL SetVideoProfileEx(int nWidth, int nHeight, int nFrameRate, int nBitRate);
	BOOL SetVideoKeepPro(BOOL bEnable = FALSE);

	BOOL SetAudioProfile(AUDIO_PROFILE_TYPE audioProfile, AUDIO_SCENARIO_TYPE scenario);
	BOOL SetAudioRecordParam(int nSampleRate,int nChannel,int nSamplePerCall);

	BOOL JoinChannel(LPCTSTR lpChannelName, UINT nUID = 0, LPCSTR lpDynamicKey = NULL);
	BOOL LeaveCahnnel();
	CString GetChanelName();
	CString GetCallID();
	CString GetAppID() { return m_strAppID; };

	void SetAppCert(LPCTSTR lpAppCert) { m_strAppCert = lpAppCert; };
	CString GetAppCert() { return m_strAppCert; };

	void SetSelfUID(UINT nUID) { m_nSelfUID = nUID; };
	UINT GetSelfUID() { return m_nSelfUID; };

	BOOL EnableVideo(BOOL bEnable = TRUE);
	BOOL IsVideoEnabled();

	BOOL EnableScreenCapture(HWND hWnd, int nCapFPS = 15, LPCRECT lpCapRect = NULL, BOOL bEnable = TRUE,int nBitrate = 0);
	BOOL IsScreenCaptureEnabled();

	BOOL MuteLocalAudio(BOOL bMuted = TRUE);
	BOOL IsLocalAudioMuted();

	BOOL MuteAllRemoteAudio(BOOL bMuted = TRUE);
	BOOL IsAllRemoteAudioMuted();

	BOOL MuteLocalVideo(BOOL bMuted = TRUE);
	BOOL IsLocalVideoMuted();

	BOOL MuteAllRemoteVideo(BOOL bMuted = TRUE);
	BOOL IsAllRemoteVideoMuted();

	BOOL EnableLoopBack(BOOL bEnable = TRUE);
	BOOL IsLoopBackEnabled();

	BOOL SetChannelProfile(BOOL bBroadcastMode);
	BOOL IsBroadcastMode();
	
	void SetWantedRole(CLIENT_ROLE_TYPE role);
	int  GetWnatedRole() { return m_nWantRoleType; };

	BOOL SetClientRole(CLIENT_ROLE_TYPE role, LPCSTR lpPermissionKey = NULL);
	int  GetClientRole() { return m_nRoleType; };

	BOOL EnableExtendAudioCapture(BOOL bEnable, IAudioFrameObserver* lpAudioFrameObserver);
	BOOL EnableExtendVideoCapture(BOOL bEnable, IVideoFrameObserver* lpVideoFrameObserver);

	BOOL EnableAudioRecording(BOOL bEnable, LPCTSTR lpFilePath);

	BOOL EnableLastmileTest(BOOL bEnable);

	BOOL LocalVideoPreview(HWND hVideoWnd, BOOL bPreviewOn = TRUE);

	BOOL SetLogFilter(LOG_FILTER_TYPE logFilterType, LPCTSTR lpLogPath);

    BOOL SetEncryptionSecret(LPCTSTR lpKey, int nEncryptType = 0);

	BOOL EnableLocalRender(BOOL bEnable);
	BOOL EnableLocalMirrorImage(BOOL bMirrorLocal);

	BOOL SetVideoRenderType(int nType);

	BOOL EnableWebSdkInteroperability(BOOL bEnable);
	BOOL EnableLocalPublishLeftRotate90(BOOL bEnable);

    int CreateMessageStream();
    BOOL SendChatMessage(int nStreamID, LPCTSTR lpChatMessage);

	BOOL SetHighQualityAudioPreferences(BOOL bFullBand, BOOL bStereo, BOOL bFullBitrate);
	BOOL StartAudioMixing(LPCTSTR lpMusicPath, BOOL bLoopback, BOOL bReplace, int nCycle);
	BOOL StopAudioMixing();
	BOOL PauseAudioMixing();
	BOOL ResumeAudioMixing();
	
	BOOL EnableAudio(BOOL bEnable = TRUE);
	BOOL IsAudioEnabled();

	void SetSEIInfo(UINT nUID, LPSEI_INFO lpSEIInfo = NULL);
	void RemoveSEIInfo(UINT nUID);
	void RemoveAllSEIInfo();
	BOOL GetSEIInfo(UINT nUID, LPSEI_INFO lpSEIInfo);
	BOOL GetSEIInfoByIndex(int nIndex, LPSEI_INFO lpSEIInfo);
	int	 GetSEICount() { return m_mapSEIInfo.GetCount(); };
	BOOL EnableSEIPush(BOOL bEnable, COLORREF crBack);

	BOOL EnableH264Compatible();
	BOOL AdjustVolume(int nRcdVol, int nPlaybackVol, int nMixVol);
	void GetVolume(int *nRcdVol, int *nPlaybackVol, int *nMixVol);

	int GetAudioMixingPos();
	int GetAudioMixingDuration();

	void SetSelfResolution(int nWidth, int nHeight);
	void GetSelfResolution(int *nWidth, int *nHeight);

	static IRtcEngine *GetEngine();
	
	static CString GetSDKVersion();
	static CString GetSDKVersionEx();
	static BOOL EnableWhiteboardVer(BOOL bEnable);
	static BOOL EnableWhiteboardFeq(BOOL bEnable);

	void setPublishParam(const AGE_PUBLISH_PARAM &publishparam);
	void getPublishParam(AGE_PUBLISH_PARAM &publishParam);
	bool enablePublish(bool enable = true);

	BOOL setAudioAEC(BOOL bEnable = FALSE);
	BOOL setAudioNS(BOOL bEnable = FALSE);
	BOOL setAudioAgcOn(BOOL bEnable = FALSE);

protected:
	CAgoraObject(void);

private:
	DWORD	m_dwEngineFlag;
	static  CAgoraObject	*m_lpAgoraObject;
	static	IRtcEngine		*m_lpAgoraEngine;
	static	CString			m_strAppID;

	CString					m_strAppCert;
	CString					m_strDynamicChannelKey;
	
	UINT		m_nSelfUID;
	CString		m_strChannelName;
	BOOL		m_bVideoEnable;
	BOOL		m_bAudioEnable;

	BOOL		m_bLocalAudioMuted;
	BOOL		m_bLocalVideoMuted;
	BOOL		m_bAllRemoteAudioMuted;
	BOOL		m_bAllRemoteVideoMuted;
	BOOL		m_bScreenCapture;

	int			m_nWantRoleType;
	int			m_nRoleType;
	int			m_nChannelProfile;

	int			m_nRcdVol;
	int			m_nPlaybackVol;
	int			m_nMixVol;

	BOOL		m_bLoopBack;
	BOOL		m_bFullBand;
	BOOL		m_bStereo;
	BOOL		m_bFullBitrate;

	int			m_nCanvasWidth;
	int			m_nCanvasHeight;

	AGE_PUBLISH_PARAM m_publishParam;

	CAtlMap<UINT, SEI_INFO>	m_mapSEIInfo;
public:
	static CAgoraObject *GetAgoraObject(LPCTSTR lpVendorKey = NULL);
	static void CloseAgoraObject();

	static CAGEngineEventHandler m_EngineEventHandler;
};
