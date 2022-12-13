#include "newmpi.h"

void nzad1(int argc, char* argv[]) {
    MPI_Status status;
    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 0) printf("number of processes: %d\n...", ProcNum);
    printf("From process %i: Hello, World!\n", ProcRank);

    MPI_Finalize();
}




void nzad2(int argc, char* argv[]) {
    const int mSize = 10;
    const int genProc = 0;
    const int any = 0;
    int a[mSize];
    int ProcNum;
    int ProcRank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == genProc) {
        for (int i = 0; i < mSize; ++i)
            a[i] = rand() % ((int)mSize * 3) + 1;

        MPI_Send(&a, mSize, MPI_INT, 1, any, MPI_COMM_WORLD);
    }
    
    if (ProcRank == 1) {
        //меньше или больше msize
        MPI_Recv(&a, mSize, MPI_INT, MPI_ANY_SOURCE, any, MPI_COMM_WORLD, &status);
        for (int i = 0; i < mSize; i++)
            printf("%d ", a[i]);
  
        printf("\n");
    }

    MPI_Finalize();
}






void nzad3(int argc, char* argv[]) {
    const int mSize = 10;
    const int any = 0;


    int ProcNum;
    int ProcRank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    if (ProcRank == 1) {
        int a[mSize];
        for (int i = 0; i < mSize; ++i)
            a[i] = rand() % ((int)mSize * 3) + 1;
        for (int i = 0; i < ProcNum; i++) {
            if (i != 1) {
                MPI_Send(&a, mSize, MPI_INT, i, mSize, MPI_COMM_WORLD);
            }
        }
    }

    if (ProcRank != 1) {
        MPI_Status status;
        int count;
        MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        MPI_Get_count(&status, MPI_INT, &count);
        int *qwe = new int[count];

        MPI_Recv(qwe, count, MPI_INT, MPI_ANY_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status);

        printf("proc #%d\n", ProcRank);
        for (int i = 0; i < count; i++)
            printf("%d ",qwe[i]);
        
        printf("\n");
        delete qwe;
    }

    MPI_Finalize();
}



void nzad9(int argc, char* argv[]) {
    constexpr int SIZE = 24;
    /*объявление структуры типа элемент-индекс, но я не очень понял логики, почему редьюс работает
    лишь со связкой*/
    struct di {
        double e;
        int i;
    };
    /*инициализация потоков, получение информации о системе*/
    int ProcNum;
    int ProcRank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    //Попытка поделить нацело все данные, если не удается, то программа не исполниться
    int locSIZE = SIZE / ProcNum;
    //при 24 требуется 12 8 4 2 или 1 нить
    if (double(locSIZE) != double(SIZE) / ProcNum) {
        MPI_Finalize();
        return;
    }
    //создание переменных
    di* locArr = new di[SIZE / ProcNum];
    di  ansv;
    di* arr = nullptr;
    di min = { -9999,-9999 };
    srand(time(0));
    if (ProcRank == 0) {
        // инициализация переменных в 0 потоке
        arr = new di[SIZE];
        double lower_bound = -1000;
        double upper_bound = 1000;
        std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
        std::default_random_engine re;
        for (auto i = 0; i < SIZE; i++){
            arr[i].e = unif(re);
            arr[i].i = i;
            printf("%d\t", arr[i].e);
        }
    }
    //раздача части массива остальным потокам
    MPI_Scatter(arr, locSIZE, MPI_DOUBLE_INT, locArr, locSIZE, MPI_DOUBLE_INT, 0, MPI_COMM_WORLD);
    //нахождение всеми нитями локального минимума.
    ansv = locArr[0];
    for (int i = 1; i < locSIZE; ++i) {
        if (locArr[i].e < ansv.e) {
            ansv= locArr[i];
        }
    }
    //локальный ответ
    printf("LocMin %d)\t el%d\t = %f\n", ProcRank,ansv.i, ansv.e);
    
    //поиск глобальгного минимума по локальным с помощью указаний mpi_minloc. Записывается на 0 нить
    MPI_Reduce(&ansv, &min, ProcNum, MPI_DOUBLE_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
    
    if (ProcRank == 0) {
        //вывод ответа
        printf("Min el %d) %f\n", min.i, min.e);
        delete[] arr;
    }
    
    //окончания области исполения mpi
    delete[]locArr;
    MPI_Finalize();
    return; 
}





int nzad10(int argc, char* argv[]) {
    //объявление служебных переменных
    constexpr int N = 10, M = 5;
    int ProcNum;
    int ProcRank;
    srand(time(0));
    //инициализация mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    
    //для распределение сколько строк, столько и процессов необходимо
    //вот такое распределение поровну
    if (ProcNum != N) {
        MPI_Finalize();
        return 1;
    }
    //создание переменных
    int* A=nullptr;
    int row[M], x[N], b[N];
    
    if (ProcRank == 0) {
        //создание переменных  
        A = new int[N * M];
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; j++) {
                A[i * M + j] = rand() % 10;
            }
        }
        for (auto i = 0; i < N; i++) {
            x[i] = rand() % 10;
        }

        printf("Matrix A:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                printf("%d\t", A[i * M + j]);
            }
            printf("\n");
        }

        printf("Column vector x:\n");
        for (auto i = 0; i < N; i++) {
            printf("%d ", x[i]);
        }
        printf("\n");
    }
    /*
    Первые три параметра соответственно обозначают адрес, количество и тип данных. 
    Четвертый параметр указывает номер источника данных (головной процесс), 
    пятый параметр – название коммуникатора группы. 
    Таким образом, после обращения к MPI_Bcast все процессы имеют значение x и собственные идентификаторы
    */
    MPI_Bcast(x, N, MPI_INT, 0, MPI_COMM_WORLD);
    /*
        рассылка всем остальным процессам по строчке
    */
    MPI_Scatter(A, M, MPI_INT, row, M, MPI_INT, 0, MPI_COMM_WORLD);

    //расчет локального скалярного произведения
    int locRes=0;
    for (int i = 0; i < M; i++) {
        locRes += row[i] * x[i];
    }
    //собирание обратно в вектор б значений со всех процессоров
    MPI_Gather(&locRes, 1, MPI_INT, b, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (ProcRank == 0) {
        //вывод ответа на 0 процессе
        printf("B vector:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", b[i]);
        }
        printf("\n");
        delete[] A;
    }
    //завершение mpi
    MPI_Finalize();
    return 0;
}



