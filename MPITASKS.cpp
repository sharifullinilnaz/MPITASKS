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
//    } else 
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
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("x[%d] = %d ", i, x[i]);
//        }
//        printf("\n");
//
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("y[%d] = %d ", i, y[i]);
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
//                MPI_Send(x + shift, block, MPI_INT, i, 1000, MPI_COMM_WORLD);
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
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("x[%d] = %d ", i, x[i]);
//        }
//        printf("\n");
//
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("y[%d] = %d ", i, y[i]);
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
//                MPI_Send(x + shift, block, MPI_INT, i, 1000, MPI_COMM_WORLD);
//                MPI_Send(y + shift, block, MPI_INT, i, 2000, MPI_COMM_WORLD);
//			}
//        }
//
//        for (int i = 1; i < size; i++) 
//        {
//
//            MPI_Status statusB;
//            int resultCountB;
//
//            MPI_Probe(i, 3000, MPI_COMM_WORLD, &statusB);
//
//            MPI_Get_count(&statusB, MPI_INT, &resultCountB);
//
//
//            MPI_Recv(y, resultCountB, MPI_INT, i, 3000, MPI_COMM_WORLD, &statusB);
//            printf("\n process=%d results B from process=%d :", rank, i);
//
//            for (int i = 0; i < resultCountB; i++)
//            {
//                printf("%d ", y[i]);
//            }
//
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
//        int* yB = new int[countOfElemY];
//
//        for (int i = 0; i < countOfElemY; i++) {
//            yB[i] = a * xBuffer[i] + b * yBuffer[i];         
//        }
//
//        for (int i = 0; i < countOfElemY; i++) {
//            printf("x = %d ", xBuffer[i]);
//            printf("y = %d ", yBuffer[i]);
//            printf("yB = %d ", yB[i]);
//        }
//
//        MPI_Send(yB, countOfElemY, MPI_INT, 0, 3000, MPI_COMM_WORLD);
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
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("x[%d] = %d ", i, x[i]);
//        }
//        printf("\n");
//
//        for (int i = 0; i < vectorSize; i++)
//        {
//            printf("y[%d] = %d ", i, y[i]);
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
//                MPI_Send(x + shift, block, MPI_INT, i, 1000, MPI_COMM_WORLD);
//                MPI_Send(y + shift, block, MPI_INT, i, 2000, MPI_COMM_WORLD);
//			}
//        }
//
//        for (int i = 1; i < size; i++) 
//        {
//
//            MPI_Status statusDx;
//            int resultCountDx;
//
//            MPI_Probe(i, 3000, MPI_COMM_WORLD, &statusDx);
//
//            MPI_Get_count(&statusDx, MPI_INT, &resultCountDx);
//
//
//            MPI_Recv(x, resultCountDx, MPI_INT, i, 3000, MPI_COMM_WORLD, &statusDx);
//            printf("\n process=%d results D from process=%d :", rank, i);
//            printf("result X \n");
//            for (int i = 0; i < resultCountDx; i++)
//            {
//                printf("%d ", x[i]);
//            }
//
//            MPI_Status statusDy;
//            int resultCountDy;
//
//            MPI_Probe(i, 3002, MPI_COMM_WORLD, &statusDy);
//
//            MPI_Get_count(&statusDy, MPI_INT, &resultCountDy);
//
//
//            MPI_Recv(y, resultCountDy, MPI_INT, i, 3002, MPI_COMM_WORLD, &statusDy);
//            printf("\n process=%d results D from process=%d :", rank, i);
//            printf("result Y \n");
//            for (int i = 0; i < resultCountDy; i++)
//            {
//                printf("%d ", y[i]);
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
//        int* zd = new int[countOfElemX];
//
//        for (int i = 0; i < countOfElemX; i++) {
//            zd[i] = xBuffer[i];
//            xBuffer[i] = yBuffer[i];
//            yBuffer[i] = zd[i];
//        }
//
//        for (int i = 0; i < countOfElemX; i++) {
//            printf("x = %d ", xBuffer[i]);
//            printf("y = %d ", yBuffer[i]);
//        }
//
//        MPI_Send(xBuffer, countOfElemX, MPI_INT, 0, 3000, MPI_COMM_WORLD);
//        MPI_Send(yBuffer, countOfElemX, MPI_INT, 0, 3002, MPI_COMM_WORLD);
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
//Задание7
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int messSize = 15;
//
//    int* x = new int[messSize];
//    int* answer = new int[messSize];
//    for (int i = 0; i < messSize; i++)
//    {
//        x[i] = rand() % 10 + 1;
//    }
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    double startTime = MPI_Wtime();
//    if (rank == 0) {
//        MPI_Send(x, messSize, MPI_INT, 1, 1000, comm);
//        MPI_Recv(answer, messSize, MPI_INT, 1, 1000, comm, MPI_STATUS_IGNORE);
//        double workTime = MPI_Wtime() - startTime;
//        printf("Process = %d PingPing work time = %f \n", rank,  workTime);
//    }
//    if (rank == 1) {
//        MPI_Send(x, messSize, MPI_INT, 0, 1000, comm);
//        MPI_Recv(answer, messSize, MPI_INT, 0, 1000, comm, MPI_STATUS_IGNORE);
//        double workTime = MPI_Wtime() - startTime;
//        printf("Process = %d PingPing work time = %f \n", rank, workTime);
//    }
//   
//
//    MPI_Finalize();
//
//}

