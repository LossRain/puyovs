// Copyright (c) 2024, LossRain
// SPDX-License-Identifier: GPLv3

#pragma once
#include "Animation.h"
#include "DebugLog.h"
#include "GameSettings.h"
#include "RuleSet/RuleSet.h"
#include <iostream>
#include <map>
#include <string>

namespace ppvs {

class GameAssetSettings {
public:
	GameAssetSettings() {};
	GameAssetSettings(GameSettings* gs);
	std::string baseAssetDir;
	std::string language;
	std::string background;
	std::string puyo;
	std::string sfx;
	std::map<PuyoCharacter, std::string> characterSetup;
};

class TokenFnTranslator {
public:
	explicit TokenFnTranslator(GameAssetSettings* aS);
	~TokenFnTranslator();

	void reload();

	std::string token2fn(const std::string& token);
	std::string token2fn(const std::string& token, PuyoCharacter character);

	DebugLog* m_debug = nullptr;

private:
	/*const std::string baseSpecifier = "%base%";
	const std::string language = "%lang";
	const std::string background = "%background%";
	const std::string puyo = "%puyo%";
	const std::string sfx = "%sfx%";
	const std::string characterSetup = "%charfolder%";

	const std::string userSounds = "%usersounds%";
*/
	GameAssetSettings* gameSettings;
	std::map<const char*, std::string> specialTokens;
	std::map<std::string, std::string> sndTokenToPseudoFn = {
		{ "chain1", "%base%/%usersounds%/%sfx%/chain1.ogg" },
		{ "chain2", "%base%/%usersounds%/%sfx%/chain2.ogg" },
		{ "chain3", "%base%/%usersounds%/%sfx%/chain3.ogg" },
		{ "chain4", "%base%/%usersounds%/%sfx%/chain4.ogg" },
		{ "chain5", "%base%/%usersounds%/%sfx%/chain5.ogg" },
		{ "chain6", "%base%/%usersounds%/%sfx%/chain6.ogg" },
		{ "chain7", "%base%/%usersounds%/%sfx%/chain7.ogg" },
		{ "allClearDrop", "%base%/%usersounds%/%sfx%/allclear.ogg" },
		{ "drop", "%base%/%usersounds%/%sfx%/drop.ogg" },
		{ "fever", "%base%/%usersounds%/%sfx%/fever.ogg" },
		{ "feverLight", "%base%/%usersounds%/%sfx%/feverlight.ogg" },
		{ "feverTimeCount", "%base%/%usersounds%/%sfx%/fevertimecount.ogg" },
		{ "feverTimeEnd", "%base%/%usersounds%/%sfx%/fevertimeend.ogg" },
		{ "go", "%base%/%usersounds%/%sfx%/go.ogg" },
		{ "heavy", "%base%/%usersounds%/%sfx%/heavy.ogg" },
		{ "hit", "%base%/%usersounds%/%sfx%/hit.ogg" },
		{ "lose", "%base%/%usersounds%/%sfx%/lose.ogg" },
		{ "move", "%base%/%usersounds%/%sfx%/move.ogg" },
		{ "nuisanceHitL", "%base%/%usersounds%/%sfx%/nuisance_hitL.ogg" },
		{ "nuisanceHitM", "%base%/%usersounds%/%sfx%/nuisance_hitM.ogg" },
		{ "nuisanceHitS", "%base%/%usersounds%/%sfx%/nuisance_hitS.ogg" },
		{ "nuisanceL", "%base%/%usersounds%/%sfx%/nuisanceL.ogg" },
		{ "nuisanceS", "%base%/%usersounds%/%sfx%/nuisanceS.ogg" },
		{ "ready", "%base%/%usersounds%/%sfx%/ready.ogg" },
		{ "rotate", "%base%/%usersounds%/%sfx%/rotate.ogg" },
		{ "win", "%base%/%usersounds%/%sfx%/win.ogg" },
		{ "decide", "%base%/%usersounds%/%sfx%/decide.ogg" },
		{ "cancel", "%base%/%usersounds%/%sfx%/cancel.ogg" },
		{ "cursor", "%base%/%usersounds%/%sfx%/cursor.ogg" },
		{ "charChain1", "%base%/%charsetup%/%char%/Voice/chain1.wav" },
		{ "charChain2", "%base%/%charsetup%/%char%/Voice/chain2.wav" },
		{ "charChain3", "%base%/%charsetup%/%char%/Voice/chain3.wav" },
		{ "charChain4", "%base%/%charsetup%/%char%/Voice/chain4.wav" },
		{ "charChain5", "%base%/%charsetup%/%char%/Voice/chain5.wav" },
		{ "charChain6", "%base%/%charsetup%/%char%/Voice/chain6.wav" },
		{ "charChain7", "%base%/%charsetup%/%char%/Voice/chain7.wav" },
		{ "charSpell1", "%base%/%charsetup%/%char%/Voice/spell1.wav" },
		{ "charSpell2", "%base%/%charsetup%/%char%/Voice/spell2.wav" },
		{ "charSpell3", "%base%/%charsetup%/%char%/Voice/spell3.wav" },
		{ "charSpell4", "%base%/%charsetup%/%char%/Voice/spell4.wav" },
		{ "charSpell5", "%base%/%charsetup%/%char%/Voice/spell5.wav" },
		{ "charCounter", "%base%/%charsetup%/%char%/Voice/counter.wav" },
		{ "charCounterSpell", "%base%/%charsetup%/%char%/Voice/counterspell.wav" },
		{ "charDamage1", "%base%/%charsetup%/%char%/Voice/damage1.wav" },
		{ "charDamage2", "%base%/%charsetup%/%char%/Voice/damage2.wav" },
		{ "charChoose", "%base%/%charsetup%/%char%/Voice/choose.wav" },
		{ "charFeverSuccess", "%base%/%charsetup%/%char%/Voice/feversuccess.wav" },
		{ "charFeverFail", "%base%/%charsetup%/%char%/Voice/feverfail.wav" },
		{ "charFever", "%base%/%charsetup%/%char%/Voice/fever.wav" },
		{ "charLose", "%base%/%charsetup%/%char%/Voice/lose.wav" },
		{ "charWin", "%base%/%charsetup%/%char%/Voice/win.wav" },
	};

