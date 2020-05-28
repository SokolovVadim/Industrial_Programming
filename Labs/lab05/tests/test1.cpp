#include <print.hpp>

#include <gtest/gtest.h> // gtest

TEST(Print, InFileStream) // test module with function and description
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text); // if(result == text)
}
