#include "gtest\gtest.h"


#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <regex>

bool hasTlsSupportReg(const std::string &ip)
{
  std::smatch m_res;
  std::regex tls("(\\w)(\\w)\\2(?!\\2)\\1(?!\\[(\\w)(\\w)\\1\\2).*");
  if (std::regex_search(ip, m_res, tls)) {
    return true;
  }
  return false;
}

bool hasTlsSupport(const std::string& ip)
{
//  size_t headerLen = ip.find("[");
  // Should be +2
  bool hypernet = false;
  bool candidate = false;

  for (unsigned int i = 1; i < ip.length() - 2; i++)
  {
    if (ip[i] == '[') {
      hypernet = true;
      continue;
    }
    if (ip[i] == ']') {
      hypernet = false;
      continue;
    }
    if (ip[i] == ip[i + 1]) {
      if (ip[i - 1] == ip[i + 2] && ip[i] != ip[i - 1]) {
        if (hypernet)
          return false;
        else
          candidate = true;
      }
    }
  }
  return candidate;
}

bool hasSslSupport(const std::string& str) {

  std::vector<std::string> abaList;
  std::vector<std::string> babList;
  bool hypernet = false;

  for (unsigned int i = 0; i < str.size()-2; i++) {
    if (str[i] == '[')
    {
      hypernet = true;
      continue;
    }
    if (str[i] == ']')
    {
      hypernet = false;
      continue;
    }

    if (str[i] == str[i + 2] && str[i] != str[i + 1] && str[i+1] != '[' && str[i+1] != ']')
    {
      if (hypernet)
        babList.push_back(str.substr(i, 3));
      else
        abaList.push_back(str.substr(i, 3));
    }
  }

  for (auto &aba : abaList)
  {
    aba[0] = aba[1];
    aba[1] = aba[2];
    aba[2] = aba[0];
    if (std::find(babList.begin(), babList.end(), aba) != babList.end()) {
      return true;
    }
  }
  return false;
}

TEST(AdventOfCode7, ABBA)
{
  ASSERT_TRUE(hasTlsSupport("ABBA"));
}

TEST(AdventOfCode7, xABBAx)
{
  ASSERT_TRUE(hasTlsSupport("xABBAx"));
}

TEST(AdventOfCode7, AAAA)
{
  ASSERT_FALSE(hasTlsSupport("AAAA"));
}

TEST(AdventOfCode7, ABBC)
{
  ASSERT_FALSE(hasTlsSupport("ABBC"));
}

TEST(AdventOfCode7, ABBA_Hyper_ABxBA)
{
  ASSERT_TRUE(hasTlsSupport("ABBA[ABxBA]"));
  ASSERT_TRUE(hasTlsSupportReg("ABBA[ABxBA]"));
}

TEST(AdventOfCode7, ABBA_Hyper_ABBA)
{
  ASSERT_FALSE(hasTlsSupport("ABBA[ABBA]"));
  ASSERT_FALSE(hasTlsSupportReg("ABBA[ABBA]"));
}

TEST(AdventOfCode7, ABBAx_Hyper_xABBA)
{
  ASSERT_FALSE(hasTlsSupport("ABBAx[xABBA]"));
  ASSERT_FALSE(hasTlsSupportReg("ABBAx[ABBA]"));
}

TEST(AdventOfCode7, xABBAx_Hyper_ABxBA)
{
  ASSERT_TRUE(hasTlsSupport("xABBAx[ABxBA]"));
//  ASSERT_FALSE(hasTlsSupportReg("xABBAx[ABxBA]"));
}

TEST(AdventOfCode7, Quest1)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input7_1.txt");
  std::string str;
  int count = 0;

  while (std::getline(file, str))
  {
    if (hasTlsSupport(str))
    {
      count++;
    }
  }

  std::cout << "Nr: " << count<< std::endl;
  ASSERT_EQ(115, count);
}

TEST(DISABLED_AdventOfCode7, Quest1Reg)
{
  std::ifstream file("C:\\programming\\advent2016\\input\\input7_1.txt");
  std::string str;
  int count = 0;

  while (std::getline(file, str))
  {
    if (hasTlsSupportReg(str))
    {
      count++;
    }
  }

  std::cout << "Nr: " << count << std::endl;
}

TEST(AdventOfCode7, Quest2) {
  std::ifstream file("C:\\programming\\advent2016\\input\\input7_1.txt");
  std::string str;
  int count = 0;


  while (std::getline(file, str))
  {
    if (hasSslSupport(str))
    {
      count++;
    }

  }
  std::cout << "Nr: " << count << std::endl;
  ASSERT_EQ(231, count);
}

