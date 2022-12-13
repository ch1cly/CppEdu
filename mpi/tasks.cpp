#include "tasks.h"



void test12(int* argc, char*** argv)
{
    int num, r;
    MPI_Init(argc, argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &r);
    MPI_Comm_size(MPI_COMM_WORLD, &num);
    printf("ranks:%d, andf nums %d\n", r, num);

    MPI_Finalize();
}



void task4(int* argc, char*** argv) {
    //объявление переменных
    constexpr int SIZE = 10;
    srand(time(0));
    int ProcNum;
    int ProcRank;
    //инициализация процессов
    MPI_Init(argc, argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);


    
    if (ProcRank == 0)
    {
        //область рабочего процесса
        int x[SIZE];
        int y[SIZE];
        int z[SIZE];
        //генерация значений
        for (int i = 0; i < SIZE; ++i) {
            x[i] = rand() % ((int)SIZE * 3) + 1;
            y[i] = rand() % ((int)SIZE * 3) + 1;
        }
        //вычисление обычной передачи
        const int partitionG = int(round(double(SIZE) / (ProcNum - 1)));
        //вычисление последней передачи
        int partitionL = SIZE - (ProcNum - 2) * partitionG;
        for (int i = 1; i < ProcNum; ++i) {
            int partition = partitionG;   
            if (i == ProcNum - 1) {
                //если последняя, то могут быть измененеия
                partition = partitionL;
            }
            const int offset = (i-1) * partitionG;
            //отправка значений
            MPI_Send((y + offset), partition, MPI_INT, i, 0, (MPI_Comm)MPI_COMM_WORLD);
            MPI_Send((x + offset), partition, MPI_INT, i, 1, (MPI_Comm)MPI_COMM_WORLD);
        }
        for (int i = 1; i < ProcNum; ++i) {
            int partition = partitionG;
            if (i == ProcNum - 1) {
                partition = partitionL;
            }
            const int offset = (i - 1) * partitionG;
            //принятие решений
            MPI_Recv((z + offset), partition, MPI_INT, i, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        }
        for (size_t i = 0; i < SIZE; i++) 
            printf("%d = %d and %d\n",z[i], x[i], y[i]);
    }

    if (ProcRank != 0) {
        //тут остальные процессы совершают вычисления
        MPI_Status status;
        int count=1;
        int partitionG = int(round(double(SIZE) / (ProcNum - 1)));
        int partitionL = SIZE - (ProcNum - 1) * partitionG;
        //проверка сообщения и получение количества элементов
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, (MPI_Comm)MPI_COMM_WORLD, &status);//проверка структуры входящего сообщения
        MPI_Get_count(&status, MPI_INT, &count);
        //создание переменных для приема 
        int* bx = new int[count];
        int* by = new int[count];
        //прием
        MPI_Recv(bx, count, MPI_INT, status.MPI_SOURCE, 0, (MPI_Comm)MPI_COMM_WORLD, &status);
        MPI_Recv(by, count, MPI_INT, status.MPI_SOURCE, 1, (MPI_Comm)MPI_COMM_WORLD, &status);

        //обработка
        for (int i = 0; i < count; ++i)
            bx[i] = bx[i] * by[i];
            //bx[i] = bx[i] + by[i];
        //отсылка обратно
        MPI_Send(bx, count, MPI_INT, 0, 0, (MPI_Comm)MPI_COMM_WORLD);
        //высвобождения места
        delete bx;
        delete by;

    }
    MPI_Finalize();
}

