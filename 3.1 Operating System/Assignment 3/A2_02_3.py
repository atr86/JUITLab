"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
 *
 * 3rd Year 1st Semester OS Lab - Information Technology
 * Section: A2
 * Team Number: 02
 *    Team Member Names                   Roll Numbers
 * 1. Abishkar Chatterjee (Team Leader) - 002311001080
 * 2. Atrij Roy                         - 002311001086
 * 3. Soyeb Hoque                       - 002311001065
 *
 * Assignment: 3 (10 Marks) [CO4]
 * Title: Parallel Programming in Python
 * Description: The objective of this assignment is to write a parallel program in Python which will do Matrix Multiplication between two large Square Matrices with
 * unsigned integer elements. You have to also measure the time elapsed. The Matrix should be large enough (at least 3000 x 3000) and dynamically
 * allocated to fit in your computer memory. Both the Matrices need to be initialized with random numbers (‘mod’ to some value).
 * As you increase the number of Parallel Threads (max to your number of CPUs), your timing should show improvement. Use time.perf_counter() or
 * an equivalent high-resolution timer to note down the timing. Make sure you attach the timing to the starting comment block of your source file. Your
 * time should not include the Matrices initialization time. You are not allowed to use Python’s threading module. You can import thepackage “multiprocessing” 
 * for this purpose. Also, use proper command to show CPU utilization(cpustat or sar) and attach these outputs to the starting comment block of your source file.
 *
 * Command Line Inputs Required: 
 * This program should take four command line arguments. 
 * The first argument N is the dimension of the Square Matrix.

 * The second argument C is about the number of Parallel Threads. For example, the value of the second argument will be 1, 2, 3, 4 etc.; signifying how the workload will be split among all the CPUs.

 * The third argument M will be the value of the ‘mod’ which will be used to initialize all the elements of two input square matrices.

 * The fourth (last) argument P will be the print_switch. If its value is ‘1’, both the Input and Output Matrices and as well as the Result Matrix will be printed
 * on the screen. In case the value is ‘0’, Matrices won’t be printed on the screen. 

 * Sample Output Generated:
 * For inputs:
 * N = 3000
 * C = 6
 * M = 1000
 * P = 1
 * ===== OUTPUT =====
 * Matrix A
 *  145   590   728    68    90     7   540   795   396   476   405   366   811    28   253   278   700   894   888   872
 *  133   867   315   622   993   827   228   540   296   229   299   702   804   899   647   863   353   816    85   411
 *   42   226   551   687   358   867   177   559   648   996   230   621   278   187   297    73   638   449   802   249
 *  773   615   795   655   742   262   280   762   505   757   574   248   750   932   722   987   460   769   965    15
 *  321   498   740    96   818   790   543   554   454   506   179   251   142   181    45   915   158   278   355   301
 *  976   250   801   271   254   129   575   154   892   408   814   201   350   160   212   710   356   529   753   413
 *    8   102   201   411   651   580   245    49   712   696   382   173   530   409   201   728   202   625   363   259
 *  828   814   590   694    62   314   664   425   101   281   250   705   644   550   334   729    97   736   972   715
 *   67   312   190    85   248   841   401   726   759   417   228   366   679   308   861   215   696   575    86   821
 *   45   676   888   347   914   838   125   872   498   511   638   818   920   702   568   150   165   305     9    68
 *  235   588   254   968   556    57   587   893   325   557   137   407   741   311   762   765   337   240    91   416
 *  528   286   642   400   447    24   257   757   290   852    28   413   782   782   900   887   925   673   942   381
 *  216    55   469    29   815   148   556   269   244   897   957   110   170   822   439   296   806   812   213   745
 *  709   270   520   216   603   960    45   496   679   965     6   723   382   696   916   529   669   230    40   619
 *  556    28   291   225   757   635   798   373   614   872   149   981   314   116   593   196   289   594   432   566
 *  895   190   176   280    68   463   850   596   990   227   281   898   406   274    20   503   226    33    56   561
 *  461    10   683   499   895   381   844   886   950   521   739   306   658   119   416   943   139   936   923   398
 *  156   963   459   976   513   925   184   116   424   440    38   839   434   840   895   768   914   879   337   662
 *  835   982   322   364   814   787   571   890   967   774   715   245   532   704   702   915   539   695   602   496
 *  882   487   579   975    51   747   550   363   869   309   766   581   271   320   323    82   852   919   941   325
 * Truncated for display... (showing first 20 rows and columns)
 * Matrix B
 *  237   135   720   292   218   524   187   275   715   998   692   744   101   622   779   855   566   774   922   504
 *  765   612    82   695   339    35   934   787    58    58    28   463   188   639   836   864   743   301   685   593
 *  960   993   211    34   135   944   652   873   608   618   388   715   931   951   436   962   344   737   661   751
 *  161   257   240    60   587   898   731   152   546   514   164   382   806   414   170   900   882   522   410   493
 *  980   701   913   155    23   212   774   338   767   930   213   188   926    26   232   417   849   306   956   355
 *  164   160   589   182   723   195   739   248   818   409   812   964   748   472   338   790   499   828    70   935
 *  847    54   610   785   342   613   356   798   961   178   757   722   447   492   677   518   453   897   895   580
 *  507   357    52   506    75   703   735   421   471   181   246   547   607   332   434   763   914   726   947   624
 *  600   696    92   563   880   802   996   713    32   752   811   648   991   820   102   786   725   114   169    69
 *  571   691   941   109   322   979   223   536    70   880   142   356   988   747   475   170   668   883   605   951
 *  330   178   224   357   650    29   915    20   879   493   601   821   277   808   386   212   452   225   103   222
 *  775   816   395   841   861   313    30   174   501   156   697   754   266   524   964   690   416   966   732   368
 *  918   317    66    70   301   571   335   689   509   476   244    50   246   917    50   452   203   858   891   755
 *  430   192   211   861   879   532   401   835   731   546   636   954    22   873   751   977   289   296   189   924
 *  838   479   530   458   793   633    50   346   699   105   622   426   623   438   761    62   293   723   463   303
 *  944   800   845   862    84   578    42   419    95   142    27   619   166    95   931    52   603   731   977   678
 *  625    81   754   174   932   403   286   322   574   765   585   267   201   202   329   609   105   731   531   676
 *  993   379   430   684   261   645   705   241   390   175   325   806    91   149   898   919   234   225   602   115
 *  520   655   874   454   340   620   129   365   536   206   525   478   777   395   661   529   926   980   549    33
 *   19   515   979   218    76    63   568   277   824   505   286   657   944   508   391   260   969   644   764   585
 * Truncated for display... (showing first 20 rows and columns)
 *
 * COMPUTING MULTIPLICATION...
 * [INFO] cpustat not found, trying sar...
 * Linux 5.15.167.4-microsoft-standard-WSL2 (LAPTOP-681OEGCT)      08/15/25        _x86_64_        (8 CPU)
 *
 * 09:43:25        CPU     %user     %nice   %system   %iowait    %steal     %idle
 * 09:43:26        all     13.18      0.00     12.44      0.12      0.00     74.25
 * 09:43:27        all     49.57      0.00     14.80      0.00      0.00     35.64
 * 09:43:28        all     72.90      0.00      6.15      0.00      0.00     20.95
 * 09:43:29        all     74.66      0.00      0.37      0.00      0.00     24.97
 * 09:43:30        all     74.69      0.00      0.63      0.00      0.00     24.69
 * 09:43:31        all     74.91      0.00      0.12      0.00      0.00     24.97
 * 09:43:32        all     74.47      0.00      0.75      0.00      0.00     24.78
 * 09:43:35        all     74.32      0.00      0.99      0.00      0.00     24.69
 * 09:43:36        all     74.63      0.00      0.50      0.00      0.00     24.88
 * 09:43:37        all     74.63      0.00      0.75      0.00      0.00     24.63
 * 09:43:38        all     74.94      0.00      0.25      0.00      0.00     24.81
 * 09:43:39        all     74.01      0.00      1.24      0.00      0.00     24.75
 * 09:43:40        all     75.09      0.00      0.00      0.00      0.00     24.91
 * 09:43:41        all     74.78      0.00      0.37      0.00      0.00     24.84
 * 09:43:42        all     74.38      0.00      0.75      0.00      0.00     24.88
 * 09:43:43        all     66.71      0.00      9.94      0.00      0.00     23.35
 * 09:43:44        all     59.24      0.00     13.05      0.00      0.00     27.71
 * 09:43:45        all     60.25      0.00     13.95      0.12      0.00     25.68
 * 09:43:46        all     71.32      0.00      5.44      0.00      0.00     23.24
 * 09:43:47        all     75.16      0.00      0.38      0.00      0.00     24.47
 * 09:43:48        all     74.72      0.00      0.50      0.00      0.00     24.78
 * 09:43:49        all     74.63      0.00      0.62      0.00      0.00     24.75
 * 09:43:50        all     74.53      0.00      0.75      0.00      0.00     24.72
 * 09:43:51        all     74.44      0.00      0.74      0.00      0.00     24.81
 * 09:43:52        all     74.63      0.00      0.62      0.00      0.00     24.75
 * 09:43:53        all     74.53      0.00      0.62      0.00      0.00     24.84
 *
 * 09:43:53        CPU     %user     %nice   %system   %iowait    %steal     %idle
 * 09:43:54        all     74.75      0.00      0.50      0.00      0.00     24.75
 * 09:43:55        all     74.57      0.00      0.62      0.00      0.00     24.81
 *
 * Matrix C = A x B (mod 1000) =
 * 599   714   465     0   445   976    43   633   462   923   336    18   307   498   349   717   928   451   876     3
 * 941   443   536   494   571   352   906   298   701    94   898   534   760   631   907   317   701   404   130   342
 * 640   459   527   143   732   915   885    46   522   789   866   323   440   830    37    63   942   526   701   854
 * 668   925   798   341   339   274   521   887   980   309    79   836   658   281   352   126   766    24   464    31
 * 339   277    35   129   675   571   819   695   735   439   372   186   787   996    57   891   491   544   680   563
 * 543   414   817   634   852    38   885   593   262   872    49   378   389   374    75    80   517   933   761   812
 * 567   680   143   310   598   404   893   662    49   860   451    11   698   128   680   540   267   966   562   737
 * 744   109   714   254   374   467   293   986   839    40    60   733   174   132   184   567   277   470   684   308
 * 292   120   522   936   858   156   496   520   282   377   739   200   375   933   994   615   755    67   863   543
 * 368   772   149   312   714   620   293   582    44   379   260   366   817   781   718   227   996   830   447   987
 * 126   896   703   999   474   219   994   447   349   410   560   698   613   384   132   175    72   640   684   521
 *  87   216    75   279   970   718   772   288   918   240   343   393   504   509   561   729    68   164   407   857
 * 858   835   121   499   208   184   744   171   819   724   431   928   460   788    67   345   342   300   497   949
 * 679   561   750   324   812   994   153   850   583   442   305    66   530   118    56   227   872   298   648   329
 * 884   245   271   443   651   856   676   846   523   845   114   528   721   875   858   158   749   494   212   975
 * 996   416   219    35   415   294   324   124   105   979   278   967   515   913   681   623   613   428   517   274
 * 186   193   984   433   737   371   575    72   227   337   289   182   757   804   344    56   677   338   836   385
 * 238   755   296   831   917    85   214   342   287   680   539   426    12   956   816   737   583   284   142   950
 * 480   382   802   550    29   900   341    73    37   767   783   204   963   456    77   219   337   748    52    36
 * 875   386   455   221    39   496   190   265   624   696   665   592   994   762   724   300   107   141   676    65
 * Truncated for display... (showing first 20 rows and columns)
 

 * TIME TAKEN IS 20.401421 SECONDS

 * ===== END =====
 *
 * NOTE: 
 * 1. This program will only run on POSIX-compliant OS like Linux, or other Unix-based systems. To run on Windows, you have to run it on a WSL terminal.
 * 2. Please make sure pip is installed.
 * 3. Please make sure you have atleast one of cpustat or sar installed, otherwise the CPU process statistics will not display.
 *
 * HOW TO COMPILE AND RUN:
 * 1. Navigate into the same directory as this .py file.
 * 2. To compile and run the file, enter: 
 *    python3 A2_02_3.py N C M P 
 *    (Where N, C, M and P are the input parameters mentioned above)
 *    Example: python3 A2_02_3.py 3000 6 1000 1
 *
 *
 *
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

