//Задание 1
//#include <mpi.h>
//#include <stdio.h>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    printf("process %d size %d \n", rank, size);
//    MPI_Finalize();
//}
//Задание 2
//#include <mpi.h>
//#include <iostream>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0)
//    {
//        int a[10];
//        for (int i = 0; i < 10; i++)
//            a[i] = rand() % 100;
//        printf("array was sent by process number %d \n", rank);
//        for (int i = 1; i < size; i++)
//            MPI_Send(&a, 10, MPI_INT, i, 1000, MPI_COMM_WORLD);
//    } else if (rank == 1)
//    {
//        int b[10];
//        printf("print array by process number %d \n", rank);
//        MPI_Recv(&b, 10, MPI_INT, 0, 1000, MPI_COMM_WORLD, &status);
//        for (int i = 0; i < 10; i++)
//            printf("%d ", b[i]);
//    }
//    MPI_Finalize();
//}
//Задание 3
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    int A[10];
//
//    for (int i = 0; i < 10; i++)
//    {
//        A[i] = rand() % 100;
//    }
//
//    if (rank == 1) {
//        for (int i = 0; i < size; i++)
//        {
//            if (i != 1)
//            {
//                MPI_Send(A, 10, MPI_INT, i, 1000, MPI_COMM_WORLD);
//            }
//        }
//        printf("process=%d sent array \n", rank);
//    }
//    else
//    {
//        int count;
//        MPI_Probe(MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &status);
//        MPI_Get_count(&status, MPI_INT, &count);
//
//        int* buffer = new int[count];
//
//        MPI_Recv(buffer, count, MPI_INT, 1, 1000, MPI_COMM_WORLD, &status);
//
//        printf("process=%d ", rank);
//
//        for (int i = 0; i < count; i++)
//        {
//            printf("A[%d]=%d ", i, buffer[i]);
//        }
//    }
//    MPI_Finalize();
//}
//Задание 4
//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//
//int main(int argc, char** argv)
//{
//	int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	if (rank == 0) 
//	{
//
//		int a[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
//		int sizeOfBlock = 12 / size + 1;
//
//		printf("process=%d: ", rank);
//		for (int i = 0; i < sizeOfBlock; i++) 
//		{
//			printf("%d ", a[i]);
//		}
//
//		for (int i = 1; i < size; i++) 
//		{
//
//			int shift = i * (12 / size) + i;
//			if (12 - shift <= sizeOfBlock)
//			{
//				sizeOfBlock = 12 - shift;
//			}
//
//			if (sizeOfBlock < 0) {
//				MPI_Send(a + shift, 0, MPI_INT, i, 1000, MPI_COMM_WORLD);
//			}
//			else {
//				MPI_Send(a + shift, sizeOfBlock, MPI_INT, i, 1000, MPI_COMM_WORLD);
//			}
//
//		}
//	}
//
//	else {
//		int receivedBlock;
//		MPI_Probe(MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_INT, &receivedBlock);
//		int* buffer = new int[receivedBlock];
//
//		MPI_Recv(buffer, receivedBlock, MPI_INT, 0, 1000, MPI_COMM_WORLD, &status);
//
//		printf("process=%d: ", rank);
//		for (int i = 0; i < receivedBlock; i++)
//		{
//			printf("%d ", buffer[i]);
//		}
//	}
//
//	MPI_Finalize();
//}
//Задание 5
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    int a = 5;
//    int b = 2;
//    const int vectorSize = 10;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0) {
//
//        int x[vectorSize];
//        int y[vectorSize];
//        for (int i = 0; i < vectorSize; i++)
//        {
//            x[i] = rand() % 5 + 1;
//            y[i] = rand() % 5 + 1;
//        }
//
//        int block = ceil((double)vectorSize / (size - 1));
//
//        for (int i = 1; i < size; i++) {
//
//            int shift = (i - 1) * block;
//
//            if (vectorSize - shift <= block) {
//                block = vectorSize - shift;
//            }
//            if (block < 0) {
//                MPI_Send(x + shift, 0, MPI_INT, i, 1000, MPI_COMM_WORLD);
//                MPI_Send(y + shift, 0, MPI_INT, i, 2000, MPI_COMM_WORLD);
//			} else {
               /* MPI_Send(x + shift, block, MPI_INT, i, 1000, MPI_COMM_WORLD);*/
