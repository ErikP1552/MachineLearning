//
//  main.cpp
//  KmeansNew
//
//  Created by Erik on 9/16/19.
//  Copyright © 2019 Erik. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct dataHolder{
    int r;
    int g;
    int b;
};

double comparitorTemp = 0;
double distance(double, double, double, double, double, double);
int findSmallestElement(double arr[], int n);
dataHolder updateCenters(dataHolder c[], dataHolder Cluster);
void print(dataHolder c);
float newTermination(dataHolder Cluster, dataHolder object);
bool readFile(dataHolder input[], string infile);
void loadFile(dataHolder input[]);
void assignStartClusters(dataHolder input[], dataHolder Clusters[]);
void calculateDistances(dataHolder input[], dataHolder Clusters[]);
void saveClusterCentersToFile(dataHolder input[], int knn[]);

// Object to hold K-cluster Centers
dataHolder Cluster[16] = {0,0,0}; // empty for now
// Objects to hold assigned data points per cluster to calculate distances averaged per cycle
dataHolder Cluster1[20000] = {0,0,0};
dataHolder Cluster2[20000] = {0,0,0};
dataHolder Cluster3[20000] = {0,0,0};
dataHolder Cluster4[20000] = {0,0,0};
dataHolder Cluster5[20000] = {0,0,0};
dataHolder Cluster6[20000] = {0,0,0};
dataHolder Cluster7[20000] = {0,0,0};
dataHolder Cluster8[20000] = {0,0,0};
dataHolder Cluster9[20000] = {0,0,0};
dataHolder Cluster10[20000] = {0,0,0};
dataHolder Cluster11[20000] = {0,0,0};
dataHolder Cluster12[20000] = {0,0,0};
dataHolder Cluster13[20000] = {0,0,0};
dataHolder Cluster14[20000] = {0,0,0};
dataHolder Cluster15[20000] = {0,0,0};
dataHolder Cluster16[20000] = {0,0,0};
// Create file in section and save data to array of 512 sets
dataHolder input[20000]; // Total of pixels in the document






