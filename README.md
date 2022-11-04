<h1 align="center" >Pthread Experiment</h1>

# Introdution
<p>It's a study in the language C about parallel processing using `threads` and `mutex`. The main objective is to process a big matrix and count how many prime numbers it has.<p>
<p>So the matrix its divided in block of equal size and the blocks are send to threads and this blocks are processed in parallel by each thread, so we can decrease the process time.</p>

* Requisites:
> You need to install the GCC to compile the .c file. I'm using `gcc 9.4.0`.

* Linux:
> To compile the code you should run: `gcc -o binary main_Pthreads.c -lpthread` on your terminal. And them you get the binary of the code named: `binary`. Run typing: `./binary`.

* Windows:
> To compile the code you should run: `gcc -o binary.exe main_Pthreads.c -lpthread` on your terminal. And them you get the binary of the code named: `binary.exe`. Run typing `binary`.

> You can rename the output file as you want using `gcc -o <filename> main_Pthreads.c -lpthread`.

# The matrix
The numbers of the matrix has a max limit set by `Biggest_Rand_Number`. The matrix need to be a square matrix, so you can set the `n` and `m` as long n == m and need to have a size that is divisible by the number of threads (`(n*m) % nThreads == 0`). The number of threads as set at `nThreads`, i recommend you set the number of cores of your processor.

# Functions
* `CreatePthreads` as the name say create the threads and `JoinPthreads` join them on the processing pool.
* `ProcessMatrix` is the function that call the threads to be created and joined. 
* `FillMatrix` is responsible to fill the matrix with random numbers. 
* `ShowMatrix` just print the matrix on the screen. 
* `endOfBlock` calculate the index where a block ends. It receive the block number.
* `startOfBlock` calculed the index where a block starts. It receive the block number.
* `ProcessSubMatrix` is the function responsable to be process a block of the matrix. That function is the one been processed in every joined thread. It pick the block number using the `Block_number` that is a global variable, increment that variable, so the next thread pick the next block, and then start counting how many prime numbers there are in that block, incrementing a local counter. At the end it increment the global counter using that local counter. It uses the mutex, lock and unlock to operate with the global variables, so the threads don't shock operations.
* `isPrime` receive a number and check if it's a prime number. If its zero or one its a exception so it just return FALSE, if not start verifing if therer a number that can divided the number with remainder being zero.
