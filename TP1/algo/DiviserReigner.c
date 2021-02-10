#include <stdio.h>

int diviserReigner(int skyline1[][2],int skyline2[][2]){
    const int sizeSkyline = (sizeof skyline1 / sizeof skyline1[0]);
    int result[100][2] = {0};
    int h1[] = {0,0};
    int h2[] = {0,0};
    int currentHeight = 0;
    int indexSkyline1 = 0;
    int indexSkyline2 = 0;
    for(int i =0; i < sizeSkyline; i++){
        if(sizeSkyline != indexSkyline1 && skyline1[indexSkyline1][0] <= skyline2[indexSkyline2][0]){
            h1[0] = skyline1[indexSkyline1][0];
            h1[1] = skyline1[indexSkyline1][1];
            result[i][0] = h1[0];
            indexSkyline1++;
        }else if(sizeSkyline != indexSkyline2 && skyline1[indexSkyline1][0] > skyline2[indexSkyline2][0]){
            h2[0] = skyline1[indexSkyline2][0];
            h2[1] = skyline1[indexSkyline2][1];
            result[i][0] = h2[0];
            indexSkyline2++;
        }
        currentHeight = h1[1]>h2[1] ? h1[1] : h2[1];
        result[i][1] = currentHeight;

    }

    return 0;
}

int main(int argc, char *argv[]) {
    int Skyline1[5][2] = {(1, 11),  (3, 13),  (9, 0),  (12, 7),  (16, 0)};
    int Skyline2[5][2] = {(14, 3),  (19, 18), (22, 3), (23, 13),  (29, 0)};

}