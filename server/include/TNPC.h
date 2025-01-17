#ifndef TNPC_H
#define TNPC_H

#include <time.h>
#include "CString.h"
#include "IUtil.h"

#ifdef V8NPCSERVER
#include <unordered_map>
#include <unordered_set>
#include "ScriptBindings.h"
#include "ScriptExecutionContext.h"
#endif

enum
{
	NPCPROP_IMAGE			= 0,
	NPCPROP_SCRIPT			= 1,
	NPCPROP_X				= 2,
	NPCPROP_Y				= 3,
	NPCPROP_POWER			= 4,
	NPCPROP_RUPEES			= 5,
	NPCPROP_ARROWS			= 6,
	NPCPROP_BOMBS			= 7,
	NPCPROP_GLOVEPOWER		= 8,
	NPCPROP_BOMBPOWER		= 9,
	NPCPROP_SWORDIMAGE		= 10,
	NPCPROP_SHIELDIMAGE		= 11,
	NPCPROP_GANI			= 12,	// NPCPROP_BOWGIF in pre-2.x
	NPCPROP_VISFLAGS		= 13,
	NPCPROP_BLOCKFLAGS		= 14,
	NPCPROP_MESSAGE			= 15,
	NPCPROP_HURTDXDY		= 16,
	NPCPROP_ID				= 17,
	NPCPROP_SPRITE			= 18,
	NPCPROP_COLORS			= 19,
	NPCPROP_NICKNAME		= 20,
	NPCPROP_HORSEIMAGE		= 21,
	NPCPROP_HEADIMAGE		= 22,
	NPCPROP_SAVE0			= 23,
	NPCPROP_SAVE1			= 24,
	NPCPROP_SAVE2			= 25,
	NPCPROP_SAVE3			= 26,
	NPCPROP_SAVE4			= 27,
	NPCPROP_SAVE5			= 28,
	NPCPROP_SAVE6			= 29,
	NPCPROP_SAVE7			= 30,
	NPCPROP_SAVE8			= 31,
	NPCPROP_SAVE9			= 32,
	NPCPROP_ALIGNMENT		= 33,
	NPCPROP_IMAGEPART		= 34,
	NPCPROP_BODYIMAGE		= 35,
	NPCPROP_GATTRIB1		= 36,
	NPCPROP_GATTRIB2		= 37,
	NPCPROP_GATTRIB3		= 38,
	NPCPROP_GATTRIB4		= 39,
	NPCPROP_GATTRIB5		= 40,
	NPCPROP_GMAPLEVELX		= 41,
	NPCPROP_GMAPLEVELY		= 42,

	NPCPROP_UNKNOWN43		= 43,

	NPCPROP_GATTRIB6		= 44,
	NPCPROP_GATTRIB7		= 45,
	NPCPROP_GATTRIB8		= 46,
	NPCPROP_GATTRIB9		= 47,

	NPCPROP_UNKNOWN48		= 48,
	NPCPROP_SCRIPTER		= 49, // My guess is UNKNOWN48 or this is the scripter's name
	NPCPROP_NAME			= 50,
	NPCPROP_TYPE			= 51,
	NPCPROP_CURLEVEL		= 52,

	NPCPROP_GATTRIB10		= 53,
	NPCPROP_GATTRIB11		= 54,
	NPCPROP_GATTRIB12		= 55,
	NPCPROP_GATTRIB13		= 56,
	NPCPROP_GATTRIB14		= 57,
	NPCPROP_GATTRIB15		= 58,
	NPCPROP_GATTRIB16		= 59,
	NPCPROP_GATTRIB17		= 60,
	NPCPROP_GATTRIB18		= 61,
	NPCPROP_GATTRIB19		= 62,
	NPCPROP_GATTRIB20		= 63,
	NPCPROP_GATTRIB21		= 64,
	NPCPROP_GATTRIB22		= 65,
	NPCPROP_GATTRIB23		= 66,
	NPCPROP_GATTRIB24		= 67,
	NPCPROP_GATTRIB25		= 68,
	NPCPROP_GATTRIB26		= 69,
	NPCPROP_GATTRIB27		= 70,
	NPCPROP_GATTRIB28		= 71,
	NPCPROP_GATTRIB29		= 72,
	NPCPROP_GATTRIB30		= 73,

