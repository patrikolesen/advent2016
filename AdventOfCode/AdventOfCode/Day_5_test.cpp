#include "gtest\gtest.h"


#include <iostream>
#include "md5.h"

using std::cout; using std::endl;
#if 0
TEST(AdventOfCode5, init)
{
  std::string input = "reyedfim";
  std::string passwd = "";
  int count = 0;
  for (int i = 0; 1; i++)
  {
    if (i % 1000000 == 0)
    {
      std::cout << "  Trying " << i << std::endl;
    }
    std::stringstream sstream;
    sstream << input;
    sstream << i;
    std::string myhash = md5(sstream.str());
    if (std::string("00000") == myhash.substr(0, 5))
    {
      cout << sstream.str() << ":" << myhash << endl;
      count++;
      passwd += myhash[5];
      cout << " passwd :" << passwd << endl;
      if (count == 8)
        break;
    }
  }
 }
#endif

#if 0
TEST(AdventOfCode5, 2)
{
  std::string input = "reyedfim";
  char passwd[] = "________";
  int count = 0;

  for (int i = 0; 1; i++)
  {
    if (i % 1000000 == 0)
    {
      std::cout << "  Trying " << i << std::endl;
    }
    std::stringstream sstream;
    sstream << input;
    sstream << i;
    std::string myhash = md5(sstream.str());
    if (std::string("00000") == myhash.substr(0, 5))
    {
      cout << sstream.str() << ":" << myhash << endl;
      int pos = myhash[5] - '0';
      if (pos >= 0 && pos <= 7 && passwd[pos] == '_') {
        count++;
        passwd[pos] = myhash[6];
      }
      cout << " passwd :" << passwd << endl;
      bool done = true;
      for (int j = 0; j < 8; j++)
      {
        if (passwd[j] == '_')
          done = false;
      }
      if (done)
        break;
    }
  }
 }
#endif

#if 0
reyedfim797564:00000fc2d5e1c74f4f562dc6c5a70fb4
  passwd : f
  reyedfim938629 : 000009eda651e255e4a5c90e441dcab0
  passwd : f9
  Trying 1000000
  reyedfim1617991 : 00000774278f87486dd763de7c36d7ac
  passwd : f97
  Trying 2000000
  reyedfim2104453 : 00000c569a8c3f3ba99c95be012958d1
  passwd : f97c
  reyedfim2564359 : 000003dbf0ad65c48ec74313dde4ea8d
  passwd : f97c3
  reyedfim2834991 : 000005e7d422c718d47e47dfff429cbb
  passwd : f97c35
  Trying 3000000
  reyedfim3605750 : 000004d93de3e18869925a23989f0753
  passwd : f97c354
  Trying 4000000
  Trying 5000000
  Trying 6000000
  Trying 7000000
  reyedfim7183955 : 00000d3ea22d988f35663c26220b0982
  passwd : f97c354d
#endif