int main() {
    cout << "Program to Test and demostrate K-means" <<endl<<endl<<endl;
    //TASK 1 - CREATE DATA OBJECTs TO HOLD ALL DATA POINTS X,Y
    cout << "Created Test input" <<endl<<endl<<endl;
    
    
    dataHolder c[] = {{55,57,95}, {47,58,58}, {47,85,39}};
    dataHolder x, h;
    x.r = {43};
    x.g = {32};
    x.b = {22};
    h = updateCenters(c, x);
    print(h);
    
    //loadFile(input);
    
    //assignStartClusters(input, Cluster);

    /*for (int jk = 0; jk < 16; jk++){
                       cout << "Values for Cluster at Start: " << jk << " : " <<  Cluster[jk].r << " " << Cluster[jk].g << " " << Cluster[jk].b << endl;
                 }*/
    
    //ISSUE WITH updating centers in this
    //calculateDistances(input,Cluster);   // FOR DEBUGGING  - CLUSTER CENTERS ARE EXCEEDING 16 currently
 
    
    return 0;
}





 
dataHolder updateCenters(dataHolder c[], dataHolder x){ //FIRST ONE is STORAGE for CLUSTER, Second one is current cluster value
    int sumr = 0, sumg = 0, sumb = 0;
    int q = 0, k = 0, l = 0;
    dataHolder temp = {0,0,0}; // HOLDER object
   
    for (int i = 0; i < 3; i++){ // RUNS THROUGH EACH THE WHOLE SIZE OF THE ARRAY
            
        if (c[i].r != 0){ // MAKING SURE ELEMENT IS NOT EMPTY
             sumr = sumr + c[i].r; //ADDING THE VALUE OF EACH ELEMENT R VALUE TO SUMR
            
            cout << " SUM of R values is: " << sumr <<endl;
            cout << " Total numbers is: " << q <<endl;
             q++; // ADDING A COUNT ELEMENT TO DIVIDE BY TOTAL OF ELEMENTS NOT 0
         }
        
        
         if (c[i].g != 0){ // MAKING SURE ELEMENT IS NOT EMPTY
             sumg = sumg + c[i].g; //ADDING THE VALUE OF EACH ELEMENT G VALUE TO SUMR
             
             cout << " SUM of g values is: " << sumg <<endl;
             cout << " Total numbers is: " << k <<endl;

             k++; // ADDING A COUNT ELEMENT TO DIVIDE BY TOTAL OF ELEMENTS NOT 0
         }
        
        
         if (c[i].b != 0){ // MAKING SURE ELEMENT IS NOT EMPTY
             sumb = sumb + c[i].b;
             
             cout << " SUM of b values is: " << sumb <<endl;
             cout << " Total numbers is: " << l <<endl;
             
             l++; // ADDING A COUNT ELEMENT TO DIVIDE BY TOTAL OF ELEMENTS NOT 0
           }
    }
        
        
    
    
    //NEXT
    
        
       if (l != 0){ //MAKING SURE IT WAS MORE THEN 1 REPETITIONS
           cout << " sumb is " << sumb << " divided by " << l<<endl;
           
           sumb = (sumb / l); // DIVIDING TOTAL OF DISTANCES BY THE NUMBER OF ELEMENTS
       }
     
       if (k != 0){//MAKING SURE IT WAS MORE THEN 1 REPETITIONS
           cout << " sumg is " << sumb << " divided by " << l<<endl;
           
           sumg = (sumg / k); // DIVIDING TOTAL OF DISTANCES BY THE NUMBER OF ELEMENTS
       }
     
       if (q != 0){//MAKING SURE IT WAS MORE THEN 1 REPETITIONS
           cout << " sumr is " << sumb << " divided by " << l<<endl;
           
           sumr = (sumr / q); // DIVIDING TOTAL OF DISTANCES BY THE NUMBER OF ELEMENTS
       }

    
    
    // Saving results
    
    temp.r = sumr; // SAVING THE AVERAGE OF THE TOTAL DISTANCES IN A TEMP
    temp.g = sumg; // SAVING THE AVERAGE OF THE TOTAL DISTANCES IN A TEMP
    temp.b = sumb; // SAVING THE AVERAGE OF THE TOTAL DISTANCES IN A TEMP
    
    
    
    
    
    if (temp.r && temp.g && temp.b != 0){
        return temp; // RETURNS TEMP IF NOT 0
    }
    
    else{
        
       return x; //RETURNS PREVIOUS SAVED CLUSTER IF THE VALUES ARE 0
}
    
}





