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
			Assert::AreEqual(0, p.get_score());
		} 

		TEST_METHOD(Test_score)
		{
			Player p{ "Soukup",0 };
			p.increase_score();
			Assert::AreEqual(1, p.get_score());
			p.reset_score();
			Assert::AreEqual(0, p.get_score());
		}
	};
}