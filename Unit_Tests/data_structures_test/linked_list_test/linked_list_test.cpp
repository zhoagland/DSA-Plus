#include <gtest/gtest.h>
#include "linked_list.h"
#include "linked_list_internal.h"

namespace Linked_List {
    #define SL Singly_Linked
    #define DL Doubly_Linked
    #define CL Circularly_Linked




    // Helper data for tests
    int test_data[] = {0, 1, 2, 3, 4};

    void map_func(void *data) {
        int val = *(int *)data;
        printf("%d\n", val);
    }

    TEST(SL, Init) {
        LinkedListHandle handle = linked_list_initialize(SINGLY_LINKED_LIST, &test_data);
        ASSERT_NE(handle, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t*)handle)->list_length , 1);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->data, &test_data);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head,
                  ((dsa_linked_list_control_block_t *)handle)->tail);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->next_node, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->previous_node, nullptr);
        
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->tail->next_node, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->tail->previous_node, nullptr);


        LinkedListHandle handle2 = linked_list_initialize(SINGLY_LINKED_LIST, NULL);
        ASSERT_NE(handle2, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->list_length, 0);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head,
                  ((dsa_linked_list_control_block_t *)handle2)->tail);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->tail, nullptr);


        ASSERT_NE(handle, handle2);

        linked_list_delete(&handle);
        linked_list_delete(&handle2);
    }

    
    TEST(DL, Init) {
        LinkedListHandle handle = linked_list_initialize(DOUBLY_LINKED_LIST, &test_data);
        ASSERT_NE(handle, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->list_length, 1);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->data, &test_data);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head,
                  ((dsa_linked_list_control_block_t *)handle)->tail);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->next_node, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->previous_node, nullptr);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->tail->next_node, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->tail->previous_node, nullptr);

        LinkedListHandle handle2 = linked_list_initialize(DOUBLY_LINKED_LIST, NULL);
        ASSERT_NE(handle2, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->list_length, 0);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head,
                  ((dsa_linked_list_control_block_t *)handle2)->tail);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->tail, nullptr);

        ASSERT_NE(handle2, nullptr);

        ASSERT_NE(handle, handle2);

        linked_list_delete(&handle);
        linked_list_delete(&handle2);
    
    }

    
    TEST(CL, Init) {
        LinkedListHandle handle = linked_list_initialize(CIRCULARLY_LINKED_LIST, &test_data);
        ASSERT_NE(handle, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->list_length, 1);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->data, &test_data);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head,
                  ((dsa_linked_list_control_block_t *)handle)->tail);

        ASSERT_NE(((dsa_linked_list_control_block_t *)handle)->head->next_node, nullptr);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->head->previous_node,
                  ((dsa_linked_list_control_block_t *)handle)->tail);

        ASSERT_NE(((dsa_linked_list_control_block_t *)handle)->tail->previous_node, nullptr);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle)->tail->next_node,
                  ((dsa_linked_list_control_block_t *)handle)->head);

        LinkedListHandle handle2 = linked_list_initialize(CIRCULARLY_LINKED_LIST, NULL);

        ASSERT_NE(handle2, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->list_length, 0);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head,
                  ((dsa_linked_list_control_block_t *)handle2)->tail);

        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->head, nullptr);
        ASSERT_EQ(((dsa_linked_list_control_block_t *)handle2)->tail, nullptr);

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
        LinkedListHandle handle = linked_list_initialize(CIRCULARLY_LINKED_LIST, &test_data);
        ASSERT_EQ(linked_list_delete(&handle), 0);
    }

    TEST(SL, Mapped_Action_On_Delete) {
        auto mapped_act_on_del  = [](void *data) { printf("Data Deleted %d", *(int *)data); };

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
        auto printer = [](void *data) {};
        linked_list_print(handle, printer);
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