void task5(int* argc, char*** argv) {
   /*
   * объявление рабочих переменных и инициализация потоков
   */
    const int N = 3;
    const int M = 6;
    int cst = 2;//обозначение состояния
    int counter = 0;
    int ProcRank, ProcNum;
    srand(time(0));
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

    if (ProcRank == 0) {
   /*
   * зона для главного (нулевого) процесса
   * идет генерация матрицы и вектора для ответа
   */
        int** matrix;
        matrix = new int* [N];
        for (size_t i = 0; i < N; ++i) {
            matrix[i] = new int[M];
        }
        int *diagel = new int[std::min(N,M)];

        for (int i = 0; i < N; ++i) 
            for (size_t j = 0; j < M; j++) 
                matrix[i][j] = rand() % 100 + 0;
            
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) 
                printf("%d\t", matrix[i][j]);
            printf("\n");
        }
        /*
            На каждый процесс отправляется одна строка
        */
        for (int i = 0; i < N && cst != 3; i += ProcNum - 1) {
            for (int locNum = 1; locNum < ProcNum; locNum++) {
                //получаем номер строки
                int glId = i + locNum - 1;
                if (glId >= N) break;
                int cc = 2;
                //отправка состояния. Если 2, то работа продолжается
                MPI_Send(&cc, 1, MPI_INT, locNum, 1, MPI_COMM_WORLD);
                //отправка индекса строки и самой строки
                MPI_Send(&glId, 1, MPI_INT, locNum, 0, MPI_COMM_WORLD);
                MPI_Send(matrix[glId], M, MPI_INT, locNum, 0, MPI_COMM_WORLD);
                
            }
            for (int locNum = 1; locNum < ProcNum; locNum++){ 
                
                int glID = i + locNum - 1;
                if (glID >= N) {
                    break;
                }
                //получение обратно ответа
                MPI_Recv(&cst, 1, MPI_INT, locNum, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                if (cst == 3) {
                    break;
                }
                //получение значения, если оно есть)
                MPI_Recv(diagel+ (i * (ProcNum - 1) + locNum - 1), 1, MPI_INT, locNum, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        //остановка процесса во всех потоках
        int cc = 0;
        for (int id = 1; id < ProcNum; id++)
            MPI_Send(&cc, 1, MPI_INT, id, 1, MPI_COMM_WORLD);
        //вывод ответа
        for (int i = 0; i < std::min(M,N); i++)
            printf("%d ", diagel[i]);
        printf("\n");

        delete diagel;
    }
    else {
        //блок рабочих процессов
        //объявдение переменных
        int pcc,occ, rows[M],rowInd;
        while (true) {
            //прием текущего состояния
            MPI_Recv(&pcc, M, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (pcc == 0) {
                break;
            }
            //прием номера и самой строки
            MPI_Recv(&rowInd, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(rows, M, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //отправка ответа
            if (rowInd >= M) {
                occ = 3;//остановка
                MPI_Send(&occ, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            }
            else {
                occ = 1;
                MPI_Send(&occ, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
                MPI_Send(rows+rowInd, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }
    }
    MPI_Finalize();
}


void task8(int* argc, char*** argv) {
    constexpr int N = 10;

    int procId;
    int procsNum;

    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procId);
    MPI_Comm_size(MPI_COMM_WORLD, &procsNum);

    int elTemp = N / procsNum + 1;
    int Nplus = elTemp * procsNum;
    printf("Nplus = %d While N is %d\n", Nplus, N);
    int* a = new int[Nplus];
    int* b = new int[Nplus];
    int resTemp = 0;
    int res = 0;
    int* abuf = new int[elTemp];
    int* bbuf = new int[elTemp];


    // init arrays A, B
    if (procId == 0) {
        printf("\nprocessor %d  Initialising arrays\n", procId);
        srand((unsigned)time(0) + 1);
        for (int i = 0; i < Nplus; i++) {
            if (i < N)
                a[i] = rand() % 10 + 0;
            else
                a[i] = 0;
        }
        for (int i = 0; i < Nplus; i++) {
            if (i < N)
                b[i] = rand() % 10 + 0;
            else
                b[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            printf("%d ", a[i]);
        }
        printf("\n"); 
        for (int i = 0; i < N; i++) {
            printf("%d ", b[i]);
        }
        printf("\n");
    }

    MPI_Scatter(
        a, elTemp, MPI_INT,
        abuf, elTemp, MPI_INT,
        0, MPI_COMM_WORLD);
    MPI_Scatter(
        b, elTemp, MPI_INT,
        bbuf, elTemp, MPI_INT,
        0, MPI_COMM_WORLD);

    for (int i = 0; i < elTemp; i++) {
        resTemp += abuf[i] * bbuf[i];
    }
    printf("\nprocessor %d  scalar multiplication of buffer\n", procId);
    for (int i = 0; i < elTemp; i++) {
        printf("%d ", abuf[i]);
    }
    printf("\n");
    for (int i = 0; i < elTemp; i++) {
        printf("%d ", bbuf[i]);
    }
    printf("\n");
    printf("mid result on proc %d is %d\n",procId, resTemp);

    MPI_Reduce(&resTemp, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (procId == 0) {
        printf("\nprocessor %d scalar multiplication\n", procId);
        printf("Final result on proc %d is %d\n", procId, res);
    }

    delete[] a;
    delete[] b;
    delete[] abuf;
    delete[] bbuf;

    MPI_Finalize();
}


void task7(int* argc, char*** argv){
    int procId;
    int procsNum;
    constexpr int N = 10;
    MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &procId);
    MPI_Comm_size(MPI_COMM_WORLD, &procsNum);

    int elTemp = N / procsNum + 1;
    int Nplus = elTemp * procsNum;
    int resTemp = 0, res = 0;
    int* a = new int[Nplus];
    int* buf = new int[elTemp];

    // init array 
    if (procId == 0) {
        printf("\nInitialising array on proc %d\n", procId);
        srand((unsigned)time(0) + 1);
        for (int i = 0; i < Nplus; i++) {
            if (i < N)
                a[i] = rand() % 10 + 0;
            else
                a[i] = 0;
        }
        for (int i = 0; i < Nplus; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    // send array to all procs
    MPI_Scatter(
        a, elTemp, MPI_INT,
        buf, elTemp, MPI_INT,
        0, MPI_COMM_WORLD);

    // calc chunk results
    for (int i = 0; i < elTemp; i++) {
        resTemp += abs(buf[i]);
    }

    printf("\nl1 norm of chunk % d \n", procId);
    printf("Array is\n");
    for (int i = 0; i < elTemp; i++) {
        printf("%d ", buf[i]);
    }
    printf("\n");
    printf("mid result is %d\n", resTemp);

    // sum of chunk results
    MPI_Reduce(&resTemp, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // show result
    if (procId == 0) {
        printf("\nl1 norm of chunk %d \n",procId);
        printf("Final result is %d\n", res);
    }

    delete[] buf;
    delete[] a;

    MPI_Finalize();
}