void calculateDistances(dataHolder input[], dataHolder Clusters[]){
       int i = 16, holderTemp = 0;
       int setNum = 0;
       int newcycles = 0;
       //int knn[20245];
       int knn[20000];

       while (setNum == 0){ //forever**
      int newterminationtemp = 0;
       newcycles++;
           while(i < 20000){   // for each pixel**
               //i is 16 - first 16 saved as cluster points already
               // Need to modify to be 1 on next rotation if not already
            
               int k = 0;
               // Calculating distance between each center
           double x = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x1 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x2 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x3 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x4 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x5 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x6 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x7 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x8 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x9 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x10 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x11 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x12 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x13 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x14 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           double x15 = distance(input[i].r, input[i].g, input[i].b, Cluster[k].r, Cluster[k].g, Cluster[k].b); k++;
           
        double temp[] = {x, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15}; // to easily find closest one
               
        int ClusterTemp = findSmallestElement(temp, 16);
              // cout << "Smallest element is: " <<ClusterTemp <<endl;
               
         /*
        cout << "Saved Element at array element " << i << " that holds " << input[i].r << " " << input[i].g << " " << input[i].b << " is assigned to cluster at area (0-15)" << ClusterTemp <<endl; // Cluster temp should always be number between 1 - 16*/
               
               // ***** LOGIC IS GOOD ABOVE
               
           knn[i] = ClusterTemp; // Smallest cluster element being saved into knn[i] as index number
           int tempa = 0;
           if (ClusterTemp == 1){
              //Cluster1[i] = input[i]; // Cluster1 is holding the pixel of current i
              
              tempa = newTermination(Cluster[0], input[i]);  // New Termination is having the pixel calculated into it twice
              Cluster1[i] = input[i]; // STORING THE PIXEL INTO CLUSTER1 TO HOLD EACH ONE MATCHING THIS CLUSTER TO UPDATE LATER
              newterminationtemp = newterminationtemp + tempa; // newtermination temp is adding new termination calculation into it for a total for each i
           }
               
           else if (ClusterTemp == 2){
               
               tempa = newTermination(Cluster[1], input[i]);
               Cluster2[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 3){
               
               tempa = newTermination(Cluster[2], input[i]);
               Cluster3[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 4){
               
               tempa = newTermination(Cluster[3], input[i]);
               Cluster4[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 5){
            
               tempa = newTermination(Cluster[4], input[i]);
               Cluster5[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 6){
              
               tempa = newTermination(Cluster[5], input[i]);
               Cluster6[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
                
           else if (ClusterTemp == 7){
               
               tempa = newTermination(Cluster[6], input[i]);
               Cluster7[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 8){
             
               tempa = newTermination(Cluster[7], input[i]);
               Cluster8[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 9){
              
               tempa = newTermination(Cluster[8], input[i]);
               Cluster9[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 10){
               
               tempa = newTermination(Cluster[9], input[i]);
               Cluster10[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 11){
               
               tempa = newTermination(Cluster[10], input[i]);
               Cluster11[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 12){
               
               tempa = newTermination(Cluster[11], input[i]);
               Cluster12[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 13){

               tempa = newTermination(Cluster[12], input[i]);
               Cluster13[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 14){
               
               tempa = newTermination(Cluster[13], input[i]);
               Cluster14[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 15){
               
               tempa = newTermination(Cluster[14], input[i]);
               Cluster15[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
           else if (ClusterTemp == 16){
               
               tempa = newTermination(Cluster[15], input[i]);
               Cluster16[i] = input[i];
               newterminationtemp = newterminationtemp + tempa;
           }
               i++;
               ClusterTemp = 0; // adding to reset
           } // end of the while loop
           //LOGIC GOOD ABOVE NOW
        //   cout << endl << "Current Sum of distances of clusters from points is: " << newterminationtemp <<endl;
           comparitorTemp = holderTemp - newterminationtemp;
           // TERMINATOR *****************
           if  (comparitorTemp < 0.05 && comparitorTemp > -0.05 && newcycles > 1){
               /*cout << endl << "Ending because Distortion is " << comparitorTemp << endl << "Previous sum is : " << holderTemp <<endl << "New sum is " << newterminationtemp <<endl << "Current Cycle is: " << newcycles <<endl;*/
              // saveClusterCentersToFile(input,knn);
                       
               
               /*for (int jk = 0; jk < 16; jk++){
                     cout << "Values for Cluster at END: " << jk << " : " <<  Cluster[jk].r << " " << Cluster[jk].g << " " << Cluster[jk].b << endl;
               }*/
               
               exit(0);
           }
           
           // TERMINATOR ****************
       holderTemp = newterminationtemp;
           //*****NEW CLUSTER CENTERS
           
       cout << endl << " New Cluster centers are: " <<endl<<endl;
       Cluster[0] = updateCenters(Cluster1, Cluster[0]); print(Cluster[0]);
       Cluster[1] = updateCenters(Cluster2, Cluster[1]); print(Cluster[1]);
       Cluster[2] = updateCenters(Cluster3, Cluster[2]); print(Cluster[2]);
       Cluster[3] = updateCenters(Cluster4, Cluster[3]); print(Cluster[3]);
       Cluster[4] = updateCenters(Cluster5, Cluster[4]); print(Cluster[4]);
       Cluster[5] = updateCenters(Cluster6, Cluster[5]); print(Cluster[5]);
       Cluster[6] = updateCenters(Cluster7, Cluster[6]); print(Cluster[6]);
       Cluster[7] = updateCenters(Cluster8, Cluster[7]); print(Cluster[7]);
       Cluster[8] = updateCenters(Cluster9, Cluster[8]); print(Cluster[8]);
       Cluster[9] = updateCenters(Cluster10, Cluster[9]); print(Cluster[9]);
       Cluster[10] = updateCenters(Cluster11, Cluster[10]); print(Cluster[10]);
       Cluster[11] = updateCenters(Cluster12, Cluster[11]); print(Cluster[11]);
       Cluster[12] = updateCenters(Cluster13, Cluster[12]); print(Cluster[12]);
       Cluster[13] = updateCenters(Cluster14, Cluster[13]); print(Cluster[13]);
       Cluster[14] = updateCenters(Cluster15, Cluster[14]); print(Cluster[14]);
       Cluster[15] = updateCenters(Cluster16, Cluster[15]); print(Cluster[15]);
           cout << endl;
           
       i = 0; // Being used to difer first rotation from rest
       }
}




























void saveClusterCentersToFile(dataHolder input[], int knn[]){
 ofstream myfilez;
 myfilez.open("/users/erik/desktop/Kmeans3D/abc.txt");
 // Results to write
 myfilez << " Result Output: " <<endl;
 for (int i = 0; i < 20000; i++){
 myfilez << input[i].r <<" " << input[i].g << " " << input[i].b << " Cluster: " << knn[i] << endl;
 }
myfilez.close();
}

//WORKING FINE
void print(dataHolder x){
    cout << x.r << " , " << x.g << " , " << x.b << endl;
}

//WORKING FINE
float newTermination(dataHolder object, dataHolder Cluster){
    float sum = 0;
    sum = ((Cluster.r - object.r)^2) + ((Cluster.g - object.g)^2) + ((Cluster.b - object.b)^2);
    return sum;
}

//WORKING FINE
bool readFile(dataHolder input[], string infilex)
{
ifstream infile(infilex);
   
    if(infile.fail()){
        return false;
    }
dataHolder k;
    int a = 0;
while(infile >> k.r){
    infile >> k.g >> k.b;
   // cout << k.r << " " << k.g << " " << k.b << " Number: " << a << endl; // DEBUGGING
    input[a] = k;
    a++;
    if (a > 20000){
        break;}
}
infile.close();
return true;
}

// WORKING FINE
void loadFile(dataHolder input[]){
   
    string infile("/users/erik/desktop/Kmeans3D/Original.txt");
    if(!readFile(input, infile)) // Adding Student records from text file
      {
      cout << "ERROR: Could not read the input file" << endl;
      exit(0);
      }
    //cout << "**********************************************"<<endl;  //DEBUGGING
    // for (int i = 0; i < 262144; i++){
        //cout << input[i].r <<" " << input[i].g << " " << input[i].b <<endl;
   // }
}

//WORKING FINE
void assignStartClusters(dataHolder input[], dataHolder Cluster[]){
    cout << "Storing first 16 points as cluster centers"<<endl<<endl<<endl;
    for (int i = 0; i < 16; i++){ // GOING THROUGH EACH ELEMENT
        Cluster[i] = input[i]; // assigning first 16 points as random clusters centers
    }
}

double distance(double r1, double g1, double b1, double r2, double g2, double b2){
    double x = r1 - r2;
    double y = g1 - g2;
    double n = b1 - b2;
    double disCal;
    disCal = pow(x, 2) + pow(y, 2) + pow(n, 2);
    disCal = sqrt(disCal); // not neccessary for square root
    return disCal;
}

int findSmallestElement(double arr[], int n){
    int temp = arr[0];
    for(int i = 0; i < n; i++) {
        if (temp > arr[i]) {
            temp = i;
        }
    }
    return temp;
}
