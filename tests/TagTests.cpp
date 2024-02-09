//
// Created by Herman on 5/27/2021.
//

#include <gtest/gtest.h>
#include "../src/Elements/Tag/Tag.h"
#include "../src/Elements/Tag/TagPool.h"

struct TagForTest {
    std::shared_ptr<TagImpl> impl;
};

TEST(TagTests, SimpleTagTest) {
    std::string tagName = "hashtag";
    Tag tag(tagName);
    Tag tag2("stringName");
    EXPECT_EQ(tag.getName(), tagName);
    EXPECT_EQ(tag2.getName(), "stringName");
}

TEST(TagTests, TagPoolTest) {
    std::string tagName = "hashtag";
    Tag tag1(tagName);
    Tag tag2(tagName);
    TagForTest* tag1test = reinterpret_cast<TagForTest*>(&tag1);
    TagForTest* tag2test = reinterpret_cast<TagForTest*>(&tag2);

    EXPECT_EQ(tag1test->impl.get(), tag2test->impl.get());
    EXPECT_EQ(TagPool::getInstance().size(), 1);
}