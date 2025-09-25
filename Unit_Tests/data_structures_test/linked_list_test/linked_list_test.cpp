#include <gtest/gtest.h>
#include "linked_list.h"
#include "linked_list_internal.h"

namespace Linked_List {

#define SL Singly_Linked
#define DL Doubly_Linked
#define CSL Circular_Singly_Linked
#define CDL Circular_Doubly_Linked


    // Helper data for tests
    int test_data[] = {0, 1, 2, 3, 4};

    void map_func(void *data) {
        int val = *(int *)data;
        printf("%d\n", val);
    }

    TEST(SL, Init) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        auto             list   = ((dsa_linked_list_control_block_t *)handle);

        // Handle shouldn't be null.
        ASSERT_NE(handle, nullptr);

        // List length should be one with an initializer data
        ASSERT_EQ(list->list_length, 1);

        // Data addresses should match
        ASSERT_EQ(list->head->data, &test_data);

        // With only one node head should also be tail
        ASSERT_EQ(list->head, list->tail);

        // Head next node should be null. Only one node.
        ASSERT_EQ(list->head->next_node, nullptr);

        // Previous should be null as singly linked
        ASSERT_EQ(list->head->previous_node, nullptr);

        // Tail should always point to null in singly linked
        ASSERT_EQ(list->tail->next_node, nullptr);

        // No node should point to a previous in a singly linked list.
        ASSERT_EQ(list->tail->previous_node, nullptr);


        LinkedListHandle handle2 = linked_list_initialize(SINGLY_LINKED_LIST, NULL);
        auto             list2   = ((dsa_linked_list_control_block_t *)handle2);

        // Handle again should not be null
        ASSERT_NE(handle2, nullptr);

        // Length should be zero because initialized without a data pointer.
        ASSERT_EQ(list2->list_length, 0);

        // No nodes in the list so head and tail should be null.
        ASSERT_EQ(list2->head, nullptr);
        ASSERT_EQ(list2->tail, nullptr);

        // Again both null so they should equal each other.
        ASSERT_EQ(list2->head, list2->tail);

        // Handles should not be the same.
        ASSERT_NE(handle, handle2);