	NPCPROP_CLASS			= 74,	// NPC-Server class.  Possibly also join scripts.
	NPCPROP_X2				= 75,
	NPCPROP_Y2				= 76,

	NPCPROP_COUNT
};

//! NPCPROP_VISFLAGS values.
enum
{
	NPCVISFLAG_VISIBLE			= 0x01,
	NPCVISFLAG_DRAWOVERPLAYER	= 0x02,
	NPCVISFLAG_DRAWUNDERPLAYER	= 0x04,
};

//! NPCPROP_BLOCKFLAGS values.
enum
{
	NPCBLOCKFLAG_BLOCK		= 0x00,
	NPCBLOCKFLAG_NOBLOCK	= 0x01,
};

//! NPCMOVE_FLAGS values
enum
{
	NPCMOVEFLAG_NOCACHE			= 0x00,
	NPCMOVEFLAG_CACHE			= 0x01,
	NPCMOVEFLAG_APPEND			= 0x02,
	NPCMOVEFLAG_BLOCKCHECK		= 0x04,
	NPCMOVEFLAG_EVENTWHENDONE 	= 0x08,
	NPCMOVEFLAG_APPLYDIR		= 0x10
};

#ifdef V8NPCSERVER
//! NPC Event Flags
enum
{
	NPCEVENTFLAG_CREATED		= (int)(1 << 0),
	NPCEVENTFLAG_TIMEOUT		= (int)(1 << 1),
	NPCEVENTFLAG_PLAYERCHATS	= (int)(1 << 2),
	NPCEVENTFLAG_PLAYERENTERS	= (int)(1 << 3),
	NPCEVENTFLAG_PLAYERLEAVES	= (int)(1 << 4),
	NPCEVENTFLAG_PLAYERTOUCHSME	= (int)(1 << 5),
	NPCEVENTFLAG_PLAYERLOGIN	= (int)(1 << 6),
	NPCEVENTFLAG_PLAYERLOGOUT	= (int)(1 << 7),
	NPCEVENTFLAG_NPCWARPED		= (int)(1 << 8),
};
#endif

class TServer;
class TLevel;
class TPlayer;
class TNPC
{
	public:
		TNPC(TServer* pServer, bool pLevelNPC = false);
		TNPC(const CString& pImage, const CString& pScript, float pX, float pY, TServer* pServer, TLevel* pLevel, bool pLevelNPC = true);
		~TNPC();

		void setScriptCode(const CString& pScript);

		// prop functions
		CString getProp(unsigned char pId, int clientVersion = CLVER_2_17) const;
		CString getProps(time_t newTime, int clientVersion = CLVER_2_17) const;
		CString setProps(CString& pProps, int clientVersion = CLVER_2_17, bool pForward = false);

		// set functions
		void setId(unsigned int pId)			{ id = pId; }
		void setLevel(TLevel* pLevel)			{ level = pLevel; }
		void setX(float val)					{ x = val; x2 = (int)(16 * val); }
		void setY(float val)					{ y = val; y2 = (int)(16 * val); }
		void setHeight(int val)					{ height = val; }
		void setWidth(int val)					{ width = val; }
		void setRupees(int val)					{ rupees = val; }
		void setName(const std::string& name)	{ npcName = name; }
		void setNickname(const CString& nick)	{ nickName = nick; }
		void setScripter(const CString& name)	{ npcScripter = name; }
		void setType(const CString& type)		{ npcType = type; }
		void setBlockingFlags(int val)			{ blockFlags = val; }
		void setVisibleFlags(int val)			{ visFlags = val; }
		void setColorId(unsigned int idx, unsigned char val);
		void setSave(unsigned int idx, unsigned char val);
		void setPropModTime(unsigned char pid, time_t time);

