# MultiProcess-MultiThread
# 開發環境 
macOS Monterey
# 使用開發環境
Xcode Version 13.2.1 (13C100)
# 使用的程式語言 
C++
# 實作方法與流程 

## 實作方法:
1. 將檔案一個數字一個數字讀入後存在vector<int>numVec中。 

2. 再依照使用者將檔案切成k份，並存在vector<vector<int>> dataToKpart 中。

3. 根據使用者輸入的方法，判斷要做何種方法。

* 方法一:將存入的vector直接做bubblesort後輸出檔案。
* 方法二:將分成k份的vector輪流做bubblesort，所有vector再輪流經由兩個 vector 做 mergesort 合併成一個檔案後，以此類推，直至剩下一個 vector 後輸出檔案。
* 方法三:將分成k份的vector用fork的方式同時做bubblesort，將做好的 bubblesort vector 各自輸出為一個檔案後，等待所有 process 完成後，再讀入所有輸出的檔案到 vector 中。
        所有vector 經由兩個 vector 做 mergesort 合併成一個檔案後，以此類推，直至剩下一個 vector 後輸出檔案。
* 方法四:將分成k份的vector，把bubblesort2k放置到thread的陣 列中，同時做 bubblesort，等待所有 thread 完成後，經由兩個 vector 做 mergesort 合併成一個檔案後。
        以此類推，直至剩下一個 vector 後輸出檔案。
# 流程:
使用者輸入檔案名稱，再輸入要切成幾份，最後輸入要執行的方法 1-4。
1. 根據使用者的檔名先去判斷檔案是否存在，若不存在則再輸入一次，反之則進行下一步驟。
2. 使用者輸入要切成幾份後記錄為全域變數。
3. 再根據使用者輸入的數字來判斷要進行何種方法。輸入非1-4則需重新輸入，輸入 0 則結束程式。
* 方法一
將N個數目字直接進行BubbleSort，並顯示CPU執行之時間。
* 方法二
將N個數目字切成K份，在一個process內對K份資料進行 BubbleSort 之後，再用同一個 process 作 MergeSort，並顯示CPU 執行之時間。
* 方法三
將N個數目字切成K份，並由K個processes分別進行BubbleSort 之後，再用 process 作 MergeSort，並顯示 CPU 執行之時間。
* 方法四
將N個數目字切成K份，並由K個threads分別進行BubbleSort 之後，再用 thread 作 MergeSort，並顯示 CPU 執行之時間。

# 分析結果和原因:
<img width="552" alt="截圖 2022-10-07 下午5 21 31" src="https://user-images.githubusercontent.com/95215851/194520274-e364e27d-13b5-4dd7-a626-968f1bd09aa5.png">
<img width="560" alt="截圖 2022-10-07 下午5 21 36" src="https://user-images.githubusercontent.com/95215851/194520306-6dd15272-dc12-47bc-8161-09113483a1cf.png">

## 由此圖表可以得知在不同 N 值時:
方法一:
        效率最差的方式。因為所有資料用一個 bubbleSort 去執行。 bubbleSort 在資料量越大時所花費的時間越多，由其時間複雜度 O(2!) 可得知此結果。
方法二:
        將資料切成K份再輪流進行 bubbleSort，由於資料比方法一 的資料少了 1/k，將大問題分解成小問題，雖然用了一個 process 對 k 份資料排序，並用一個 process 將資料 Merge，但依成長幅度，其效率 還是遠大於第一題的方法。
方法三:
        把資料切成 k 份，由 k 個 process 進行排序，再由 1 個 process 將資料 Merge。由於是多個 process 同時執行 bubblesort 所以效 率與方法二相比較好。一個 Process 會同時存在多個 Thread。但是由於採用讀檔寫檔的方式，與 thread 直接取陣列的方式相比會較花時間。
方法四:
        將資料切成 k 份，由 k 個 thread 對 k 份資料排序，再由 1 個 thread 將 k 份資料 Merge。Thread 也是由多個 thread 同時執行 bubblesort，所以速度會較快。
可以看到方法三與方法四的執行時間之成長幅度相去不遠，代表兩種
方法效率差不多，是四種方法中，最佳的兩種。
        
