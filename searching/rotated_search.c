/**
 * @file   rotated_search.c
 * @brief  [Rotated Search](https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/)
 * @author [GziXnine](https://github.com/AllamF5J)
 */
#include <assert.h>
#include <stdio.h>

/**
 * Performs search on a rotated sorted array to find the target element.
 *
 * Time Complexity: O(log(n)), where n is the number of elements in the array.
 *                  Rotated search is a modified binary search algorithm that works efficiently even on rotated sorted arrays.
 *                  such as => {8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 1, 2, 3, 4, 5, 6, 7};
 *
 * @param array          : The rotated sorted array to search in.
 * @param begin          : The starting index of the subarray to search within.
 * @param end            : The ending index of the subarray to search within.
 * @param target_element : The element to search for within the array.
 *
 * @return               : The index of the found element if present, otherwise -1.
 */
int rotated_search(int array[], int begin, int end, int target_element);

/**
 * @brief Test function for the rotated_search function.
 */
static void test();

int main()
{
    test();  // run self-test implementations

    return 0;
}

int rotated_search(int array[], int begin, int end, int target_element)
{
    while (begin <= end)
    {
        // I use "begin + ((end - begin) / 2)" instead of "((end + begin) / 2)" to avoid causing overflow
        int middle = begin + ((end - begin) / 2);  // ((end + begin) / 2)

        if (array[middle] == target_element)
        {
            return middle;
        }

        if (array[begin] <= array[middle])
        {
            if ((array[middle] >= target_element) && (array[begin] <= target_element))
            {
                end = middle - 1;
            }
            else
            {
                begin = middle + 1;
            }
        }
        else
        {
            if ((array[middle] <= target_element) && (array[begin] >= target_element))
            {
                begin = middle + 1;
            }
            else
            {
                end = middle - 1;
            }
        }
    }

    return -1;
}

static void test()
{
    int arr_empty[] = {0}; /**< Empty array */
    assert(rotated_search(arr_empty, 0, 0, 10) == -1);

    int arr_smaller[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element smaller than all elements */
    assert(rotated_search(arr_smaller, 0, 4, 5) == -1);

    int arr_larger[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element larger than all elements */
    assert(rotated_search(arr_larger, 0, 4, 60) == -1);

    int arr_not_present[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element not present */
    assert(rotated_search(arr_not_present, 0, 4, 25) == -1);

    int arr_random[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found in the middle */
    assert(rotated_search(arr_random, 0, 4, 30) == 2);

    int arr_beginning[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at the beginning */
    assert(rotated_search(arr_beginning, 0, 4, 10) == 0);

    int arr_end[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at the end */
    assert(rotated_search(arr_end, 0, 4, 50) == 4);

    int arr_odd_index[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at an odd index */
    assert(rotated_search(arr_odd_index, 0, 4, 40) == 3);

    int arr_even_index[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at an even index */
    assert(rotated_search(arr_even_index, 0, 4, 20) == 1);

    // Larger arrays
    int large_arr[1000];
    for (int i = 0; i < 1000; i++) 
    {
        large_arr[i] = i + 1; // Filling with numbers from 1 to 1000
    }
    assert(rotated_search(large_arr, 0, 999, 500) == 499);   // Middle element
    assert(rotated_search(large_arr, 0, 999, 1) == 0);       // First element
    assert(rotated_search(large_arr, 0, 999, 1000) == 999);  // Last element
    assert(rotated_search(large_arr, 0, 999, 1001) == -1);   // Element larger than all

    printf("All tests have successfully passed!\n");
}