		// get functions
		unsigned int getId() const				{ return id; }
		bool isLevelNPC() const					{ return levelNPC; }
		float getX() const						{ return x; }
		float getY() const						{ return y; }
		int getPixelX() const					{ return x2; }
		int getPixelY() const					{ return y2; }
		int getHeight() const 					{ return height; }
		int getWidth() const 					{ return width; }
		int getRupees() const 					{ return rupees; }
		int getBlockFlags() const 				{ return blockFlags; }
		int getVisibleFlags() const 			{ return visFlags; }
		int getTimeout() const 					{ return timeout; }

		const CString& getBodyImage() const		{ return bodyImage; }
		const CString& getHeadImage() const		{ return headImage; }
		const CString& getHorseImage() const	{ return horseImage; }
		const CString& getShieldImage() const	{ return shieldImage; }
		const CString& getSwordImage() const	{ return swordImage; }
		const CString& getImage() const			{ return image; }
		const CString& getNickname() const 		{ return nickName; }
		const std::string& getName() const		{ return npcName; }
		const CString& getType() const			{ return npcType; }
		const CString& getClientScript() const	{ return clientScript; }
		const CString& getServerScript() const	{ return serverScript; }
		const CString& getScriptCode() const	{ return originalScript; }
		const CString& getScripter() const		{ return npcScripter; }
		const CString& getWeaponName() const	{ return weaponName; }
		TLevel * getLevel() const				{ return level; }
		time_t getPropModTime(unsigned char pId);
		unsigned char getColorId(unsigned int idx) const;
		unsigned char getSave(unsigned int idx) const;

#ifdef V8NPCSERVER
		// TODO(joey): clean this all up, some of this stuff can be taken out of the v8npcserver definition
		void addClassCode(const std::string& className, const std::string& classCode);
		void setTimeout(int val);
		void updatePropModTime(unsigned char propId);

		//
		bool hasScriptEvent(int flag) const;
		void setScriptEvents(int mask);

		ScriptExecutionContext * getExecutionContext();
		IScriptWrapped<TNPC> * getScriptObject() const;
		void setScriptObject(IScriptWrapped<TNPC> *object);

		// -- flags
		CString getFlag(const std::string& pFlagName) const;
		void setFlag(const std::string& pFlagName, const CString& pFlagValue);
		void deleteFlag(const std::string& pFlagName);
		std::unordered_map<std::string, CString>* getFlagList() { return &flagList; }

		bool deleteNPC();
		void reloadNPC();
		void resetNPC();

		bool isWarpable() const { return canWarp; }
		void allowNpcWarping(bool canWarp);
		void moveNPC(int dx, int dy, double time, int options);
		void warpNPC(TLevel *pLevel, float pX, float pY);

		// file
		bool getPersist() const			{ return persistNpc; }
		void setPersist(bool persist)	{ persistNpc = persist; }
		bool loadNPC(const CString& fileName);
		void saveNPC();

		void queueNpcAction(const std::string& action, TPlayer *player = 0, bool registerAction = true);
		void queueNpcTrigger(const std::string& action, const std::string& data);

		template<class... Args>
		void queueNpcEvent(const std::string& action, bool registerAction, Args&&... An);

		void registerNpcUpdates();
		void registerTriggerAction(const std::string& action, IScriptFunction *cbFunc);

		bool runScriptTimer();
		bool runScriptEvents();

		CString getVariableDump();
#endif

	private:
		bool blockPositionUpdates;
		bool levelNPC;
		time_t modTime[NPCPROP_COUNT];
		float x, y, hurtX, hurtY;
		int x2, y2;
		unsigned char gmaplevelx, gmaplevely;
		unsigned int id;
		int rupees;
		unsigned char darts, bombs, glovePower, bombPower, swordPower, shieldPower;
		unsigned char visFlags, blockFlags, sprite, colors[5], power, ap;
		CString gAttribs[30];
		CString image, swordImage, shieldImage, headImage, bodyImage, horseImage, bowImage, gani;
		CString nickName, imagePart, chatMsg, weaponName;
		CString serverScript, clientScript, clientScriptFormatted, originalScript;
		unsigned char saves[10];
		TLevel* level;
		TServer* server;

