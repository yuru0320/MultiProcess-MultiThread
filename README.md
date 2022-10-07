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
