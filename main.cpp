//
//  main.cpp
//  os_p1
//
//  Created by Ruby on 2022/4/24.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include<sys/time.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <spawn.h>

using namespace std;

vector <int> numVec;
vector<vector <int>> dataToKpart ;
string filename;
timeval startT , endT;
int divideNum = 0;
pid_t c_pid = 1;
void init(){
    numVec.clear();
    dataToKpart.clear();

}

void readFile(){
    //init();
    numVec.clear();
    ifstream txtfile;
    string dataLine;
    int num;
    cout << "輸入檔案名稱: "<<endl;
    cin >> filename;
    //filename += ".txt";
    txtfile.open(filename+ ".txt");
    while (!txtfile.is_open()) {
        cout << "Failed to open file.\n";
        cout << "輸入檔案名稱: "<<endl;
        cin >> filename;
        txtfile.open(filename + ".txt");
    }

    while (txtfile >> num  ) {
        numVec.push_back(num);
    }
    txtfile.close();
    
}

void bubbleSort(vector<int>& bubbleVec){
    int i, j, tmp;
    for(i = bubbleVec.size()-1; i > 0; i--)
    {
        for(j = 0; j <= i-1; j++)
        {
            if( bubbleVec[j] > bubbleVec[j+1])
            {
                tmp = bubbleVec [j];
                bubbleVec[j] = bubbleVec[j+1];
                bubbleVec[j+1] = tmp;
            }
        }
    }
    
}


void writeFile(string outputnum, vector <int> outVec){
    double time;
    ofstream outFile;
    outFile.open(filename+outputnum+".txt");
    outFile << "Sort :" <<endl;
    for(int i = 0 ; i < outVec.size(); i ++ ){
        outFile << outVec[i]<< "\r\n";
    }
    timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%Y-%m-%d %H:%M:%S", std::gmtime(&ts.tv_sec));
    gettimeofday(&endT, NULL) ;
    time = (endT.tv_sec - startT.tv_sec)*1000.0;
    time += (endT.tv_usec - startT.tv_usec)/1000.0;
    //cout <<time/1000<<endl;
    cout << "CPU Time : "<< time/1000 << " sec" <<endl;
    outFile << "CPU Time : "<< time/1000 << " sec" <<endl;
    outFile << "datatime: " <<buff<<ts.tv_nsec <<"+08:00"<<endl;
    outFile.close();
}

void dividePart(){
    vector<int> tmp;
    int count = 0;
    int unitnum = 0 ;
    for(int i = 0; i < numVec.size() ; i++){
        
        tmp.push_back(numVec[i]);
        if(unitnum == (numVec.size()/divideNum)-1){
            count ++;
            dataToKpart.push_back(tmp);
            unitnum=-1;
            tmp.clear();
        }
        unitnum++;
    }
    if(numVec.size() % divideNum != 0 ) {
        for (int i = 0 ; i < tmp.size() ; i++)
            dataToKpart[dataToKpart.size()-1].push_back(tmp[i]);
    }


}

void merge(vector<vector<int>> &mergeVEC){
    //dataToKpart 存num的vector
    vector<int> mergeTmp;
    int idxLeft = 0, idxRight = 0;
    for(int i = 0 ; idxLeft<mergeVEC[0].size() && idxRight < mergeVEC[1].size() ; i++){
        if (mergeVEC[0][idxLeft] <= mergeVEC[1][idxRight] ) {
            mergeTmp.push_back(mergeVEC[0][idxLeft]);
            idxLeft++;
        }
        else{
            mergeTmp.push_back(mergeVEC[1][idxRight]);
            idxRight++;
        }
    }
    
    while(idxLeft < mergeVEC[0].size()){
        mergeTmp.push_back(mergeVEC[0][idxLeft]);
        idxLeft++;
    }
    while(idxRight < mergeVEC[1].size()){
        mergeTmp.push_back(mergeVEC[1][idxRight]);
        idxRight++;
    }
    
    mergeVEC.push_back(mergeTmp);
    mergeVEC.erase(mergeVEC.begin());
    mergeVEC.erase(mergeVEC.begin());

}
    

int main(int argc, const char * argv[]) {
    // insert code here...
    int command = -1 , num =0 ;             // user command
    vector<int> tmp;
    init();
    readFile();
    cout << "請輸入要切成幾份: "<<endl;
    cin >> divideNum;
    cout << "請輸入方法編號（方法1, 方法2, 方法3, 方法4）: "<<endl;
    cin >> command; // get a command
    while(command!=1 && command!=2 && command!=3 && command!=4 && command!= 0){
        cout << "方法不存在請重新輸入！";
        cout << "請輸入方法編號（方法1, 方法2, 方法3, 方法4）: "<<endl;
        cin >> command;
    }
    dividePart();
        
    if(command == 1 ){
        gettimeofday(&startT, NULL) ;
        bubbleSort(numVec);
        writeFile("_output1", numVec);
        numVec.clear();
        //break;
    }
    else if(command == 2 ){
        gettimeofday(&startT, NULL) ;
        for(int i = 0 ; i < dataToKpart.size() ; i++){
            bubbleSort(dataToKpart[i]);
        }
        while(dataToKpart.size() != 1 ){
            if(dataToKpart.size() == 1) break;
            //cout << dataToKpart.size() <<endl;
            merge(dataToKpart);
        }
        writeFile("_output2", dataToKpart[0]);
        dataToKpart.clear();
        numVec.clear();
    }
    else if(command == 3 ){
        ifstream txtfile;
        gettimeofday(&startT, NULL) ;
        for(int i = 0 ; i < divideNum; i++){
            c_pid = fork();
            if(c_pid == 0){
                ofstream outFile;
                outFile.open(to_string(i)+".txt");
                bubbleSort(dataToKpart[i] );
                for(int j = 0 ; j < dataToKpart[i].size(); j ++ ){
                    outFile << dataToKpart[i][j]<< "\r\n";
                }
                outFile.close();
                exit(0);
            }
        }
        
        for(int i = 0 ; i < (divideNum*2) ; i ++ ){
            wait( 0 );
        }
        numVec.clear();
        dataToKpart.clear();
        for(int i = 0 ; i < divideNum ; i ++ ){
            string path = to_string(i)+".txt";
            char *savePath = const_cast<char*>(path.c_str());
            txtfile.open(to_string(i)+".txt");
            while (txtfile >> num  ) {
                numVec.push_back(num);
            }
            txtfile.close();
            remove(savePath);
        }
        dividePart();
        while(dataToKpart.size() != 1 ){
            if(dataToKpart.size() == 1) break;
            //cout << dataToKpart.size() <<endl;
            merge(dataToKpart);
        }

        writeFile("_output3",dataToKpart[0] );
        dataToKpart.clear();
        numVec.clear();
        //break;
    }
    else if(command == 4 ){
        numVec.clear();
        gettimeofday(&startT, NULL) ;
        thread threads1[divideNum];
        for (int i = 0; i < divideNum; i++) {
            threads1[i] = thread( bubbleSort, ref(dataToKpart.at(i)) );
        } // for
        
        for (int i = 0; i < dataToKpart.size(); i++) {
            threads1[i].join();
        }
        
        //-----merge sort----
        while(dataToKpart.size() != 1 ){
            if(dataToKpart.size() == 1) break;
            merge(dataToKpart);
        }
        writeFile("_output4", dataToKpart[0]);
        dataToKpart.clear();
    }
    else if(command ==0 ) {
        cout << "Quit the program !" << endl;
    }
    return 0;
}