//                MPI_Send(y + shift, block, MPI_INT, i, 2000, MPI_COMM_WORLD);
//			}
//        }
//
//        for (int i = 1; i < size; i++) 
//        {
//
//            MPI_Status statusA;
//            int resultCountA;
//            int * resultBufferA;
//
//            MPI_Probe(i, 3000, MPI_COMM_WORLD, &statusA);
//
//            MPI_Get_count(&statusA, MPI_INT, &resultCountA);
//
//            resultBufferA = new int[resultCountA];
//
//            MPI_Recv(resultBufferA, resultCountA, MPI_INT, i, 3000, MPI_COMM_WORLD, &statusA);
//            printf("\n process=%d results A from process=%d :", rank, i);
//
//            for (int i = 0; i < resultCountA; i++)
//            {
//                printf("%d ", resultBufferA[i]);
//            }
//
//            MPI_Status statusC;
//            int resultCountC;
//            int* resultBufferC;
//
//            MPI_Probe(i, 3002, MPI_COMM_WORLD, &statusC);
//
//            MPI_Get_count(&statusC, MPI_INT, &resultCountC);
//
//            resultBufferC = new int[resultCountC];
//
//            MPI_Recv(resultBufferC, resultCountC, MPI_INT, i, 3002, MPI_COMM_WORLD, &statusC);
//            printf("\n process=%d results C from process=%d :", rank, i);
//
//            for (int i = 0; i < resultCountC; i++)
//            {
//                printf("%d ", resultBufferC[i]);
//            }
//        }
//
//    } else {
//
//        int countOfElemX = 0;
//        int countOfElemY = 0;
//        int* xBuffer;
//        int* yBuffer;
//
//        MPI_Status xStatus;
//        MPI_Status yStatus;
//
//        MPI_Probe(MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &xStatus);
//        MPI_Get_count(&xStatus, MPI_INT, &countOfElemX);
//        xBuffer = new int[countOfElemX];
//        MPI_Recv(xBuffer, countOfElemX, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &xStatus);
//
//        MPI_Probe(MPI_ANY_SOURCE, 2000, MPI_COMM_WORLD, &yStatus);
//        MPI_Get_count(&yStatus, MPI_INT, &countOfElemY);
//        yBuffer = new int[countOfElemY];
//        MPI_Recv(yBuffer, countOfElemY, MPI_INT, MPI_ANY_SOURCE, 2000, MPI_COMM_WORLD, &yStatus);
//
//        printf("process=%d : \n", rank);
//
//        int* za = new int[countOfElemX];
//        int* zc = new int[countOfElemX];
//
//        for (int i = 0; i < countOfElemX; i++) {
//            za[i] = a * xBuffer[i] + b * yBuffer[i];
//            zc[i] = xBuffer[i] * yBuffer[i];
//            yBuffer[i] = a * xBuffer[i] + b * yBuffer[i];
//        }
//
//        for (int i = 0; i < countOfElemX; i++) {
//            printf("x = %d ", xBuffer[i]);
//            printf("y = %d ", yBuffer[i]);
//            printf("zA = %d ", za[i]);
//            printf("zC = %d \n", zc[i]);
//        }
//
//        MPI_Send(za, countOfElemX, MPI_INT, 0, 3000, MPI_COMM_WORLD);
//        MPI_Send(zc, countOfElemX, MPI_INT, 0, 3002, MPI_COMM_WORLD);
//    }
//
//    MPI_Finalize();
//
//}
//Задание 6
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    const int matrixSize = 3;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    float C[matrixSize][matrixSize];
//
//    if (rank == 0) {
//
//        float A[matrixSize][matrixSize];
//        float B[matrixSize][matrixSize];
//
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                B[i][j] = rand() % 5 + 1;
//            }
//        }
//        printf("\nProcess = %d :\n", rank);
//        printf("Array A : \n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("A[%d][%d]=%.3g ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//
//        printf("Array B : \n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("B[%d][%d]=%.3g ", i, j, B[i][j]);
//            }
//            printf("\n");
//        }
//
//        int block = ceil((double)matrixSize / (size - 1));
//
//        float cBuffer[matrixSize][matrixSize];
//
//        for (int i = 1; i < size; i++) {
//
//            int shift = (i - 1) * block;
//
//            if (matrixSize - shift <= block) {
//                block = matrixSize - shift;
//            }
//            
//            MPI_Send(&block, 1, MPI_INT, i, 1000, MPI_COMM_WORLD);
//            MPI_Send(&shift, 1, MPI_INT, i, 2000, MPI_COMM_WORLD);
//
//            for (int j = shift; j < shift + block; j++) {
//                MPI_Send(&A[j][0], matrixSize, MPI_FLOAT, i, 1001, MPI_COMM_WORLD);
//                MPI_Send(&B[j][0], matrixSize, MPI_FLOAT, i, 2001, MPI_COMM_WORLD);
//
//            }
//
//            MPI_Status cStatus;
//
//            for (int j = shift; j < shift + block; j++) {
//                MPI_Recv(cBuffer[j], matrixSize, MPI_FLOAT, i, 1003, MPI_COMM_WORLD, &cStatus);
//            }
//		
//        }
//        printf("Process = %d result Array C:\n", rank);
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("C[%d][%d]=%.3g ", i, j, cBuffer[i][j]);
//            }
//            printf("\n");
//        }
//
//    } else {
//
//        int block;
//        int shift;
//        float  aBuffer[matrixSize][matrixSize];
//        float  bBuffer[matrixSize][matrixSize];
//        MPI_Status blockStatus;
//        MPI_Status shiftStatus;
//        MPI_Status lineAStatus;
//        MPI_Status lineBStatus;
//
//
//        MPI_Recv(&block, 1, MPI_INT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &blockStatus);
//        MPI_Recv(&shift, 1, MPI_INT, MPI_ANY_SOURCE, 2000, MPI_COMM_WORLD, &shiftStatus);
//
//        printf("\nProcess = %d \n", rank);
//
//        for (int i = shift; i < shift + block; i++) {
//
//            MPI_Recv(&aBuffer[i], matrixSize, MPI_FLOAT, MPI_ANY_SOURCE, 1001, MPI_COMM_WORLD, &lineAStatus);
//            MPI_Recv(&bBuffer[i], matrixSize, MPI_FLOAT, MPI_ANY_SOURCE, 2001, MPI_COMM_WORLD, &lineBStatus);
//
//            for (int j = 0; j < matrixSize; j++) {
//                printf("A[%d][%d]=%.3g ", i, j, aBuffer[i][j]);      
//            }
//            printf("\n");
//
//            for (int j = 0; j < matrixSize; j++) {
//                printf("B[%d][%d]=%.3g ", i, j, bBuffer[i][j]);            
//            }
//
//            printf("\n");
//
//            for (int j = 0; j < matrixSize; j++) {
//                C[i][j] = aBuffer[i][j] * bBuffer[i][j];
//                printf("C[%d][%d]=%.3g ", i, j, C[i][j]);
//            }
//            printf("\n");
//
//            MPI_Send(&C[i][0], matrixSize, MPI_FLOAT, 0, 1003, MPI_COMM_WORLD);
//        }
//
//    }
//
//    MPI_Finalize();
//
//}
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    const int matrixSize = 3;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    float C[matrixSize][matrixSize];
//
//    if (rank == 0) {
//
//        float A[matrixSize][matrixSize];
//        float B[matrixSize][matrixSize];
//
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                B[i][j] = rand() % 5 + 1;
//            }
//        }
//        printf("\nProcess = %d :\n", rank);
//        printf("Array A : \n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("A[%d][%d]=%.3g ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//
//        printf("Array B : \n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("B[%d][%d]=%.3g ", i, j, B[i][j]);
//            }
//            printf("\n");
//        }
//
//        int block = ceil((double)matrixSize / (size - 1));
//
//        printf("Process = %d result Array C:\n", rank);
//
//        for (int i = 1; i < size; i++) {
//
//            int shift = (i - 1) * block;
//
//            if (matrixSize - shift <= block) {
//                block = matrixSize - shift;
//            }
//
//            MPI_Send(&B[0][0], matrixSize * matrixSize, MPI_FLOAT, i, 2000, MPI_COMM_WORLD);
//
//            for (int j = shift; j < shift + block; j++) {
//                MPI_Send(&A[j], matrixSize, MPI_FLOAT, i, 1000, MPI_COMM_WORLD);
//            }
//
//            float* cBuffer = new float[matrixSize];
//            MPI_Status cStatus;
//
//            for (int j = 0; j < matrixSize; j++) {
//                cBuffer[j] = 0;
//            }
//
//            MPI_Recv(cBuffer, matrixSize, MPI_FLOAT, i, 1001, MPI_COMM_WORLD, &cStatus);
//
//            for (int j = 0; j < matrixSize; j++) {
//                printf("%.3g ", cBuffer[j]);
//            }
//            printf("\n");
//
//        }
//
//    }
//    else {
//
//        float *aBuffer = new float[matrixSize];
//        float bBuffer[matrixSize][matrixSize];
//        float result[matrixSize];
//        MPI_Status lineAStatus;
//        MPI_Status bStatus;
//
//        for (int i = 0; i < matrixSize; i++) {
//            result[i] = 0;
//        }
//
//        MPI_Recv(aBuffer, matrixSize, MPI_FLOAT, MPI_ANY_SOURCE, 1000, MPI_COMM_WORLD, &lineAStatus);
//        MPI_Recv(&bBuffer, matrixSize * matrixSize, MPI_FLOAT, MPI_ANY_SOURCE, 2000, MPI_COMM_WORLD, &bStatus);
//
//        printf("\nProcess = %d \n", rank);
//
//        for (int i = 0; i < matrixSize; i++) {
//            printf("A[%d]=%.3g ", i, aBuffer[i]);
//        }
//        printf("\n");
//
//        for (int i = 0; i < matrixSize; i++) {
//            for (int j = 0; j < matrixSize; j++) {
//                printf("B[%d][%d]=%.3g ", i, j, bBuffer[i][j]);
//            }
//            printf("\n");
//        }
//
//
//        for (int i = 0; i < matrixSize; i++) {
//            for (int j = 0; j < matrixSize; j++) {
//                result[i] += aBuffer[j] * bBuffer[j][i];
//            }
//        }
//
//        for (int i = 0; i < matrixSize; i++) {
//            printf("C[%d]=%.3g ", i, result[i]);
//        }
//
//        MPI_Send(&result, matrixSize, MPI_FLOAT, 0, 1001, MPI_COMM_WORLD);
//
//    }
//
//    MPI_Finalize();
//
//}
//Задание8
#include <mpi.h>
#include<stdio.h>
#include <iostream>
#include "time.h"

