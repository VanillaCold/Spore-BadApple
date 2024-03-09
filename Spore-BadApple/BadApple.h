#pragma once

#include <Spore\BasicIncludes.h>

#define BadApplePtr intrusive_ptr<BadApple>

class BadApple
	: public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("BadApple");
	static const uint32_t mNumFrames = 0x1999;

	static uint32_t fileCount;
	uint32_t count;

	BadApple();
	~BadApple();

	int AddRef() override;
	int Release() override;
	//void* Cast(uint32_t type) const override;
	//void Update() override;
	void Update() override;

	static int8_t GetPixel(int x, int y);
	static bool SetImage(uint32_t index);
	static cImageDataRawPtr currentImage;

	static vector<vector<IVisualEffectPtr>> images;
	static IVisualEffectPtr musicEffect;
	static bool mbIsStarted;
	static void StartVideo();
	//ImagePtr currentImage;
};
