#include "stdafx.h"
#include "BadAppleCheat.h"
#include "BadApple.h";

BadAppleCheat::BadAppleCheat()
{
}


BadAppleCheat::~BadAppleCheat()
{
}


void BadAppleCheat::ParseLine(const ArgScript::Line& line)
{
	if (auto op = line.GetOption("pixel", 2))
	{
		auto pix = BadApple::GetPixel(mpFormatParser->ParseInt(op[0]), mpFormatParser->ParseInt(op[1]));
		ModAPI::Log("%x", pix);
	}
	else if (auto op = line.GetOption("setImage", 1))
	{
		BadApple::SetImage(mpFormatParser->ParseInt(op[0]));
	}
	else if (line.HasFlag("start"))
	{
		BadApple::StartVideo();
	}
}

const char* BadAppleCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "BadAppleCheat: Elaborate description of what this cheat does.";
	}
}