int main(int argc, char** argv) {

    int rank, size;
    const int arraySize = 15;

    int block;
    float* x = NULL;
    float* y = NULL;
    float minVal;
    int minIndex;

    struct {
        float value;
        int   index;
    } in, out;

    MPI_Comm comm = MPI_COMM_WORLD;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        x = (float*)malloc(arraySize * sizeof(float));
        printf("Process=%d \nArray :", rank);
        srand(time(0));
        for (int i = 0; i < arraySize; i++)
        {
            x[i] = rand() % 100 + 1;
            printf("%.3g ", x[i]);
        }
        printf("\n");
    }
    
    block = arraySize / size;
    y = (float*)malloc(block * sizeof(float));

    MPI_Scatter(x, block, MPI_FLOAT, y, block, MPI_FLOAT, 0, comm);

    in.index = 0;
    in.value = y[0];

    printf("Process = %d \n", rank);
    for (int i = 0; i < block; i++) {
        if (y[i] < in.value) {
            in.value = y[i]; 
            in.index = i;
        }
        printf("%.3g ", y[i]);
    }
    in.index = rank * block + in.index;

    MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MINLOC, 0, comm);

    if (rank == 0) {
        minVal = out.value;
        minIndex = out.index;
        printf("\nProcess = %i Result : min= %.3g , index = %d\n", rank, minVal, minIndex);
    }

    MPI_Finalize();

}

//Задание16
