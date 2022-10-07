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