import multiprocessing
import sys
import time
import subprocess

# Auto-install numpy if not present
try:
    import numpy as np
except ImportError:
    subprocess.check_call([sys.executable, "-m", "pip", "install", "numpy"])
    import numpy as np


# ---------------- CPU Monitoring ----------------
def start_cpu_monitor():
    try:
        # Try cpustat first (sample every 1 second)
        proc = subprocess.Popen(["cpustat", "-c", "1"])
        return proc
    except FileNotFoundError:
        print("[INFO] cpustat not found, trying sar...")
        try:
            # sar 1 → sample every 1 second continuously
            proc = subprocess.Popen(["sar", "1"])
            return proc
        except FileNotFoundError:
            print("[WARNING] Neither cpustat nor sar found. CPU monitoring disabled.")
            return None

def stop_cpu_monitor(proc):
    if proc:
        proc.terminate()


# ---------------- Matrix Multiplication ----------------
s = sys.argv
if len(s) < 5:
    print(f"Required 4 arguments. You entered {len(s)}")
    sys.exit(1)

MAX = int(s[1])
MAX_PROCESS = int(s[2])
MOD = int(s[3])
MAX_VAL = 100000
print_switch = int(s[4])

# Generate random matrices using NumPy
matA = np.random.randint(0, MOD, size=(MAX, MAX), dtype=np.int64)
matB = np.random.randint(0, MOD, size=(MAX, MAX), dtype=np.int64)

