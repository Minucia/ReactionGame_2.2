#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ReactionGame_2/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestReactionGame
{		
	TEST_CLASS(Player_test)
	{
	public:

		TEST_METHOD(Test_default_construction)
		{
			Player p;
			Assert::AreEqual("MusterMaxi", p.get_name().c_str(), "Default name is different");
			Assert::AreEqual(0, p.get_score());
		}

		TEST_METHOD(Test_construction) 
		{
			Player p{ "Soukup", 0 };
			Assert::AreEqual("Soukup", p.get_name().c_str(), "Names are different");
			Assert::AreEqual(0, p.get_score());
		}

		TEST_METHOD(Test_name)
		{
			Player p;
			p.set_name("Susi");
			Assert::AreEqual("Susi", p.get_name().c_str(), "Names are different");
		}

		TEST_METHOD(Test_increase_score)
		{
			Player p{ "Soukup", 0 };
			p.increase_score();
			Assert::AreEqual(1, p.get_score());
			p.increase_score();
			Assert::AreEqual(2, p.get_score());
		}

		TEST_METHOD(Test_reset_score)
		{
			Player p{ "Susi", 4 };
			Assert::AreEqual(4, p.get_score());
			p.reset_score();
			Assert::AreEqual(0, p.get_score());
			p.increase_score();
			Assert::AreEqual(1, p.get_score());
			p.reset_score();
			Assert::AreEqual(0, p.get_score());
			p.reset_score();
			Assert::AreEqual(0, p.get_score());
		}
	};
}