/**
 * @file   exponential_search2.c
 * @brief  [Exponential Search](https://en.wikipedia.org/wiki/Exponential_search)
 * @author [GziXnine](https://github.com/AllamF5J)
 */
#include <stdio.h>     
#include <assert.h>

/**
 * Performs exponential search on a sorted array followed by binary search for the target element.
 * Exponential search is a search algorithm designed to find the position of a target value within a sorted array.
 *
 * Time Complexity: O(log(n)), where n is the number of elements in the array.
 *                  Exponential search divides the array into segments of size 2^i, where i starts from 1 and doubles with each iteration. After finding a
 *                  segment where the target value might be present, binary search is applied, which has a time complexity of O(log(n)).
 *
 * @param array          : The sorted array to search in.
 * @param size           : The size of the array.
 * @param target_element : The element to search for within the array.
 * @return               : The index of the found element if present, otherwise -1.
 */
int exponential_search(int array[], int size, int target_element);

/**
 * Performs binary search on a sorted array for the target element.
 *
 * @param array          : The sorted array to search in.
 * @param begin          : The starting index of the subarray to search within.
 * @param end            : The ending index of the subarray to search within.
 * @param target_element : The element to search for within the array.
 * @return               : The index of the found element if present, otherwise -1.
 */
int binary_search(int array[], int begin, int end, int target_element); // Renamed to follow convention

/**
 * @brief Test function for the exponential_search function.
 */
static void test();

int main()
{
    test();  // run self-test implementations

    return 0;
}

int exponential_search(int array[], int size, int target_element)
{
    int i = 1;

    // Handle the case where the array is empty
    if (size == 0)
    {
        return -1;  // Return -1 indicating that the element was not found
    }

    if (array[0] == target_element)
    {
        return 0;
    }

    // Perform exponential search to find the appropriate range where the target element might be present
    while ((i < size) && (array[i] <= target_element))
    {
        i <<= 1;
    }

    return binary_search(array, i >> 1, (i < size) ? i : size - 1, target_element); // Changed to match function name in CMakeLists.txt
}

int binary_search(int array[], int begin, int end, int target_element)
{
    while (begin <= end)
    {
        // I use "begin + ((end - begin) / 2)" instead of "((end + begin) / 2)" to avoid causing overflow
        int middle = begin + ((end - begin) / 2);  // ((end + begin) / 2)

        if (array[middle] == target_element)
        {
            return middle;
        }
        else if (array[middle] < target_element)
        {
            begin = middle + 1;
        }
        else
        {
            end = middle - 1;
        }
    }

    return -1;
}

static void test()
{
    int arr_empty[] = {0}; /**< Empty array */
    assert(exponential_search(arr_empty, 0, 10) == -1);

    int arr_smaller[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element smaller than all elements */
    assert(exponential_search(arr_smaller, 5, 5) == -1);

    int arr_larger[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element larger than all elements */
    assert(exponential_search(arr_larger, 5, 60) == -1);

    int arr_not_present[] = {10, 20, 30, 40, 50}; /**< Array with elements, target element not present */
    assert(exponential_search(arr_not_present, 5, 25) == -1);

    int arr_random[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found in the middle */
    assert(exponential_search(arr_random, 5, 30) == 2);

    int arr_beginning[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at the beginning */
    assert(exponential_search(arr_beginning, 5, 10) == 0);

    int arr_end[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at the end */
    assert(exponential_search(arr_end, 5, 50) == 4);

    int arr_odd_index[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at an odd index */
    assert(exponential_search(arr_odd_index, 5, 40) == 3);

    int arr_even_index[] = {10, 20, 30, 40, 50}; /**< Array with elements, random element found at an even index */
    assert(exponential_search(arr_even_index, 5, 20) == 1);

    // Larger arrays
    int large_arr[1000];
    for (int i = 0; i < 1000; i++) 
    {
        large_arr[i] = i + 1; // Filling with numbers from 1 to 1000
    }
    assert(exponential_search(large_arr, 1000, 500) == 499); // Middle element
    assert(exponential_search(large_arr, 1000, 1) == 0); // First element
    assert(exponential_search(large_arr, 1000, 1000) == 999); // Last element
    assert(exponential_search(large_arr, 1000, 1001) == -1); // Element larger than all

    printf("All tests have successfully passed!\n");
}
