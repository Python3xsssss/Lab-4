#include "List.h"
#include <gtest.h>
TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<int>(3));
}

TEST(List, can_create_copied_list)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ASSERT_NO_THROW(List<int>(ls));
}

TEST(List, copied_list_is_equal_to_source_one)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	List<int> tmp(ls);
	EXPECT_EQ(ls[1], tmp[1]);
}

TEST(List, can_push_top_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Push_top(3);
	EXPECT_EQ(3, ls[0]);
}

TEST(List, can_push_bot_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Push_bot(3);
	EXPECT_EQ(3, ls[2]);
}

TEST(List, can_pop_top_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Pop_top();
	EXPECT_EQ(2, ls[0]);
}

TEST(List, can_pop_bot_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Pop_bot();
	ASSERT_ANY_THROW(ls[1]);
}

TEST(List, can_insert_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Insert(1, 3);
	EXPECT_EQ(3, ls[1]);
}

TEST(List, can_delete_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	ls.Delete(1);
	ASSERT_ANY_THROW(ls[1]);
}

TEST(List, can_set_and_get_element)
{
	List<int> ls(3);
	ls.Set(0, 1);
	EXPECT_EQ(1, ls.Get(0));
}

TEST(List, can_set_and_get_element_by_operator)
{
	List<int> ls(3);
	ls[0] = 1;
	EXPECT_EQ(1, ls[0]);
}

TEST(List, can_get_top_element)
{
	List<int> ls(2);
	ls[0] = 1;
	ls[1] = 2;
	EXPECT_EQ(1, ls.Top());
}

TEST(List, empty_list_is_empty)
{
	List<int> ls;
	EXPECT_EQ(true, ls.Empty());
}

TEST(List, not_empty_list_is_not_empty)
{
	List<int> ls(2);
	EXPECT_EQ(false, ls.Empty());
}

TEST(List, can_get_size_of_list)
{
	List<int> ls(2);
	EXPECT_EQ(2, ls.GetSize());
}