//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int messSize = 10000;
//
//    int* x = new int[messSize];
//    int* answer = new int[messSize];
//    for (int i = 0; i < messSize; i++)
//    {
//        x[i] = rand() % 10 + 1;
//    }
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    double startTime = MPI_Wtime();
//    if (rank == 0) {
//        MPI_Send(x, messSize, MPI_INT, 1, 1000, comm);
//        MPI_Recv(answer, messSize, MPI_INT, 1, 1000, comm, MPI_STATUS_IGNORE);
//        double workTime = MPI_Wtime() - startTime;
//        printf("Process = %d PingPong work time = %f \n", rank, workTime);
//    }
//    if (rank == 1) {
//        int* messBuff = new int[messSize];
//        MPI_Recv(messBuff, messSize, MPI_INT, 0, 1000, comm, MPI_STATUS_IGNORE);
//        MPI_Send(messBuff, messSize, MPI_INT, 0, 1000, comm);
//    }
//
//
//    MPI_Finalize();
//
//}


//Задание8
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int arraySize = 15;
//
//    int block;
//    float* x = NULL;
//    float* y = NULL;
//    float minVal;
//    int minIndex;
//
//    struct {
//        float value;
//        int   index;
//    } in, out;
//
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0) {
//        x = (float*)malloc(arraySize * sizeof(float));
//        printf("Process=%d \nArray :", rank);
//        srand(time(0));
//        for (int i = 0; i < arraySize; i++)
//        {
//            x[i] = rand() % 100 + 1;
//            printf("%.3g ", x[i]);
//        }
//        printf("\n");
//    }
//    
//    block = arraySize / size;
//    y = (float*)malloc(block * sizeof(float));
//
//    MPI_Scatter(x, block, MPI_FLOAT, y, block, MPI_FLOAT, 0, comm);
//
//    in.index = 0;
//    in.value = y[0];
//
//    printf("Process = %d \n", rank);
//    for (int i = 0; i < block; i++) {
//        if (y[i] < in.value) {
//            in.value = y[i]; 
//            in.index = i;
//        }
//        printf("%.3g ", y[i]);
//    }
//    in.index = rank * block + in.index;
//
//    MPI_Reduce(&in, &out, 1, MPI_FLOAT_INT, MPI_MINLOC, 0, comm);
//
//    if (rank == 0) {
//        minVal = out.value;
//        minIndex = out.index;
//        printf("\nProcess = %i Result : min= %.3g , index = %d\n", rank, minVal, minIndex);
//    }
//
//    MPI_Finalize();
//
//}
//Задание9
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int matrixSize = 6;
//
//    int block;
//    int A[matrixSize][matrixSize];
//    int sentBuffer[matrixSize][matrixSize];
//    int norm = 0;
//
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//
//    if (rank == 0) {
//        printf("Process=%d \nArray :\n", rank);
//        srand(time(0));
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                printf("A[%d][%d]=%d ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//        for (int i = 0; i < matrixSize; i++) {
//            for (int j = 0; j < matrixSize; j++) {
//                sentBuffer[i][j] = A[j][i];
//                printf("sent[%d][%d]=%d ", i, j, sentBuffer[i][j]);
//            }
//            printf("\n");
//        }
//    }
//    block = matrixSize / size;
//    int* y = new int[block * matrixSize];
//
//    MPI_Scatter(sentBuffer, block * matrixSize, MPI_INT, y, block * matrixSize, MPI_INT, 0, comm);
//
//    printf("Process = %d \n", rank);
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {
//            printf("%d ", y[i * matrixSize + j]);
//        }
//        printf("\n");
//    }
//
//    int sum = 0;
//
//    for (int i = 0; i < block; i++) {
//        int lineSum = 0;
//        for (int j = 0; j < matrixSize; j++) {
//            lineSum += abs(y[i * matrixSize + j]);
//        }
//        if (lineSum > sum) {
//            sum = lineSum;
//        }
//        printf("sum = %d\n", lineSum);
//    }
//
//
//    MPI_Reduce(&sum, &norm, 1, MPI_INT, MPI_MAX, 0, comm);
//
//    if (rank == 0) {
//        printf("\nProcess = %i Result : norm = %d\n", rank, norm);
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Задание10
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int matrixSize = 4;
//
//    int block;
//    int A[matrixSize][matrixSize];
//    int B[matrixSize][matrixSize];
//    int C[matrixSize][matrixSize];
//      
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0) {
//        srand(time(0));
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                printf("A[%d][%d]=%d ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                B[i][j] = rand() % 5 + 1;
//                printf("B[%d][%d]=%d ", i, j, B[i][j]);
//            }
//            printf("\n");
//        }
//    }
//
//    block = matrixSize / size;
//    int* x = new int[block * matrixSize];
//    int* y = new int[block * matrixSize];
//    int* z = new int[block * matrixSize];
//
//    MPI_Scatter(A, block* matrixSize, MPI_INT, x, block * matrixSize, MPI_INT, 0, comm);
//    MPI_Scatter(B, block* matrixSize, MPI_INT, y, block * matrixSize, MPI_INT, 0, comm);
//
//    printf("Process = %d  A part\n", rank);
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {          
//            printf("%d ", x[i * matrixSize + j]);
//        }
//        printf("\n");
//    }
//    printf("Process = %d  B part\n", rank);
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {
//            printf("%d ", y[i * matrixSize + j]);
//        }
//        printf("\n");
//    }
//
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {
//            z[i * matrixSize + j] = x[i * matrixSize + j] * y[i * matrixSize + j];
//        }
//    }
//    printf("Array z : \n");
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {
//            printf("%d ", z[i * matrixSize + j]);
//        }
//        printf("\n");
//    }
//
//    MPI_Gather(z, block * matrixSize, MPI_INT, C, block * matrixSize, MPI_INT, 0, comm);
//
//    if (rank == 0) {
//        printf("Result : \n");
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {             
//                printf("C[%d][%d]=%d ", i, j, C[i][j]);
//            }
//            printf("\n");
//        }
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Задание11
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int matrixSize = 4;
//    const int vectorSize = 4;
//
//    int block;
//    int A[matrixSize][matrixSize];
//    int x[vectorSize];
//    int z[vectorSize];
//      
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0) {
//        srand(time(0));
//        for (int i = 0; i < matrixSize; i++)
//        {
//            for (int j = 0; j < matrixSize; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                printf("A[%d][%d]=%d ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
//        for (int i = 0; i < vectorSize; i++)
//        {
//            x[i] = rand() % 5 + 1;
//            printf("x[%d]=%d ", i, x[i]);
//        }
//        printf("\n");
//    }
//
//    block = matrixSize / size;
//    int* aBuffer = new int[block * matrixSize];
//
//    MPI_Scatter(A, block* matrixSize, MPI_INT, aBuffer, block * matrixSize, MPI_INT, 0, comm);
//    MPI_Bcast(x, vectorSize, MPI_INT, 0, comm);
//
//    printf("Process = %d  A part\n", rank);
//    for (int i = 0; i < block; i++) {
//        for (int j = 0; j < matrixSize; j++) {          
//            printf("%d ", aBuffer[i * matrixSize + j]);
//        }
//        printf("\n");
//    }
//
//    int* zBuffer = new int[block];
//    for (int i = 0; i < block; i++) {
//        zBuffer[i] = 0;
//        for (int j = 0; j < matrixSize; j++) {
//            zBuffer[i] += aBuffer[i * matrixSize + j] * x[j];
//        }
//    }
//
//    printf("Process = %d zBuffer : \n", rank);
//    for (int i = 0; i < block; i++) {
//        printf("%d ", zBuffer[i]);
//    }
//
//    MPI_Gather(zBuffer, block, MPI_INT, z, block, MPI_INT, 0, comm);
//
//    if (rank == 0) {
//        printf("\nResult : \n");
//        for (int i = 0; i < vectorSize; i++)
//        {          
//            printf("z[%d]=%d ", i, z[i]);
//        }
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Задание12
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int arraySize = 10;
//
//    int block;
//	int* sendBuffer = NULL;
//    int A[arraySize];
//	int Send[arraySize];
//
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	block = arraySize / size;
//
//
//	srand(time(0));
//	for (int i = 0; i < arraySize; i++)
//	{
//		Send[i] = rand() % 5 + 1;
//	}
//
//	sendBuffer = new int[block];
//
//	printf("Process = %d \n", rank);
//	srand(time(0));
//	for (int i = 0; i < block; i++)
//	{
//		sendBuffer[i] = Send[rank * block + i];
//		printf("%d ", sendBuffer[i]);
//	}
//	printf("\n");
//
//    if (rank == 0) {
//		int* receiveBuffer = new int[arraySize];
//		for (int i = 0; i < block; i++) {
//			A[i] = sendBuffer[i];
//		}
//		for (int i = 1; i < size; ++i) {
//			MPI_Recv(receiveBuffer, block, MPI_INT, i, 1000, comm, MPI_STATUS_IGNORE);
//			for (int j = 0; j < block; j++) {
//				A[i * block + j] = receiveBuffer[j];
//			}			
//		}
//
//		printf("Process = %d result A : \n", rank);
//		for (int i = 0; i < arraySize; i++) {
//			printf("%d ", A[i]);
//		}
//		printf("\n");
//	}
//	else {
//		MPI_Send(sendBuffer, block, MPI_INT, 0, 1000, comm);
//	}
//
//    MPI_Finalize();
//    return 0;
//}
//Задание13
//#include <mpi.h>
//#include<stdio.h>
//#include <iostream>
//#include "time.h"
//
//int main(int argc, char** argv) {
//
//    int rank, size;
//    const int n = 6;
//    const int m = 4;
//    int block;
//    int A[n][m];
//
//    MPI_Comm comm = MPI_COMM_WORLD;
//
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//
//    int recvcount = (n / 2) * (m / 2);
//    int* aBuffer = new int[n * m];
//    int* sendcounts = new int[size];
//    int* displs = new int[size];
//    int* resultBuffer = new int[recvcount];
//
//    if (rank == 0) {
//        srand(time(0));
//        for (int i = 0; i < n; i++)
//        {
//            for (int j = 0; j < m; j++)
//            {
//                A[i][j] = rand() % 5 + 1;
//                printf("A[%d][%d]=%d ", i, j, A[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
//
//        int index = 0;
//
//        for (int i = 0; i < n / 2; i++) {
//            for (int j = 0; j < m / 2; j++) {
//                aBuffer[index] = A[i][j];
//                index++;
//            }
//        }
//
//        for (int i = n / 2; i < n; i++) {
//            for (int j = 0; j < m / 2; j++) {
//                aBuffer[index] = A[i][j];
//                index++;
//            }
//        }
//
//        for (int i = 0; i < n / 2; i++) {
//            for (int j = m / 2; j < m; j++) {
//                aBuffer[index] = A[i][j];
//                index++;
//            }
//        }
//
//        for (int i = n / 2; i < n; i++) {
//            for (int j = m / 2; j < m; j++) {
//                aBuffer[index] = A[i][j];
//                index++;
//            }
//        }
//
//        for (int i = 0; i < size; i++) {
//            sendcounts[i] = (n / 2) * (m / 2);
//            displs[i] = i * m / 2 * n / 2;
//        }
//    }
//
//    MPI_Scatterv(aBuffer, sendcounts, displs, MPI_INT, resultBuffer, recvcount, MPI_INT, 0, comm);
//
//    int B[n/2][m/2];
//    int indexB = 0;
//    for (int i = 0; i < n / 2; i++) {
//        for (int j = 0; j < m / 2; j++) {
//            B[i][j] = resultBuffer[indexB];
//            indexB++;
//        }
//    }
//
//    printf("Process = %d  A part\n", rank);
//    for (int i = 0; i < n / 2; i++) {
//        for (int j = 0; j < m / 2; j++) {
//            printf("%d ", B[i][j]);
//        }
//        printf("\n");
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Задание14
//#include <stdio.h>
//#include <stdlib.h>
//#include <mpi.h>
//#include "time.h"
//
//int main(int argc, char** argv)
//{
//	int x, sum = 0;
//	double beginTime, endTime, workTime, result1, result2;
//	int size, rank;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//	srand(time(0));
//	x = rand() % 5 + 1;
//
//	beginTime = MPI_Wtime();
//
//	MPI_Reduce(&x, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//	MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);
//
//	endTime = MPI_Wtime();
//
//	workTime = endTime - beginTime;
//	MPI_Reduce(&workTime, &result1, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
//
//	if (rank == 0)
//	{
//		printf("MPI_Reduce with MPI_Bcast time = %f\n", result1);
//	}
//
//	sum = 0;
//
//	beginTime = MPI_Wtime();
//
//	MPI_Allreduce(&x, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
//
//	endTime = MPI_Wtime();
//	workTime = endTime - beginTime;
//	MPI_Reduce(&workTime, &result2, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
//
//	if (rank == 0)
//	{
//		printf("MPI_Allreduce time = %f\n", result2);
//	}
//
//	MPI_Finalize();
//}

//Задание15

//#include <stdio.h>
//#include <stdlib.h>
//#include <mpi.h>
//#include "time.h"
//#include <iostream>
//
//
//int main(int argc, char** argv)
//{
//	int rank, size;
//
//	int b[4][8];
//	int c[4][8];
//	int a[8][8];
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	MPI_Datatype myType;
//	MPI_Type_vector(4, 8, 16, MPI_INT, &myType);
//	MPI_Type_commit(&myType);
//
//	if (rank == 0) {
//		srand(time(0));
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				a[i][j] = rand() % 10 + 1;
//			}
//		}
//		printf("Process = %d", rank);
//		printf("Array a : \n");
//
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				printf("%d ", a[i][j]);
//			}
//			printf("\n");
//		}
//
//		for (int i = 0; i < size-1; i++) {
//			MPI_Send(&a[i][0], 1, myType, i + 1, 1000, MPI_COMM_WORLD);
//		}
//
//	}
//
//	if (rank == 1) {
//	
//		MPI_Status statusOdd;
//		int sizeOdd;
//	
//		MPI_Probe(0, 1000, MPI_COMM_WORLD, &statusOdd);
//		MPI_Get_count(&statusOdd, MPI_INT, &sizeOdd);
//	
//		int* arrayOdd = new int[sizeOdd];
//		MPI_Recv(arrayOdd, sizeOdd, MPI_INT, 0, 1000, MPI_COMM_WORLD, &statusOdd);
//	
//		int index = 0;
//		for (int i = 0; i < 8 / 2; i++) {
//			for (int j = 0; j < 8; j++) {
//				b[i][j] = arrayOdd[index];
//				index++;
//			}
//		}
//	
//		for (int i = 0; i < 4; i++) {
//			printf("Process = %d array b : ", rank);
//			for (int j = 0; j < 8; j++) {
//				printf("%d ", b[i][j]);
//			}
//			printf("\n");
//	
//		}
//
//	}
//	
//	
//	if (rank == 2) {
//		MPI_Status statusEven;
//		int sizeEven;
//	
//		MPI_Probe(0, 1000, MPI_COMM_WORLD, &statusEven);
//		MPI_Get_count(&statusEven, MPI_INT, &sizeEven);
//	
//		int* arrayEven = new int[sizeEven];
//
//		MPI_Recv(arrayEven, sizeEven, MPI_INT, 0, 1000, MPI_COMM_WORLD, &statusEven);
//	
//		int index = 0;
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 8; j++) {
//				c[i][j] = arrayEven[index];
//				index++;
//			}
//		}
//	
//		for (int i = 0; i < 4; i++) {
//			printf("Process = %d array c : ", rank);
//			for (int j = 0; j < 8; j++) {
//				printf("%d ", c[i][j]);
//			}
//			printf("\n");
//		}
//	}
//
//	MPI_Finalize();
//	return 0;
//}

//Задание16

//using namespace std;
//
//#include <stdlib.h>
//#include <iostream>
//#include <cmath>
//#include "mpi.h">
//#include <stdio.h>
//#include <stddef.h>
//#include <math.h>
//
//
//struct MyType {
//	int line1[8];
//	int line2[8];
//};
//
//int main(int argc, char** argv)
//{
//	int rank, size;
//	int a[8][8];
//	int blockslegth[2] = {8 , 8};
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	struct MyType my;
//	
//	
//	
//	MPI_Datatype newtype;
//
//
//
//	MPI_Datatype types[2] = { MPI_INT, MPI_INT };
//	MPI_Aint address[2];
//
//	address[0] = offsetof(struct MyType, line1);
//	address[1] = offsetof(struct MyType, line2);
//
//	MPI_Type_create_struct(2, blockslegth, address, types, &newtype);
//	MPI_Type_commit(&newtype);
//
//
//	if (rank == 4) {
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				a[i][j] = rand() % 100;
//			}
//		}
//
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				cout << a[i][j] << " ";
//			}
//			cout << endl;
//		}
//
//		cout << endl;
//
//		for (int i = 0; i < size - 1; i++) {
//			for (int j = 0; j < 8; j++) {
//				my.line1[j] = a[i + 4][j];
//				my.line2[j] = a[i][j];
//				
//
//			}
//			MPI_Send(&my, 1, newtype, i, 33, MPI_COMM_WORLD);
//		}		
//
//	}
//
//	if (rank == 0) {
//		MPI_Status status;
//		MPI_Recv(&my, 1, newtype, 4, 33, MPI_COMM_WORLD, &status);
//
//		int d[2][8];
//
//		for (int j = 0; j < 8; j++) {
//			d[0][j] = my.line1[j];
//			d[1][j] = my.line2[j];
//		}
//		cout << endl;
//
//
//		cout << "matrix on process : " << rank << endl;
//
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 8; j++) {
//				cout << d[i][j] << " ";
//			}
//			cout << endl;
//		}
//	}
//
//	if (rank == 1) {
//		MPI_Status status1;
//		MPI_Recv(&my, 1, newtype, 4, 33, MPI_COMM_WORLD, &status1);
//		int d[2][8];
//		
//			for (int j = 0; j < 8; j++) {
//				d[0][j] = my.line1[j]  ;
//				d[1][j] = my.line2[j];
//			}
//			cout << endl;
//
//
//			cout << "matrix on process : " << rank << endl;
//
//			for (int i = 0; i < 2; i++) {
//				for (int j = 0; j < 8; j++) {
//					cout << d[i][j] << " ";
//				}
//				cout << endl;
//			}
//	}
//
//	if (rank == 2) {
//		MPI_Status status2;
//		MPI_Recv(&my, 1, newtype, 4, 33, MPI_COMM_WORLD, &status2);
//
//		int d[2][8];
//
//		for (int j = 0; j < 8; j++) {
//			d[0][j] = my.line1[j];
//			d[1][j] = my.line2[j];
//		}
//		cout << endl;
//
//
//		cout << "matrix on process : " << rank << endl;
//
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 8; j++) {
//				cout << d[i][j] << " ";
//			}
//			cout << endl;
//		}
//	}
//
//	if (rank == 3) {
//		MPI_Status status3;
//		MPI_Recv(&my, 1, newtype, 4, 33, MPI_COMM_WORLD, &status3);
//
//		int d[2][8];
//
//		for (int j = 0; j < 8; j++) {
//			d[0][j] = my.line1[j];
//			d[1][j] = my.line2[j];
//		}
//		cout << endl;
//
//
//		cout << "matrix on process : " << rank << endl;
//
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 8; j++) {
//				cout << d[i][j] << " ";
//			}
//			cout << endl;
//		}
//	}
//
//	MPI_Type_free(&newtype);
//	MPI_Finalize();
//	return 0;
//
//}

//Задание17

//#include <iostream>
//#include <mpi.h>
//#include <stdio.h>
//#include <math.h>
//
//using namespace std;
//
//void printArray(int n, int m, int a[8][8])
//{
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            cout << a[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//int main(int argc, char** argv) {
//
//    int rank;
//    int size;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    const int m = 8;
//    const int n = 8;
//
//    int a[n][m];
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            a[i][j] = 0;
//        }
//    }
//
//    MPI_Datatype newType;
//    int blocksLength[n] = { 8,7,6,5,4,3,2,1 };
//    int indices[n] = { 0,9,18,27,36,45,54,63 };
//    MPI_Type_indexed(n, blocksLength, indices, MPI_INT, &newType);
//    MPI_Type_commit(&newType);
//
//    if (rank == 0) {
//        int counter = 1;
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                a[i][j] = counter;
//                counter++;
//            }
//        }
//    }
//
//    MPI_Bcast(&a, 1, newType, 0, MPI_COMM_WORLD);
//
//    if (rank == 1) {
//        cout << "Rectangle matrix : " << endl;
//        printArray(n, m, a);
//    }
//
//    MPI_Finalize();
//    return 0;
//}

//Задание18

//#include <iostream>
//#include <mpi.h>
//#include <stdio.h>
//#include <math.h>
//#include "time.h"
//
//using namespace std;
//
//struct MyType
//{
//    int d[10];
//    double f[8];
//};
//
//int main(int argc, char** argv) {
//
//    int rank;
//    int size;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    struct MyType my;
//    int blocksLengths[2] = { 10, 8 };
//
//    MPI_Datatype types[2] = { MPI_INT, MPI_DOUBLE };
//    MPI_Aint address[2];
//
//    address[0] = offsetof(struct MyType, d);
//    address[1] = offsetof(struct MyType, f);
//
//    MPI_Datatype newType;
//
//    MPI_Type_create_struct(2, blocksLengths, address, types, &newType);
//    MPI_Type_commit(&newType);
//
//    if (rank == 0) {
//        cout << "Procces = 0, Array : " << endl;
//        srand(time(0));
//		for (int i = 0; i < 10; i++) {
//            my.d[i] = rand() % 10 + 1;
//            cout << my.d[i] << " ";
//		}
//        srand(time(0));
//        for (int i = 0; i < 8; i++) {
//            my.f[i] = (double)rand();
//            cout << my.f[i] << " ";
//        }
//        cout << endl;
//        for (int i = 1; i < size; i++)
//            MPI_Send(&my, 1, newType, i, 1, MPI_COMM_WORLD);
//    }
//    else {
//        MPI_Status status;
//
//        MPI_Recv(&my, 1, newType, 0, 1, MPI_COMM_WORLD, &status);
//
//        printf("Process = %d \n", rank);
//        for (int j = 0; j < 10; j++) {
//            cout << my.d[j] << " ";
//            
//        }
//        cout << endl;
//        printf("Process = %d \n", rank);
//        for (int j = 0; j < 8; j++) {
//            cout << my.f[j] << " ";
//        }
//        cout << endl;
//    }
//    
//    MPI_Finalize();
//    return 0;
//}

//Задание19

//#include <iostream>
//#include <cmath>
//#include "mpi.h"
//#include <stdio.h>
//#include <cstdlib>
//
//using namespace std;
//
//#define N 10
//
//int main( int argc, char **argv) {
//    MPI_Init(&argc, &argv);
//    
//    int rank, size;
//    MPI_Status status;
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    
//
//    int newGroup[5] = { 8, 3, 9, 1, 6 };
//
//    MPI_Group group, newgroup;
//    MPI_Comm_group(MPI_COMM_WORLD, &group);
//    MPI_Group_incl(group, 5, newGroup, &newgroup);
//
//    MPI_Comm comm, local;
//    MPI_Comm_create(MPI_COMM_WORLD, newgroup, &comm);
//
//    int newrank=-1;
//
//    int a[N];
//
//    if (comm != MPI_COMM_NULL)  {
//        MPI_Comm_rank(comm, &newrank);
//    }
//
//    if (newrank==0 && comm != MPI_COMM_NULL) {
//        for (int i = 0; i < N; i++) {
//            a[i] = rand() % 100;
//        }
//        printf("Process = %d Create array: \n", rank);
//        for (int i = 0; i < N; i++) {
//            cout << a[i] << " ";
//        }
//        cout << "\n";
//        MPI_Bcast(&a, N, MPI_INT, 0, comm);
//    }
//
//    if (newrank != -1 && comm != MPI_COMM_NULL) {
//      MPI_Bcast(&a, N, MPI_INT, 0, comm);
//      printf("Process = %d :\n", rank);
//      
//      for (int i = 0; i < N; i++) {
//          cout << a[i] << " ";
//      }
//      cout << "\n";
//      if (newrank == 4) {
//          MPI_Send(a, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
//      }
//    }
//
//    if (rank == 0 ) {
//      MPI_Recv(a, N, MPI_INT, 6, 0, MPI_COMM_WORLD, &status);
//      printf("\nProcess = %d : ", rank);
//
//      for (int i = 0; i < N; i++) {
//          cout << a[i] << " ";
//      }
//
//      cout << "\n";
//    }
//
//    if (comm != MPI_COMM_NULL) {
//      MPI_Comm_free(&comm);
//    }
//
//    MPI_Group_free(&newgroup);
//    MPI_Finalize();
//    return 0;
//}

//Задание20
//#include "mpi.h"
//#include <iostream>
//#include <cstdlib>
//
//int main(int argc, char** argv)
//{
//	MPI_Init(&argc, &argv);
//
//	int size, rank;
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	MPI_Comm comm;
//
//	int groupNum = rank / 3;
//	MPI_Comm_split(MPI_COMM_WORLD, groupNum, rank % 3, &comm);
//
//	int newrank = -1;
//	if (comm != MPI_COMM_NULL) {
//		MPI_Comm_rank(comm, &newrank);
//	}
//	int comm_size = -1;
//	if (comm != MPI_COMM_NULL) {
//		MPI_Comm_size(comm, &comm_size);
//	}
//
//	int groups[4] = { groupNum, groupNum , groupNum , groupNum };
//
//	int arr[12];
//	MPI_Gather(&groups, 4, MPI_INT, &arr, 4, MPI_INT, 0, comm);
//
//	if (newrank == 0) {
//		printf("Group = %d ", groupNum);
//		for (int i = 0; i < 12; ++i) {
//			printf("%d ", arr[i]);
//		}
//		printf("\n ");
//	}
//
//	int messTag = -1;
//	int firstProc = -1;
//
//	if (groupNum == 0) {
//		messTag = 12;
//		firstProc = 3;
//	} else if (groupNum == 1) {
//		messTag = 12;
//		firstProc = 0;
//	} else if (groupNum == 2) {
//		messTag = 34;
//		firstProc = 9;
//	} else if (groupNum == 3) {
//		messTag = 34;
//		firstProc = 6;
//	}
//
//	MPI_Comm intercomm;
//	MPI_Intercomm_create(comm, 0, MPI_COMM_WORLD, firstProc, messTag, &intercomm);
//
//	if ((groupNum == 0 || groupNum == 2) && newrank == 0) {
//		MPI_Send(&arr, 12, MPI_INT, 0, groupNum, intercomm);
//	}
//
//	if ((groupNum == 1 || groupNum == 3) && newrank == 0) {
//		int buf[12];
//		MPI_Recv(&buf, 12, MPI_INT, MPI_ANY_SOURCE, groupNum - 1, intercomm, MPI_STATUS_IGNORE);
//
//		printf("\n");
//		printf("Group = %d Intercom : ", groupNum);
//		for (int i = 0; i < 12; ++i) {
//			printf("%d ", buf[i]);
//		}
//		printf("\n ");
//	}
//
//	if (comm != MPI_COMM_NULL) MPI_Comm_free(&comm);
//
//	MPI_Finalize();
//	return 0;
//}

//Задание21
//#include <mpi.h>
//#include <iostream>
//#include <ctime>
//
//int main(int argc, char** argv) {
//
//	MPI_Init(&argc, &argv);
//	int rank, size;
//	int arraySize = 10;
//	int* x = new int[arraySize];
//	float result[2];
//	float localSum;
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	int block = ceil((double)arraySize / size);
//
//	if (rank == 0) {
//		srand(time(0));
//		for (int i = 0; i < arraySize; i++) {
//			x[i] = rand() % 10 - 3;
//			printf(" %d ", x[i]);
//		}
//		printf("\n");
//	}
//	int* displs = new int[size];
//	int* sendcounts = new int[size];
//
//	for (int i = 0; i < size; ++i) {
//		displs[i] = i * block;
//		sendcounts[i] = block;
//	}
//	sendcounts[size-1] = arraySize - (size - 1) * block;
//	int blockSize = sendcounts[rank];
//	int* y = new int[blockSize];
//	MPI_Scatterv(x, sendcounts, displs, MPI_INT, y , blockSize, MPI_INT, 0, MPI_COMM_WORLD);
//	localSum = 0;
//	int localCount = 0;
//	for (int i = 0; i < blockSize; i++) {
//		if (x[i] > 0) {
//			localSum += x[i];
//			localCount++;
//		}
//	}
//
//	int arr[2];
//	arr[0] = localSum;
//	arr[1] = localCount;
//	MPI_Reduce(&arr, &result, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//	if (rank == 0)
//		printf("\n average = %f \n", result[0] / result[1]);
//
//	MPI_Finalize();
//	return 0;
//}

//Задание22
//#include <mpi.h>
//#include <stdio.h>
//#include <random>
//#include <ctime>
//
//int calculateSum(int* array, int arraySize) {
//	int pairs = ceil((double)arraySize / 2);
//	int* localSums = new int[pairs];
//	for (int i = 0; i < arraySize; i += 2) {
//		int pairNumber = (int)floor((double)i / 2);
//		if (i + 1 >= arraySize) {
//			localSums[pairNumber] = array[i];
//		}
//		else {
//			localSums[pairNumber] = array[i] + array[i + 1];
//		}
//	}
//	if (pairs == 1) {
//		return localSums[0];
//	} else {
//		return calculateSum(localSums, pairs);
//	}
//}
//
//int main(int argc, char** argv) {
//	int size, rank;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	int n = 9;
//	int* arr = new int[n];
//	srand(time(0));
//	for (int i = 0; i < n; i++) {
//		arr[i] = rand() % 5 + 1;
//		if (rank == 0) {
//			printf("%d ", arr[i]);
//		}
//	}
//	int sum = 0;
//	int sumBlock = 0;
//	int* localSums = new int[size];
//	int blockSize = floor((double)n / size);
//	int* sendcounts = new int[size];
//	int* displs = new int[size];
//	for (int i = 0; i < size; i++) {
//		sendcounts[i] = blockSize;
//		displs[i] = i * blockSize;
//	}
//	sendcounts[size - 1] = n - blockSize * (size - 1);
//
//	int blockLength = sendcounts[rank];
//	int* block = new int[blockLength];
//	MPI_Scatterv(arr, sendcounts, displs, MPI_INT, block, blockLength, MPI_INT, 0, MPI_COMM_WORLD);
//	sumBlock = calculateSum(block, blockLength);
//	MPI_Gather(&sumBlock, 1, MPI_INT, localSums, 1, MPI_INT, 0, MPI_COMM_WORLD);
//	if (rank == 0) {
//		sum = calculateSum(localSums, size);
//		printf("\nProcess = %d result sum = %d", rank, sum);
//	}
//	MPI_Finalize();
//	return 0;
//}

//Задание23
//#include <mpi.h>
//#include <stdio.h>
//#include <ctime>
//#include <random>
//
//struct dot {
//    double x;
//    double y;
//};
//
//int main(int argc, char** argv) {
//    int n = 100000;
//    int size, rank;
//    int localCount = 0;
//    int count = 0;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    struct dot* dots = new dot[n];
//    srand(time(0));
//    for (int i = 0; i < n; i++) {
//        struct dot dot;
//        dot.x = (double)(rand()) / RAND_MAX * 2 - 1;
//        dot.y = (double)(rand()) / RAND_MAX * 2 - 1;
//        dots[i] = dot;
//    }
//    int blockSize = floor((double)n / size);
//    int* sendcounts = new int[size];
//    int* displs = new int[size];
//    for (int i = 0; i < size; i++) {
//        sendcounts[i] = blockSize;
//        displs[i] = i * blockSize;
//    }
//    sendcounts[size - 1] = n - blockSize * (size - 1);
//
//    int blockLength = sendcounts[rank];
//    struct dot* block = new dot[blockLength];
//    int lengths[2] = { 1, 1 };
//    MPI_Aint offsets[2] = { 0, sizeof(double) };
//    MPI_Datatype types[2] = { MPI_DOUBLE, MPI_DOUBLE };
//    MPI_Datatype dotType;
//    MPI_Type_create_struct(2, lengths, offsets, types, &dotType);
//    MPI_Type_commit(&dotType);
//    MPI_Scatterv(dots, sendcounts, displs, dotType, block, blockLength, dotType, 0, MPI_COMM_WORLD);
//    for (int i = 0; i < blockLength; i++) {
//        struct dot dot = block[i];
//        if (dot.x * dot.x + dot.y * dot.y < 1) {
//            localCount++;
//        }
//    }
//    MPI_Reduce(&localCount, &count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
//
//    if (rank == 0) {
//        double pi = (double)count / n * 4;
//        printf("Process = %d, Result = %f", rank, pi);
//    }
//
//    MPI_Finalize();
//    return 0;
//}