def printMatrix(mat):
    for i in range(min(20, mat.shape[0])):
        for j in range(min(20, mat.shape[1])):
            print(f"{mat[i, j]:5d}", end=" ")
        print()
    print("Truncated for display... (showing first 20 rows and columns)")

def multi(args):
    row_index, A, B = args
    row_result = A[row_index, :].dot(B)
    return (row_index, row_result)

if __name__ == "__main__":
    if print_switch == 1:
        print("Matrix A")
        printMatrix(matA)
        print("Matrix B")
        printMatrix(matB)
        print("\n\nCOMPUTING MULTIPLICATION...")

    # Start CPU monitoring
    cpu_proc = start_cpu_monitor()

    args = [(i, matA, matB) for i in range(MAX)]
    pool = multiprocessing.Pool(processes=MAX_PROCESS)

    start_time = time.perf_counter()
    results = pool.map(multi, args)
    pool.close()
    pool.join()
    end_time = time.perf_counter()

    matC = np.zeros((MAX, MAX), dtype=np.int64)
    for row_index, row_result in results:
        matC[row_index, :] = row_result

    # Stop CPU monitoring
    stop_cpu_monitor(cpu_proc)

    print("Matrix C = A x B (mod {}) =".format(MOD))
    printMatrix(matC % MOD)  # apply modulus before displaying


    elapsed_time = end_time - start_time
    print(f"\n\nTIME TAKEN IS {elapsed_time:.6f} SECONDS")


