#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>//floor
#include <climits>
#include <chrono>
#include <random>
#include <algorithm>
#include "CensusData.h"

// formal parameter name commented out to avoid unused variable warning
void CensusData::insertionSort(int type) {
    for(int x=0; x<getSize();x++){
      Record* rec=data[x];
      int y=x-1;
      if(type==POPULATION){
      while(y>=0 && rec->population<data[y]->population){
        data[y+1]=data[y];
        y=y-1;
      }//while
      data[y+1]=rec;
    }//if
  else{//else it will sort by city name
      while(y>=0 && *(rec->city) < *(data[y]->city)){
        data[y+1]=data[y];
        y=y-1;
      }//while
      data[y+1]=rec;
    }//for
  }
}

// formal parameter name commented out to avoid unused variable warning
void CensusData::mergeSort(int type) {
    merge_sort(0,getSize()-1,type);
}//mergeSort
void CensusData::merge_sort(int first, int end,int type){
  if(first<end){
    int mid=floor((first+end)/2);
    merge_sort(first,mid,type);
    merge_sort(mid+1,end,type);
    merge(first,mid,end,type);
    }//if
}//merge_sort

void CensusData::merge(int first,int mid,int last, int type){
    int n1=((mid-first)+1);
    int n2=last-mid;
    vector<Record*>left;
    vector<Record*>right;
    for(int x=0;x<n1;x++){
      left.push_back(data[first+x]);
    }//for that loops through the left array
    for(int y=0;y<n2;y++){
      right.push_back(data[mid+y+1]);
    }//for that loops through the right array
    string str="~";
    left.push_back(new Record(str,str,INT_MAX));
    right.push_back(new Record(str,str,INT_MAX));
    int i,j;
    i=j=0;
    if(type==POPULATION){
    for(int x=first;x<=last;x++){
      if(left[i]->population<=right[j]->population){
        data[x]=left[i];
        i=i+1;
      }//if
      else{
        data[x]=right[j];
        j=j+1;
      }//else
    }//for
  }//if that checks if the list needs to be sorted by population
  else{
      for(int x=first;x<=last;x++){
        if(*(left[i]->city)<= *(right[j]->city)){
          data[x]=left[i];
          i=i+1;
        }//if
        else{
          data[x]=right[j];
          j=j+1;
        }//else
      }//for
  }//else it will sort by city name
}//merge

// formal parameter name commented out to avoid unused variable warning
void CensusData::quickSort(int type) {
  quick_sort(0,getSize()-1,type);
}
void CensusData::quick_sort(int first,int last,int type){
  if(first<last){
    int mid=partition(first,last,type);
    quick_sort(first,mid-1,type);
    quick_sort(mid+1,last,type);
  }
}

int CensusData::partition(int first, int last, int type){
  unsigned seed=std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int>distribution(first,last);
  int pivot=distribution(generator);
  std::swap(data[pivot],data[last]);
  if(type==POPULATION){
    int x=(data[last]->population);
    int i=first-1;
    for(int j=first;j<last;j++){
      if((data[j]->population)<=x){
        i=i+1;
        std::swap(data[j],data[i]);
      }//if
    }//for
    std::swap(data[last],data[i+1]);
    return i+1;
  }//if that checks the population
  else{
    string x=*(data[last]->city);
    int i=first-1;
    for(int j=first;j<last;j++){
      if((*data[j]->city)<=x){
        i=i+1;
        std::swap(data[j],data[i]);
      }//if
    }//for
    std::swap(data[last],data[i+1]);
    return i+1;
  }//else that checks the name of city
}//partition
