#include <stdio.h>
void print_array(int v[], int n);   // function to print a whole array
void swap(int v[], int i, int j) {  // function to swap elements of array
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
/*m_qsort function to sort an array by taking middle number as pivot and sorting
 * on the basis of it. if number is less than pivot, put it on left and if it is
 * bigger, put it on right side of the pivot.*/
void m_qsort(
    int v[],
    int left,
    int right) {  // it will take an array, starting position of array i.e. 0 by
                  // and right which is the last element position.
    int i, last;  // i to indexing and last to store the pivot.
    if (left >= right)  // checking base case i.e. if left comes eqaul to right,
                        // that mean array only contain 1 element, therefore no
                        // sorting is needed.
        return;
    swap(v, left,
         ((left + right) /
          2));    // swapping the middle element(pivot), with zeroth element
    last = left;  // storing pivot in last
    for (i = left + 1; i <= right;
         i++) {  // checking for character from left+1 which is last or pivot,
                 // if it is smaller than pivot, pushing it to left
        if (v[i] < v[left]) {
            swap(v, ++last,
                 i);  // incrementing last for the recursion after each swap.
        }
    }
    swap(v, left, last);         // re-swapping array to it's original form
    m_qsort(v, left, last - 1);  // again calling m_qsort to sort left partition
    m_qsort(v, last + 1, right);  // same for the right partition
}
void print_array(int v[], int n) {  // function to print a whole array.
    printf("{");
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("}");
}
int main() {
    int arr[] = {1, 3, 53, 32, 8, 34, 2, 3, 5};
    m_qsort(arr, 0, 8);
    print_array(arr, 9);
    return 0;
}