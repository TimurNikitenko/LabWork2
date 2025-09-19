/* Timur Nikitenko st128375@student.spbu.ru
 */

 #include <gtest/gtest.h>
 #include "main.h"
 
 TEST(TrueTest, BasicAssertions) {
     EXPECT_EQ(1, 1); 
     EXPECT_TRUE(true);
 }
 
 int main(int argc, char **argv) {
     testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
 }