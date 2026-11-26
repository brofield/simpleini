#include "../SimpleIni.h"
#include "gtest/gtest.h"

TEST(TestBugFix, TestEmptySection) {
  CSimpleIniA ini;
  ini.SetValue("foo", "skey", "sval");
  ini.SetValue("", "rkey", "rval");
  ini.SetValue("bar", "skey", "sval");

  std::string output;
  ini.Save(output);

  std::string expected = "rkey = rval\n"
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

TEST(TestBugFix, TestMultiLineIgnoreTrailSpace0) {
  std::string input = "; multiline values\n"
                      "key = <<<EOS\n"
                      "This is a\n"
                      "multiline value\n"
                      "and it ends.\n"
                      "EOS\n"
                      "\n"
                      "[section]\n";

  bool multiline = true;
  CSimpleIniA ini(true, false, multiline);

  SI_Error rc = ini.LoadData(input);
  ASSERT_EQ(rc, SI_OK);

  std::string output;
  ini.Save(output);

  std::string expected = "; multiline values\n"
                         "\n"
                         "\n"
                         "key = <<<END_OF_TEXT\n"
                         "This is a\n"
                         "multiline value\n"
                         "and it ends.\n"
                         "END_OF_TEXT\n"
                         "\n"
                         "\n"
                         "[section]\n";

  output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
  ASSERT_STREQ(expected.c_str(), output.c_str());
}

TEST(TestBugFix, TestMultiLineIgnoreTrailSpace1) {
  std::string input = "; multiline values\n"
                      "key = <<<EOS\n"
                      "This is a\n"
                      "multiline value\n"
                      "and it ends.\n"
                      "EOS \n"
                      "\n"
                      "[section]\n";

  bool multiline = true;
  CSimpleIniA ini(true, false, multiline);

  SI_Error rc = ini.LoadData(input);
  ASSERT_EQ(rc, SI_OK);

  std::string output;
  ini.Save(output);

  std::string expected = "; multiline values\n"
                         "\n"
                         "\n"
                         "key = <<<END_OF_TEXT\n"
                         "This is a\n"
                         "multiline value\n"
                         "and it ends.\n"
                         "END_OF_TEXT\n"
                         "\n"
                         "\n"
                         "[section]\n";

  output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
  ASSERT_STREQ(expected.c_str(), output.c_str());
}

TEST(TestBugFix, TestMultiLineIgnoreTrailSpace2) {
  std::string input = "; multiline values\n"
                      "key = <<<EOS\n"
                      "This is a\n"
                      "multiline value\n"
                      "and it ends.\n"
                      "EOS  \n"
                      "\n"
                      "[section]\n";

  bool multiline = true;
  CSimpleIniA ini(true, false, multiline);

  SI_Error rc = ini.LoadData(input);
  ASSERT_EQ(rc, SI_OK);

  std::string output;
  ini.Save(output);

  std::string expected = "; multiline values\n"
                         "\n"
                         "\n"
                         "key = <<<END_OF_TEXT\n"
                         "This is a\n"
                         "multiline value\n"
                         "and it ends.\n"
                         "END_OF_TEXT\n"
                         "\n"
                         "\n"
                         "[section]\n";

  output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
  ASSERT_STREQ(expected.c_str(), output.c_str());
}

TEST(TestBugFix, TestAliasKeyWithEquals) {
  CSimpleIniA ini(true, false, false);
  SI_Error rc = ini.LoadData(std::string{
      "[aliases]\n"
      "alias[=] = \"nag =\"\n"
      "alias[!] = \"nag !\"\n"
      "alias[c] = O-O\n"
      "anythingelse[=] = \"nag =\"\n"
      "custom[foo] = bar\n"
  });
  ASSERT_EQ(rc, SI_OK);

  CSimpleIniA::TNamesDepend sections;
  ini.GetAllSections(sections);
  ASSERT_EQ(sections.size(), 1u);

  CSimpleIniA::TNamesDepend keys;
  ini.GetAllKeys("aliases", keys);
  // Note: alias[=] and anythingelse[=] both define the key "=" (multikey is false, so it updates "=")
  ASSERT_EQ(keys.size(), 4u);

  ASSERT_STREQ(ini.GetValue("aliases", "="), "nag =");
  ASSERT_STREQ(ini.GetValue("aliases", "!"), "nag !");
  ASSERT_STREQ(ini.GetValue("aliases", "c"), "O-O");
  ASSERT_STREQ(ini.GetValue("aliases", "foo"), "bar");
}


