#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame_2/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestReactionGame
{		
	TEST_CLASS(Player_test)
	{
	public:
		
		TEST_METHOD(Test_construction) 
		{
			Player p{ "Soukup", 0 };
			Assert::AreEqual("Soukup", p.get_name().c_str(), "Names are different");
		} //wird Eingabe so eingelesen/ausgegeben wie gedacht?
	};
}