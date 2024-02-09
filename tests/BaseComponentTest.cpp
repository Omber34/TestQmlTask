//
// Created by Herman on 5/27/2021.
//

#include <gtest/gtest.h>
#include "../src/Components/SnippetComponent.h"
#include "../src/Components/ChapterComponent.h"
#include "../src/Components/PageComponent.h"
#include "../src/Components/BookComponent.h"


//TEST(BaseComponentTests, SnippetComponentTest) {
//    std::unordered_set<Tag> tags {};
//    tags.emplace(Tag("firstTag"));
//    tags.emplace(Tag("secondTag"));
//    std::string name = "testSnippet";
//    std::string description = "just test snippet";
//    SnippetComponent snippetComponent(tags, name, description);
//
//    EXPECT_EQ(snippetComponent.getName(), name);
//    EXPECT_EQ(snippetComponent.getDescription(), description);
//    EXPECT_EQ(snippetComponent.getTags(), tags);
//}
//
//TEST(BaseComponentTests, ChapterComponentTest) {
//    std::unordered_set<Tag> tags {};
//    tags.emplace(Tag("firstTag"));
//    tags.emplace(Tag("secondTag"));
//    std::string name = "testChapter";
//    std::string description = "just test chapter";
//    ChapterComponent snippetComponent(tags, name, description);
//
//    EXPECT_EQ(snippetComponent.getName(), name);
//    EXPECT_EQ(snippetComponent.getDescription(), description);
//    EXPECT_EQ(snippetComponent.getTags(), tags);
//}
//
//TEST(BaseComponentTests, PageComponentTest) {
//    std::unordered_set<Tag> tags {};
//    tags.emplace(Tag("firstTag"));
//    tags.emplace(Tag("secondTag"));
//    std::string name = "testPage";
//    std::string description = "just test Page";
//    PageComponent snippetComponent(tags, name, description);
//
//    EXPECT_EQ(snippetComponent.getName(), name);
//    EXPECT_EQ(snippetComponent.getDescription(), description);
//    EXPECT_EQ(snippetComponent.getTags(), tags);
//}
//
//TEST(BaseComponentTests, BookComponentTest) {
//    std::unordered_set<Tag> tags {};
//    tags.emplace(Tag("firstTag"));
//    tags.emplace(Tag("secondTag"));
//    std::string name = "testBook";
//    std::string description = "just test book";
//    BookComponent snippetComponent(tags, name, description);
//
//    EXPECT_EQ(snippetComponent.getName(), name);
//    EXPECT_EQ(snippetComponent.getDescription(), description);
//    EXPECT_EQ(snippetComponent.getTags(), tags);
//}