		CString npcScripter, npcType;
		std::string npcName;
		int timeout;
		int width, height;

#ifdef V8NPCSERVER
		void testTouch();
		void freeScriptResources();

		std::map<std::string, std::string> classMap;
		std::unordered_set<int> propModified;

		// Defaults
		CString origImage, origLevel;
		float origX, origY;

		// npc-server
		bool canWarp;
		bool npcDeleteRequested;
		bool persistNpc;
		std::unordered_map<std::string, CString> flagList;

		int _scriptEventsMask;
		IScriptWrapped<TNPC> *_scriptObject;
		ScriptExecutionContext _scriptExecutionContext;
		std::unordered_map<std::string, IScriptFunction *> _triggerActions;
#endif
};

inline
time_t TNPC::getPropModTime(unsigned char pId)
{
	if (pId < NPCPROP_COUNT) return modTime[pId];
	return 0;
}

inline
void TNPC::setPropModTime(unsigned char pId, time_t time)
{
	if (pId < NPCPROP_COUNT)
		modTime[pId] = time;
}

inline
unsigned char TNPC::getColorId(unsigned int idx) const
{
	if (idx < 5) return colors[idx];
	return 0;
}

inline
void TNPC::setColorId(unsigned int idx, unsigned char val)
{
	if (idx < 5) colors[idx] = val;
}

inline
unsigned char TNPC::getSave(unsigned int idx) const
{
	if (idx < 10) return saves[idx];
	return 0;
}

inline
void TNPC::setSave(unsigned int idx, unsigned char val)
{
	if (idx < 10) saves[idx] = val;
}

#ifdef V8NPCSERVER

inline void TNPC::updatePropModTime(unsigned char propId)
{
	if (propId < NPCPROP_COUNT) {
		propModified.insert(propId);
		registerNpcUpdates();
	}
}

inline void TNPC::allowNpcWarping(bool canWarp)
{
	if (!isLevelNPC())
		this->canWarp = canWarp;
}

/**
 * Script Engine 
 */
inline bool TNPC::hasScriptEvent(int flag) const {
	return ((_scriptEventsMask & flag) == flag);
}

inline void TNPC::setScriptEvents(int mask) {
	_scriptEventsMask = mask;
}

inline ScriptExecutionContext * TNPC::getExecutionContext() {
	return &_scriptExecutionContext;
}

inline IScriptWrapped<TNPC> * TNPC::getScriptObject() const {
	return _scriptObject;
}

inline void TNPC::setScriptObject(IScriptWrapped<TNPC> *object) {
	_scriptObject = object;
}

inline CString TNPC::getFlag(const std::string& pFlagName) const
{
	auto it = flagList.find(pFlagName);
	if (it != flagList.end())
		return it->second;
	return "";
}

inline void TNPC::setFlag(const std::string & pFlagName, const CString & pFlagValue)
{
	flagList[pFlagName] = pFlagValue;
}

inline void TNPC::deleteFlag(const std::string& pFlagName)
{
	flagList.erase(pFlagName);
}

// TODO(joey): hm
#include "TServer.h"

template<class... Args>
inline void TNPC::queueNpcEvent(const std::string& action, bool registerAction, Args&&... An)
{
	CScriptEngine *scriptEngine = server->getScriptEngine();
	ScriptAction *scriptAction = scriptEngine->CreateAction(action, _scriptObject, std::forward<Args>(An)...);

	_scriptExecutionContext.addAction(scriptAction);
	if (registerAction)
		scriptEngine->RegisterNpcUpdate(this);
}

inline void TNPC::registerNpcUpdates()
{
	CScriptEngine *scriptEngine = server->getScriptEngine();
	scriptEngine->RegisterNpcUpdate(this);
}

#endif

#endif
