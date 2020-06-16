#include "pch.h"
#include "../SimpleIni.h"

TEST(TestBugFix, TestEmptySection) {
	CSimpleIniA ini;
	ini.SetValue("foo", "skey", "sval");
	ini.SetValue("", "rkey", "rval");
	ini.SetValue("bar", "skey", "sval");

	std::string output;
	ini.Save(output);

	std::string expected =
		"rkey = rval\n"
		"\n"
		"\n"
		"[foo]\n"
		"skey = sval\n"
		"\n"
		"\n"
		"[bar]\n"
		"skey = sval\n";

	output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
	ASSERT_STREQ(expected.c_str(), output.c_str());
}