	std::map<std::string, std::string> imgTokenToPseudoFn = {
		{ "puyo", "%base%/%puyo%.png" },
		{ "imgLight", "%base%/Data/Light.png" },
		{ "imgLightS", "%base%/Data/Light_s.png" },
		{ "imgLightHit", "%base%/Data/Light_hit.png" },
		{ "imgFSparkle", "%base%/Data/CharSelect/fsparkle.png" },
		{ "imgFLight", "%base%/Data/fLight.png" },
		{ "imgFLightHit", "%base%/Data/fLight_hit.png" },
		{ "imgTime", "%base%/%background%/time.png" },
		{ "imgBackground", "%base%/%background%/back.png" },
		{ "imgFieldFever", "%base%/%background%/ffield.png" },
		{ "imgNextPuyoBackgroundR", "%base%/%background%/nextR.png" },
		{ "imgNextPuyoBackgroundL", "%base%/%background%/nextL.png" },
		{ "imgField1", "%base%/%background%/field1.png" },
		{ "imgField2", "%base%/%background%/field2.png" },
		{ "imgBorder1", "%base%/%background%/border1.png" },
		{ "imgBorder2", "%base%/%background%/border2.png" },
		{ "imgPlayerBorder", "%base%/Data/border.png" },
		{ "imgSpice", "%base%/Data/spice.png" },
		{ "imgScore", "%base%/%background%/score.png" },
		{ "imgAllClear", "%base%/%background%/allclear.png" },
		{ "imgLose", "%base%/%background%/lose.png" },
		{ "imgWin", "%base%/%background%/win.png" },
		{ "imgFeverGauge", "%base%/%background%/fgauge.png" },
		{ "imgSeconds", "%base%/%background%/fcounter.png" },
		{ "imgCharHolder", "%base%/Data/CharSelect/charHolder.png" },
		{ "imgNameHolder", "%base%/Data/CharSelect/nameHolder.png" },
		{ "imgBlack", "%base%/Data/CharSelect/black.png" },
		{ "imgDropSet", "%base%/Data/CharSelect/dropset.png" },
		{ "imgChain", "%base%/%background%/chain.png" },
		{ "imgCheckMark", "%base%/Data/checkmark.png" },
		{ "imgPlayerCharSelect", "%base%/Data/CharSelect/charSelect.png" },
		{ "imgPlayerNumber", "%base%/Data/CharSelect/playernumber.png" },
		{ "imgCharField", "%base%/%charsetup%/%char%/field.png" },
		{ "imgCharSelect", "%base%/%charsetup%/%char%/select.png" },
		{ "imgCharName", "%base%/%charsetup%/%char%/name.png" },
		{ "imgCharSelect", "%base%/%charsetup%/%char%/select.png" },
		{ "imgCharIcon", "%base%/%charsetup%/%char%/icon.png" }

	};
};

class AssetBundle {
public:
	AssetBundle() = default;
	explicit AssetBundle(Frontend* fe)
		: m_frontend(fe) {};
	~AssetBundle() = default;

	virtual int init(Frontend* fe) { return 1; };

	virtual FeImage* loadImage(std::string token) = 0;
	virtual FeSound* loadSound(std::string token) = 0;
	virtual int loadAnimations(Animation* target, std::string token) = 0;

	virtual FeImage* loadCharImage(std::string token, PuyoCharacter character) = 0;
	virtual FeSound* loadCharSound(std::string token, PuyoCharacter character) = 0;
	virtual std::string getCharAnimationsFolder(std::string token, PuyoCharacter character) = 0;

	virtual std::list<std::string> listPuyoSkins() = 0;
	virtual std::list<std::string> listBackgrounds() = 0;
	virtual std::list<std::string> listSfx() = 0;
	virtual std::list<std::string> listCharacterSkins() = 0;

	virtual void reload() = 0;
	virtual void reload(Frontend* fe) = 0;

	bool active = false;
	DebugLog* m_debug = nullptr;

protected:
	Frontend* m_frontend = nullptr;
};

class FolderAssetBundle : public AssetBundle {
public:
	FolderAssetBundle(Frontend* fe, GameAssetSettings* folderLocations);
	~FolderAssetBundle() = default;

	int init(Frontend* fe);

	FeImage* loadImage(std::string token) override;
	FeSound* loadSound(std::string token) override;

	// TODO: All of them
	int loadAnimations(Animation* target, std::string token) override;

	FeImage* loadCharImage(std::string token, PuyoCharacter character) override;
	FeSound* loadCharSound(std::string token, PuyoCharacter character) override;
	std::string getCharAnimationsFolder(std::string token, PuyoCharacter character);

	std::list<std::string> listPuyoSkins();
	std::list<std::string> listBackgrounds();
	std::list<std::string> listSfx();
	std::list<std::string> listCharacterSkins();

	void reload() override;
	void reload(Frontend* fe) override;

private:
	TokenFnTranslator* m_translator;
};

} // ppvs