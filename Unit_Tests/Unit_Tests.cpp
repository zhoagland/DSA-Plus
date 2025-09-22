#include <gtest/gtest.h>

#include "../src/include/linked_list.h"

// Helper data for tests
int test_data = 42;

void map_func(void *data) {
    int val = *(int*)data;
    printf("%d",val);
}

TEST(Linked_List, Init) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    ASSERT_NE(handle, nullptr);
    linked_list_delete(&handle);
}

TEST(Linked_List, Delete) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    ASSERT_EQ(linked_list_delete(&handle), 0);
}

TEST(Linked_List, Mapped_Action_On_Delete) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    ASSERT_EQ(linked_list_mapped_action_on_delete(&handle, &map_func), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Insert_Front) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    ASSERT_EQ(linked_list_insert_front(handle, &test_data), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Insert_Back) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    ASSERT_EQ(linked_list_insert_back(handle, &test_data), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Insert_At) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    ASSERT_EQ(linked_list_insert_at(handle, 0, &test_data), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Insert_Sorted) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    auto cmp = [](void* a, void* b) { return *(int*)a - *(int*)b; };
    ASSERT_EQ(linked_list_insert_sorted(handle, &test_data, cmp), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Remove_Front) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_front(handle, &test_data);
    ASSERT_EQ(linked_list_remove_front(handle), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Remove_Back) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_remove_back(handle), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Remove_Node) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_remove_node(handle), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Remove_At) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_remove_at(handle), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Get_Back) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_get_back(handle), &test_data);
    linked_list_delete(&handle);
}

TEST(Linked_List, Get_At) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_get_at(handle, 0), &test_data);
    linked_list_delete(&handle);
}

TEST(Linked_List, Get_Front) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_front(handle, &test_data);
    ASSERT_EQ(get_front(handle), &test_data);
    linked_list_delete(&handle);
}

TEST(Linked_List, Search) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_search(handle, &test_data), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Is_Empty) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    ASSERT_TRUE(linked_list_is_empty(handle));
    linked_list_insert_back(handle, &test_data);
    ASSERT_FALSE(linked_list_is_empty(handle));
    linked_list_delete(&handle);
}

TEST(Linked_List, Get_List_Size) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    ASSERT_EQ(linked_list_get_list_size(handle), 0);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_get_list_size(handle), 1);
    linked_list_delete(&handle);
}

TEST(Linked_List, Iter_Previous) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_iter_previous(handle, &test_data), nullptr); // depends on implementation
    linked_list_delete(&handle);
}

TEST(Linked_List, Iter_Next) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_insert_back(handle, &test_data);
    ASSERT_EQ(linked_list_iter_next(handle, &test_data), nullptr); // depends on implementation
    linked_list_delete(&handle);
}

TEST(Linked_List, Map_Data) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_insert_back(handle, &test_data);
    auto fnc = [](void *data) { printf("Mapping Data\n"); };
    ASSERT_EQ(linked_list_map_data(handle, fnc), 0);
    linked_list_delete(&handle);
}

TEST(Linked_List, Print) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_insert_back(handle, &test_data);
    auto printer = [](void *data) {};
    linked_list_print(handle, printer);
    linked_list_delete(&handle);
}

#ifdef _DSA_ERROR_H_
TEST(Linked_List, Get_Error_Code) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_get_error_code(handle);
    linked_list_delete(&handle);
}

TEST(Linked_List, Get_Error_Message) {
    LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
    linked_list_get_error_message(handle);
    linked_list_delete(&handle);
}
#endif