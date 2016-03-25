/*
Write a program to generate elements of a matrix in spiral order.
Store the generated elements in single dimensional array and return that array.

Directions for Spiral are : Go Right ,Go Down ,Go Left, Go Up
Ex:

Matrix:
1	2	3
4	5	6
7	8	9

Spiral order:
1	2	3	6	9	8	7	4	5

Given matrix is a two dimensional array(input_array) with dimensions rows, columns.
If rows, columns are invalid then return NULL.
If input_array is NULL then return NULL.

Example Input :
int board[2][3]={
				 {4,6,7},
				 {1,3,8}
				};
spiral(2,2,(int **)board); // Rows followed by columns followed by board

Example Output : Return an array consisting of {4,6,7,8,3,1};

Note : Check the function Parameters ,Its a double pointer .

*/


#include "stdafx.h"
#include<stdlib.h>

int** allocate_memory(int rows, int columns)
{
	int** return_array;
	int counter;
	return_array = (int **)malloc(sizeof(int*)*(rows));
	for (counter = 0; counter<rows; counter++)
		*(return_array + counter) = (int *)malloc(sizeof(int)*(columns));
	return return_array;
}

int **rotate_matrix_by_ninty_degrees_anticlockwise(int rows, int columns, int **input_array)
{
	int **convected_matrix, i, j;
	convected_matrix = allocate_memory(columns, rows);
	for (i = 0; i<columns; i++)
	{
		for (j = 0; j<rows; j++)
		{
			convected_matrix[i][j] = input_array[j][columns - 1 - i];
		}
	}
	return convected_matrix;
}

int *combine_two_arrays(int *array1, int *array2, int size1, int size2)
{
	int index, *combine_array;
	combine_array = (int *)malloc(sizeof(int)*(size1 + size2));
	for (index = 0; index<size1; index++)
		combine_array[index] = array1[index];
	for (; index<size1 + size2; index++)
		combine_array[index] = array2[index - size1];
	return combine_array;
}

int *spiral(int rows, int columns, int **input_array)
{
	int  *result_from_next_function_call, **rotated_matrix;

	//recursion terminate condition
	if (rows == 1)
		return *input_array;

	//basic condition
	if (rows <= 0 || columns <= 0 || input_array == NULL)
		return NULL;

	rotated_matrix = rotate_matrix_by_ninty_degrees_anticlockwise(rows - 1, columns, input_array + 1);
	result_from_next_function_call = spiral(columns, rows - 1, rotated_matrix);
	return combine_two_arrays(*input_array, result_from_next_function_call, columns, (rows - 1)*columns);
}
