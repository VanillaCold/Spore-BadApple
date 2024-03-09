#include "stdafx.h"
#include "BadApple.h"


BadApple::BadApple()
{
	images = vector<vector<IVisualEffectPtr>>(); //Emulation of a 2D array via vector inception.
	fileCount = 0x1; //set initial frame
	currentImage = nullptr; //initialize blank variables
	count = 0;

	App::AddUpdateFunction(this); //Add the update function.
	
	ResourceKey key = ResourceKey(fileCount, 0x03E421EC, id("BadApple")); //get the resource key for the first frame
	
	ModAPI::Log("trying to load!"); // Debug message.

	SetImage(0x1);
}


BadApple::~BadApple()
{
}

// For internal use, do not modify.
int BadApple::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int BadApple::Release()
{
	return DefaultRefCounted::Release();
}

void BadApple::Update()
{
	if (mbIsStarted)
	{
			SetImage(fileCount);
			fileCount += 1;
	}
}

int8_t BadApple::GetPixel(int x, int y)
{
	int8_t* imageData;
	int w = 0, h = 0;
	currentImage->GetData(w, h, imageData);
	
	auto test = imageData[x + (w * y)];
	return test;
	
}

bool BadApple::SetImage(uint32_t index)
{
	//TODO: Fix a memory leak here.
	ResourceKey key = ResourceKey(index, 0x03E421EC, id("BadApple"));
	
	ResourceObjectPtr image;
	if (ResourceManager.GetResource(key, &image))
	{
		cImageDataRawPtr rawImage = (Graphics::cImageDataRaw*)image.get();
		currentImage = rawImage;
		
		fileCount = index;
		if (mbIsStarted)
		{
			for (int i = 0; i < 360/2; i++)
			{
				for (int j = 0; j < 270/2; j++)
				{
					uint8_t pixel = GetPixel((360/2)-(i), (j));
					float test = Math::min_(float(pixel / float(0xFF)),1.0f);
					images[i][j]->SetFloatParams(Swarm::FloatParams::kParamTransparency, &test, 1);
				}
			}
		}

		return true;
		
	}
	return false;
}

void BadApple::StartVideo()
{
	images = vector<vector<IVisualEffectPtr>>();
	fileCount = 1;
	mbIsStarted = true;
	Vector3 offset = Vector3(0, 0, 0) / 2;
	
	int scale = 1;

	if (Simulator::IsScenarioMode())
	{
		offset = (GameNounManager.GetAvatar()->mPosition / 2 - Vector3(0,0,1)) + Vector3(360 / 8, 270 / 8, 0);;
	}
	else
	{
		offset = Vector3(360 / 8, 270 / 8,0);
	}
	for (int i = 0; i < 360/2; i++)
	{
		images.push_back(vector<IVisualEffectPtr>());
		for (int j = 0; j < 270/2; j++)
		{
			Vector3 thisOffset = offset + Vector3(-(i), -(j), 0) / 2;
			IVisualEffectPtr effect;
			EffectsManager.CreateVisualEffect(id("BAScreen"), 0, effect);
			effect->SetRigidTransform(effect->GetRigidTransform().SetOffset(thisOffset));
			effect->SetSourceTransform(effect->GetSourceTransform().SetOffset(thisOffset));
			images[i].push_back(effect);
			effect->Start();
		}
	}
	EffectsManager.CreateVisualEffect(id("BAMusic"), 0, musicEffect);
	musicEffect->SetRigidTransform(musicEffect->GetRigidTransform().SetOffset(offset));
	musicEffect->SetSourceTransform(musicEffect->GetSourceTransform().SetOffset(offset));
	musicEffect->Start();

}

vector<vector<IVisualEffectPtr>> BadApple::images;
IVisualEffectPtr BadApple::musicEffect;
cImageDataRawPtr BadApple::currentImage;
bool BadApple::mbIsStarted;
uint32_t BadApple::fileCount;