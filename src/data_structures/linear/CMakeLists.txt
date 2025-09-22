add_library(dsa_linked_list STATIC 
	./linked_list.c
)

target_include_directories(dsa_linked_list PUBLIC
	include
)