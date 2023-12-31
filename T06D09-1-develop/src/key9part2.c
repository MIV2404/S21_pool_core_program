#include <stdio.h>

#define LEN 100

int input(int *data, int *length);
int filter_arrays(int *data_1, int *length1, int *data_2, int *length2);
void shifting(int *data, int *length1, int length2);
void sum(int *data_1, int len, int *data_2, int *result, int *result_length);
int sub(int *data_1, int len, int *data_2, int *result, int *result_length);
void output(int *data_1, int length1, int *data_2, int length2, int err_sub);
void output_data(int *data, int length);

int main() {
    int data1[LEN], data2[LEN];
    int length1 = 0, length2 = 0;
    
    if (!input(data1, &length1) && !input(data2, &length2)) {
        int data3[LEN + 1], length3 = 0, data4[LEN], length4 = 0, err_sub = 0;
        err_sub = filter_arrays(data1, &length1, data2, &length2);

        sum(data1, length1, data2, data3, &length3);
        if (err_sub == 0) {
            err_sub = sub(data1, length1, data2, data4, &length4);
        }
        output(data3, length3, data4, length4, err_sub);
    }
    return 0;
}

// ввод элементов массива и сохранение в data
int input(int *data, int *length) {
    int err_input = 0, count = 0;
    char ch;
    do {
        if (scanf("%d", &data[*length])) {
            count++;
            ch = getchar();
            if ((ch != '\n' && ch != ' ') && (data[*length] > 9 || count > LEN)) {
                err_input = 1;
            }
            if (data[*length] != 0 || *length != 0) {
                (*length)++;
            }
        } else {
            err_input = 1;
        }
        if (err_input == 1) {
            break;
        }
    } while (ch != '\n');
    if (err_input) {
        printf("n/a");
    }
    return err_input;
}

// фильтрация массива чтобы они имели одинаковую длину
int filter_arrays(int *data_1, int *length1, int *data_2, int *length2) {
    int err_sub = 0;
    if (*length2 > *length1) {
        err_sub = 1;
        shifting(data_1, length1, *length2);
    } else if (*length1 > *length2) {
        shifting(data_2, length2, *length1);
    }

    return err_sub;
}
// сдвиг элементов массива data на основе длин
void shifting(int *data, int *length1, int length2) {
    int i;
    for (i = (*length1) - 1; i >= 0; i--) {
        data[i + length2 - (*length1)] = data[i];
    }
    for (i = 0; i < length2 - (*length1); i++) {
        data[i] = 0;
    }
    *length1 = length2;
}

// складывание элементов массива и сохранение результата в  массив result
void sum(int *data_1, int len, int *data_2, int *result, int *result_length) {
    int remain = 0, i;
    for (i = len - 1; i >= 0; i--) {
        result[i + 1] = (data_1[i] + data_2[i] + remain) % 10;
        remain = (data_1[i] + data_2[i] + remain) / 10;
    }
    result[0] = remain;
    if (result[0] == 0) {
        for (i = 0; i < len; i++) {
            result[i] = result[i + 1];
        }
        *result_length = len;
    } else {
        *result_length = len + 1;
    }
}

// вычитание и сохранение результата в result
int sub(int *data_1, int len, int *data_2, int *result, int *result_length) {
    int err_sub = 0;
    int remain = 0, i;
    for (i = len - 1; i >= 0; i--) {
        if (data_1[i] - remain >= data_2[i]) {
            result[i] = data_1[i] - remain - data_2[i];
            remain = 0;
        } else {
            result[i] = 10 + data_1[i] - remain - data_2[i];
            remain = 1;
        }
    }
    *result_length = len;
    if (remain == 0) {
        int count = 0;
        while (result[count] == 0) {
            count++;
        }
        for (i = 0; i < (*result_length) - count; i++) {
            result[i] = result[i + count];
        }
        *result_length -= count;
    } else {
        err_sub = 1;  
    }
    return err_sub;
}

// выводит содержимое массивов data_1 и data_2
void output(int *data_1, int length1, int *data_2, int length2, int err_sub) {
    output_data(data_1, length1);
    printf("\n");
    if (err_sub == 0) {
        output_data(data_2, length2);
    } else {
        printf("n/a");
    }
}

// выводит содержимое массива data заданной длины
void output_data(int *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", data[i]);
        if (i != (length - 1)) {
            printf(" ");
        }
    }
}
