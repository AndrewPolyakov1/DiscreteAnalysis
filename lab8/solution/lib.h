#include<iostream>
#include<vector>

typedef std::vector<double> doub_vector;
typedef std::vector<double> int_vector;

void GaussAlgorythm(std::vector<doub_vector>& vec, doub_vector& res, int& N, int& M){
    int cost = N;
    for(int i = 0; i < N; i++){
        int rowNum, row = -1;
        int minCost = 51;
        for(int j = i; j < M; j++){
            if(vec[j][i] != 0 && vec[j][cost] < minCost){
                minCost = vec[j][cost];
                row = j;
            }
        }

        if(row == -1){
            res.clear();
            return;
        }

        rowNum = vec[row][cost+1];

        res.push_back(rowNum);
        vec[i].swap(vec[row]);

        for(int j = i + 1; j < M; j++){
            double k = vec[j][i] / vec[i][i];
            for(int l = i; l < N; l++){
                vec[j][l] -= vec[i][l] * k;
            }
        }
    }
}

std::pair<int_vector, int> NaiveAlgorythm(int_vector freepos, int N, int start, std::vector<doub_vector>& arr){
    std::pair<int_vector, int> pairs;
    int_vector currentFree, result, currentResult;
    int sum = 100000;
    if(start == N){
        return std::make_pair(result, 0);
    }
    for(int j = 0; j < freepos.size(); j++){
        if(arr[freepos[j]][start]){

            currentFree = freepos;
            int_vector::iterator it = currentFree.begin()+j;
            currentFree.erase(it);
            pairs = NaiveAlgorythm(currentFree, N, start+1, arr);
            pairs.first.push_back(freepos[j]);

            if(sum > pairs.second + arr[freepos[j]][N]){
                sum = pairs.second + arr[freepos[j]][N];
                result = pairs.first;

            }
        }
    }
    return std::make_pair(result, sum);
}