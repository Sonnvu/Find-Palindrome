#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test FindPalindrome add a non-allowable word", "[FindPalindrome]" )
{
	INFO("Hint: add a single non-allowable word");
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE( "Test FindPalindrome add a allowable word", "[FindPalindrome]" )
{
	INFO("Hint: add a single allowable word");
	FindPalindrome b;
	REQUIRE(b.add("Odd"));
	std::vector<std::string> test = {"Odd"};
	REQUIRE(b.getCandVector() == test);
}

TEST_CASE("Test FindPalindrome add vector of non-allowable words" , "[FindPalindrome]")
{
	FindPalindrome b; 
	REQUIRE(!b.add({"kayak1", "Hell0", "World"}));
}

TEST_CASE("Test CutTest1 Function", "[FindPalindrome]")
{
	FindPalindrome b; 
	REQUIRE(b.cutTest1({"kayak"}));
	REQUIRE(b.cutTest1({"never", "odd", "or", "even"}));
	REQUIRE(!b.cutTest1({"Palindromesentence"}));
	REQUIRE(!b.cutTest1({"Palindromesentence", "Hello"}));
}

TEST_CASE("Test CutTest2 Function", "[FindPalindrome]")
{
	FindPalindrome b; 
	REQUIRE(b.cutTest2({"kayak"}, {"kayak"}));
	REQUIRE(b.cutTest2({"never", "odd"}, {"even", "or"}));
	REQUIRE(!b.cutTest2({"hello"}, {"no"}));
	REQUIRE(!b.cutTest2({"Even", "never"},{"Hello", "palindrome"}));
}

TEST_CASE("Test Default Constructor And Destructor", "[FindPalindrome]")
{
	FindPalindrome b; 
	REQUIRE(b.number() == 0); 
	REQUIRE(b.toVector().size() == 0);
}

TEST_CASE("Test Number And Clear Methods", "[FindPalindrome]")
{	
	{
		FindPalindrome b; 
		REQUIRE(b.add("Never"));
		REQUIRE(b.add("Even"));
		REQUIRE(b.add("Odd"));
		REQUIRE(b.add("Or"));
		REQUIRE(b.number() == 1); 

		b.clear(); 
		REQUIRE(b.number() == 0); 
	}

	{
		FindPalindrome b; 
		REQUIRE(b.add("Step"));
		REQUIRE(b.add("Pets"));
		REQUIRE(b.add("No"));
		REQUIRE(b.add("On"));
		REQUIRE(b.number() == 8);

		b.clear(); 
		REQUIRE(b.number() == 0); 
	}
}

TEST_CASE("Test toVector Method", "[FindPalindrome]")
{
	{
		FindPalindrome b; 
		REQUIRE(b.add("Never"));
		REQUIRE(b.add("Even"));
		REQUIRE(b.add("Odd"));
		REQUIRE(b.add("Or"));

		std::vector<std::vector<std::string>> test = 
		{{"never","odd", "or", "even"}};
		REQUIRE(b.toVector() == test);
	}

	{
		FindPalindrome b; 
		REQUIRE(b.add("Do"));
		REQUIRE(b.add("God"));
		REQUIRE(b.add("Geese"));
		REQUIRE(b.add("See"));

		std::vector<std::vector<std::string>> test = 
		{{"do","geese", "see", "god"}};
		REQUIRE(b.toVector() == test);
	}

	{
		FindPalindrome b; 
		REQUIRE(b.add("Step"));
		REQUIRE(b.add("Pets"));
		REQUIRE(b.add("No"));
		REQUIRE(b.add("On"));

		std::vector<std::vector<std::string>> test = 
		{{"step","no", "on", "pets"}, {"step", "on", "no","pets"}, {"pets", "no", "on", "step"},
		{"pets", "on", "no", "step"}, {"no", "step", "pets", "on"}, {"no", "pets", "step", "on"}, 
		{"on", "step", "pets", "no"}, {"on", "pets", "step", "no"}};
		REQUIRE(b.toVector() == test);
	}
}

TEST_CASE("N! Test", "[FindPalindrome]")
{
	FindPalindrome b; 
	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA")); 

	REQUIRE(b.number()==6); 

}