        linked_list_delete(&handle);
        linked_list_delete(&handle2);
    }


    TEST(DL, Init) {
        LinkedListHandle handle = linked_list_initialize(DOUBLY_LINKED_LIST, &test_data);
        auto             list   = ((dsa_linked_list_control_block_t *)handle);

        // Handle should be assigned
        ASSERT_NE(handle, nullptr);

        // List should be length one
        ASSERT_EQ(list->list_length, 1);

        // Data should point to test data
        ASSERT_EQ(list->head->data, &test_data);

        // Only one node so head and tail should be the same.
        ASSERT_EQ(list->head, list->tail);

        // Only one node head should point to null.
        ASSERT_EQ(list->head->next_node, nullptr);

        // Only one node head previous should always be null.
        ASSERT_EQ(list->head->previous_node, nullptr);

        // Only one node so head is also the tail.
        ASSERT_EQ(list->tail->next_node, nullptr);
        ASSERT_EQ(list->tail->previous_node, nullptr);

        LinkedListHandle handle2 = linked_list_initialize(DOUBLY_LINKED_LIST, NULL);
        auto             list2   = ((dsa_linked_list_control_block_t *)handle2);

        // Handle should be assigned.
        ASSERT_NE(handle2, nullptr);

        // Initialized with no data so length should be 0.
        ASSERT_EQ(list2->list_length, 0);

        // Head and tail should be null thus equal each otherl
        ASSERT_EQ(list2->head, list2->tail);
        ASSERT_EQ(list2->head, nullptr);
        ASSERT_EQ(list2->tail, nullptr);

        // Handles shouldn't equal each other.
        ASSERT_NE(handle, handle2);

        linked_list_delete(&handle);
        linked_list_delete(&handle2);
    }


    TEST(CL, Init) {
        LinkedListHandle handle = linked_list_initialize(CIRCULAR_SINGLY_LINKED_LIST, &test_data);
        auto             list   = ((dsa_linked_list_control_block_t *)handle);

        ASSERT_NE(handle, nullptr);
        ASSERT_EQ(list->list_length, 1);
        ASSERT_EQ(list->head->data, &test_data);
        ASSERT_EQ(list->head, list->tail);
        ASSERT_NE(list->head->next_node, nullptr);
        ASSERT_EQ(list->head->previous_node, list->tail);
        ASSERT_NE(list->tail->previous_node, nullptr);
        ASSERT_EQ(list->tail->next_node, list->head);

        LinkedListHandle handle2 = linked_list_initialize(CIRCULAR_SINGLY_LINKED_LIST, NULL);
        auto             list2   = ((dsa_linked_list_control_block_t *)handle2);

        ASSERT_NE(handle2, nullptr);
        ASSERT_EQ(list2->list_length, 0);
        ASSERT_EQ(list2->head, list2->tail);
        ASSERT_EQ(list2->head, nullptr);
        ASSERT_EQ(list2->tail, nullptr);
        ASSERT_NE(handle, handle2);

        linked_list_delete(&handle);
        linked_list_delete(&handle2);
    }

    TEST(SL, Delete) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        ASSERT_EQ(linked_list_delete(&handle), 0);
        ASSERT_EQ(handle, nullptr);
    }

    TEST(DL, Delete) {
        LinkedListHandle handle = linked_list_initialize(DOUBLY_LINKED_LIST, &test_data);
        ASSERT_EQ(linked_list_delete(&handle), 0);
    }

    TEST(CL, Delete) {
        LinkedListHandle handle = linked_list_initialize(CIRCULAR_SINGLY_LINKED_LIST, &test_data);
        ASSERT_EQ(linked_list_delete(&handle), 0);
    }

    TEST(SL, Mapped_Action_On_Delete) {
        auto mapped_act_on_del = [](void *data) { printf("Data Deleted %d", *(int *)data); };

        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        ASSERT_EQ(linked_list_mapped_action_on_delete(&handle, mapped_act_on_del), 0);
        linked_list_delete(&handle);
    }


    TEST(SL, Insert_Front) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        ASSERT_EQ(linked_list_insert_front(handle, &test_data), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Insert_Back) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        ASSERT_EQ(linked_list_insert_back(handle, &test_data), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Insert_At) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        ASSERT_EQ(linked_list_insert_at(handle, 0, &test_data), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Insert_Sorted) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        auto             cmp    = [](void *a, void *b) { return *(int *)a - *(int *)b; };
        ASSERT_EQ(linked_list_insert_sorted(handle, &test_data, cmp), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Remove_Front) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_front(handle, &test_data);
        ASSERT_EQ(linked_list_remove_front(handle, NULL), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Remove_Back) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_remove_back(handle, NULL), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Remove_Node) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_remove_node(handle, &test_data, NULL), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Remove_At) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_remove_at(handle, 0, NULL), 0);
        ASSERT_EQ(linked_list_get_list_size(handle), 1);
        linked_list_delete(&handle);
    }

    TEST(SL, Get_Back) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_get_back(handle), &test_data);
        linked_list_delete(&handle);
    }

    TEST(SL, Get_At) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_get_at(handle, 0), &test_data);
        linked_list_delete(&handle);
    }

    TEST(SL, Get_Front) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_front(handle, &test_data);
        ASSERT_EQ(get_front(handle), &test_data);
        linked_list_delete(&handle);
    }

    TEST(SL, Search) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_search(handle, &test_data), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Is_Empty) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        ASSERT_TRUE(linked_list_is_empty(handle));
        linked_list_insert_back(handle, &test_data);
        ASSERT_FALSE(linked_list_is_empty(handle));
        linked_list_delete(&handle);
    }

    TEST(SL, Get_List_Size) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        ASSERT_EQ(linked_list_get_list_size(handle), 0);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_get_list_size(handle), 1);
        linked_list_delete(&handle);
    }

    TEST(SL, Iter_Previous) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_iter_previous(handle, &test_data),
                  nullptr);  // depends on implementation
        linked_list_delete(&handle);
    }

    TEST(SL, Iter_Next) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_insert_back(handle, &test_data);
        ASSERT_EQ(linked_list_iter_next(handle, &test_data),
                  nullptr);  // depends on implementation
        linked_list_delete(&handle);
    }

    TEST(SL, Map_Data) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_insert_back(handle, &test_data);
        auto fnc = [](void *data) { printf("Mapping Data\n"); };
        ASSERT_EQ(linked_list_map_data(handle, fnc), 0);
        linked_list_delete(&handle);
    }

    TEST(SL, Print) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_insert_back(handle, &test_data);
        auto printer = [](FILE *output, void *data) {};
        linked_list_print(handle, printer, stdout);
        linked_list_delete(&handle);
    }

#ifdef _DSA_ERROR_H_
    TEST(SL, Get_Error_Code) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_get_error_code(handle);
        linked_list_delete(&handle);
    }

    TEST(SL, Get_Error_Message) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, nullptr);
        linked_list_get_error_message(handle);
        linked_list_delete(&handle);
    }
#endif
}  // namespace Linked_List