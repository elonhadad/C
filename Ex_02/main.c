#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


int same_value(int const arr[], int len){
    assert(len > 1);
    //TODO assert(int/char array???) OR?

    for (int i = 0; i < len; ++i){
        if (arr[i] == arr[i+1])
            return i;
        }
    return -1;
}

int sum_n(int  const arr[], int len, int target) {
    assert(len > 1);
    assert(isascii(target));

    int checker;
    int counter = 0;

    for (int i = 0; i < len; i++) {
        checker = arr[i];
        for (int j = i + 1; j < len; j++) {
            if (checker + arr[j] == target) {
                counter++;
            }
        }
    }
    return counter;
}


int reduce(int arr[],int len){

    for (int i = 0; i < len ; ++i) {
        for (int j = 0; j < len - 1; ++j) {
            if (arr[j] == 0 && arr[j+1] != 0){
                int temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int sum = 0;

    for (int i = 0; i <  len; ++i) {
        if (arr[i] != 0)
            sum++;
    }

    return sum;
}

bool is_legal_email(char const arr_1[]){
    bool validate = false;

    if ((strlen(arr_1) > 20) || (arr_1[0] == '@'))
        return validate;

    int temp = 0;
    int index = 0;

    for (int i = 0; i < strlen(arr_1); ++i) {
        if (arr_1[i] == '@') {
            temp++;
            index = i;
        }
    }

    if (temp != 1) {
        return validate;
    }

    for (int i = 0; i < index; ++i) {
        if ((!isalpha(arr_1[i])) && (!isdigit(arr_1[i])))
            return validate;
    }

    for (int i = index +1 ; i < strlen(arr_1); ++i) {
        if (arr_1[i] == '.') {
            validate = true;
            break;
        }
    }

    for (int i = index + 1 ; i < strlen(arr_1); ++i) {
        if ((arr_1[i] != '.') && (!isalpha(arr_1[i])))
            validate =  false;
    }

    return validate;

}

bool is_same_mail(char const arr_1[], char const arr_2[]){

    if (strlen(arr_1) != strlen(arr_2))
        return false;

    for (int i = 0; i < strlen(arr_1) ; ++i){
        if (tolower(arr_2[i]) != tolower(arr_1[i]))
            return false;
    }
    return true;

}

int main() {
    int len = 3;
    int target = 8;
    int arr[]={3,5,5};
    same_value(arr, len);
    sum_n(arr, len , target);
    reduce(arr, len);

    char arr_1[]= "abc@site.com";
    char arr_2[]= "abc@site.com";
    is_legal_email(arr_1);
    is_same_mail(arr_1, arr_2);

    printf("PASS");


    return 0;
}

