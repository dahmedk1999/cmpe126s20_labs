#include "doubly_linked_list.h"

namespace lab6 {
    // Auxiliary Functions
    unsigned partition(int* to_sort, int low, int high);

    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort);
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right);

    void quicksort(int* to_sort, int low, int high){

    }

    unsigned partititon(int* to_sort, int low, int high)
    {
    int i=low,j=high+1;
    while(1) {
        while (to_sort[(++i)] < to_sort[low])
            if (i == high) break;
        while (to_sort[low] < to_sort[--j])
            if (j == low) break;
        if (i >= j)break;
       // std::swap(to_sort, i, j);
    }
//    std::swap(to_sort,low,j);
    return j;
    }

    void mergesort(doubly_linked_list& to_sort)
    {

    }

    doubly_linked_list recursive_merge_sort(doubly_linked_list to_sort){

    }

    //Used for the merging the two lists
    doubly_linked_list merge(doubly_linked_list left, doubly_linked_list right){

    }
}