void nzad11(int argc, char* argv[]) {
    //3 процесса
    constexpr int N = 8;
    constexpr int M = 4;

    int ProcNum;
    int ProcRank;
    srand(time(0));
    //инициализация mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);


    if (ProcNum != 3) {
        if (ProcRank == 0) {
            printf("Not enough processors! Need exactly %d\n", 3);
        }
        MPI_Finalize();
        return;
    }

    if (ProcRank == 0) {

        MPI_Datatype type;
        MPI_Datatype row;

        // Creates a contiguous datatype
        MPI_Type_contiguous(N, MPI_INT, &row);
        MPI_Type_commit(&row);

        MPI_Type_vector(M, 1, 2, row, &type);
        MPI_Type_commit(&type);


        int a[N][N];
        printf("Init Matrix a\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                a[i][j] = i % 2 +1;
                printf("%d\t", a[i][j]);
            }
            printf("\n");
        }
        MPI_Send(&(a[0][0]), 1, type, 1, 11, MPI_COMM_WORLD);
        MPI_Send(&(a[1][0]), 1, type, 2, 11, MPI_COMM_WORLD);

    }
    else if (ProcRank == 1) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M * N, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("First:\n");
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t",c[i][j]);
            }
            printf("\n");
        }
    }
    else if (ProcRank == 2) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M * N, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Second:\n");
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return;
}


void nzad12(int argc, char* argv[]) {

    
    constexpr int N = 8;
    constexpr int M = 2;

    struct qqq {
        int a1[N];
        int a2[N];
        int a3[N];
        int a4[N];
        int a5[N];
    };
    
    int ProcNum;
    int ProcRank;
    srand(time(0));
    //инициализация mpi
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);


    if (ProcNum != 4) {
        if (ProcRank == 0) {
            printf("Not enough processors! Need exactly %d\n", 3);
        }
        MPI_Finalize();
        return;
    }
    int arr[N][N];
    if (ProcRank == 0) {
        qqq a;
        MPI_Datatype typei[] = {MPI_INT,MPI_INT};
        MPI_Datatype type;
        MPI_Aint adr[3], disp[2];


        MPI_Get_address(&a, &adr[0]);
        MPI_Get_address(&(a.a1[0]), &adr[1]);
        MPI_Get_address(&(a.a5[0]), &adr[2]);

        disp[0] = adr[1]-adr[0];
        disp[1] = adr[2] - adr[0];
        int blocklen[] = { N ,N};


        MPI_Type_create_struct(2, blocklen, disp, typei, &type);
        MPI_Type_commit(&type);


        
        printf("Init Matrix a\n");
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                arr[i][j] = i;
                printf("%d\t", arr[i][j]);
            }
            printf("\n");
        }

        MPI_Send(&(arr[1][0]), 1, type, 1, 11, MPI_COMM_WORLD);
        MPI_Send(&(arr[2][0]), 1, type, 2, 11, MPI_COMM_WORLD);
        MPI_Send(&(arr[3][0]), 1, type, 3, 11, MPI_COMM_WORLD);
    }
    
    
    if (ProcRank == 1) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M * N, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("11111:\n");
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t", c[i][j]);
            }
            printf("\n");
        }
    }
    else if (ProcRank == 2) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M* N, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("22222:\n");
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t", c[i][j]);
            }
            printf("\n");
        }
    }
    else if (ProcRank == 0) {
        int c[M][N];
       for(int i = 0; i < M; ++i)
           for (int j = 0; j < N; ++j) {
               c[i][j] = arr[i * 4][j];
        }
       printf("00000:\n");
       for (int i = 0; i < M; ++i) {
           for (int j = 0; j < N; ++j) {
               printf("%d\t", c[i][j]);
           }
           printf("\n");
       }
    }
    else if (ProcRank == 3) {
        int c[M][N];
        MPI_Recv(&(c[0][0]), M* N, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("33333:\n");
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                printf("%d\t", c[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return;
}
