#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

int ListNode_swap(ListNode *a, ListNode *b)
{
	void *temp = a->value;
	a->value = b->value;
	b->value = temp;
	
	return 0;
}

int List_bubble_sort(List *list, List_compare cmp)
{
	//check for a empty list or one node lidt
	if(List_count(list) <= 1) {
		return 0;
	}
	int i;
	for (i = 0; i < (List_count(list)-1); i++) {
		LIST_FOREACH(list, first, next, cur) {
			if(cur->next) {
				int rc = cmp(cur->value, cur->next->value);
				if (rc > 0) {
					ListNode_swap(cur, cur->next);
				}
			}
		}
	}
	return 0;
}

List *List_selection_sort(List *list, List_compare cmp)
{
	int length = List_count(list);
	if(length <= 1) {
		return list;
	}
	List *res = List_create();
	int i;
	for (i = 0; i < length; i++) {
		ListNode *val = NULL;
		LIST_FOREACH(list, first, next, cur) {
			if(val != NULL) {
				int rc = cmp(cur->value, val->value);
				if (rc < 0) {
					val = cur;
				}
			} else {
				val = cur;
				continue;
			}
		}
		List_push(res, val->value);
		List_remove(list, val);
	}
	return res;
}
