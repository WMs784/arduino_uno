#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#define rep(i,n) for(int i = 0;i <(int)n;i++)

#define CS 4

// void setup_sd() {
//     Serial.begin(9600); //シリアル通信開始
//     Serial.println("Initializing SD.....");
//     pinMode(10, OUTPUT);

//     if (!SD.begin(CS)) {
//         Serial.println("not found SD");
//     } 
//     else {
//         Serial.println("SD OK");
//         File dataFile = SD.open("log.txt", FILE_WRITE);
        
//         if (dataFile) {
//          Serial.print("Writing to log.txt..."); //シリアルコンソールに値を表示
//          dataFile.close();
//          Serial.println("done");
//         } 
//         else {
//           Serial.println("dataFile write error!");
//           dataFile.close();
//     }
//     }
//     File dataFile = SD.open("log.txt", FILE_WRITE);
//     if (dataFile) {
//       Serial.println("log.txt:");

//     // read from the file until there's nothing else in it:
//     while (dataFile.available()) {
//       Serial.write(dataFile.read());
//     }
//     // close the file:
//     dataFile.close();
//     } 
//     else {
//     // if the file didn't open, print an error:
//     Serial.println("error opening log.txt");    
//     }
// }

// void loop_map(char field_map[200][100], short int length, short int width) {
//     File dataFile = SD.open("log.txt", FILE_WRITE);
//     if(dataFile){
//         while(dataFile.available()){
//             Serial.write(dataFile.read());
//         }
//     rep(i,length){
//       rep(j,width){
//         dataFile.print(field_map[i][j]);
//         }
//         dataFile.println(""); //縦200*横100の型にする
//     }
//     Serial.println("map loaded");
//     dataFile.close();
//     }
//     delay(10000);
// }

// void importing(char chunk_imp[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){
//     File dataFile = SD.open("log.txt", FILE_WRITE);
//     if(dataFile){
//         while(dataFile.available()){
//             Serial.write(dataFile.read());
//         }
//         rep(i, 11){
//             rep(j, 11){
//                 dataFile.print(chunk_imp[0][i][j]); //0-10行
//                 }
//                 dataFile.println("");
//                 }
//         for(short int i = 0;i > -11;i--){
//             rep(j, 11){
//                 dataFile.print(chunk_imp[1][i][j]);
//                 }
//                 dataFile.println(""); //11-21行
//                 }
//         for(short int i = 0;i > -11;i--){
//             for(short int j = 0;j > -11;j--){        
//                 dataFile.print(chunk_imp[2][i][j]);
//                 }
//                 dataFile.println(""); //22-32行
//                 }
//         rep(i, 11){
//             for(short int j = 0;j > -11;j--){        
//                 dataFile.print(chunk_imp[3][i][j]);
//                 }
//                 dataFile.println(""); //33-43行
//                 }
//     dataFile.close();
// }
// delay(2000);
// }

// void exporting(char chunk_map[4][11][11], short int cur_x, short int cur_y, short int rel_x, short int rel_y){     //x_limit,y_limitを超えると0を返す
//     const short int x_limit = 100;
//     const short int y_limit = 50;
//     File dataFile = SD.open("log.txt", FILE_READ);
//     char Data[200][100] = {};
//     if(dataFile){
//         while(dataFile.available()){
//           rep(i,200){
//             rep(j,100){
//             Serial.write(dataFile.read());
//             char value = dataFile.read();
//             Data[i][j] = value;
//             }
//           }
//         }
//         //vector<vector<int> > chank_map(chank_num,vector<int>(chank_num,0));
//             rep(i, 11){
//                 rep(j, 11){
//                     if(abs(i + cur_x + rel_x) <= 100 && abs(j + cur_y + rel_y) <= 50){  
//                     chunk_map[0][i][j] = Data[i + cur_x + rel_x][j + cur_y + rel_y];
//                     }
//                     else{
//                         chunk_map[0][i][j] = 0;
//                     }
//                 }
//             }
//             for(short int i = 0;i > -11;i--){
//                 rep(j, 11){
//                     if(abs(i + cur_x - rel_x) <= 100 && abs(j + cur_y + rel_y) <= 50){  
//                     chunk_map[1][i+10][j] = Data[i + cur_x - rel_x][j + cur_y + rel_y];
//                     }
//                     else{
//                         chunk_map[1][i+10][j] = 0;
//                     }
//                 }
//             }
//             for(short int i = 0;i > -11;i--){
//                 for(short int j = 0;j > -11;j--){
//                     if(abs(i + cur_x - rel_x) <= 100 && abs(j + cur_y - rel_y) <= 50){  
//                     chunk_map[2][i+10][j+10] = Data[i + cur_x - rel_x][j + cur_y - rel_y];
//                     }
//                     else{
//                         chunk_map[2][i+10][j+10] = 0;
//                     }
//                  }
//             }
//             rep(i, 11){
//                 for(short int j = 0;j > -11;j--){        
//                     if(abs(i + cur_x + rel_x) <= 100 && abs(j + cur_y - rel_y) <= 50){  
//                     chunk_map[3][i][j+10] = Data[i + cur_x + rel_x][j + cur_y - rel_y];
//                     }
//                     else{
//                         chunk_map[3][i][j+10] = 0;
//                 }
//             }
//         }
//     dataFile.close();
//     }
//     delay(2000);
// }

// #include <math.h> 
// void r_theta_table(unsigned char r_theta_map[2][15][15], short int rel_x_1, short int rel_y_1){
//     File tableFile = SD.open("table.txt", FILE_WRITE);
//     if(tableFile){
//         while(tableFile.available()){
//             Serial.write(tableFile.read());
//         }
//     const float conv = 53.715; //(180 * 90 / M_PI / 96)
//     rep(i, 15){
//         rep(j, 15){
//                 r_theta_map[0][i][j] = (i + rel_x_1)*(i + rel_x_1) + (j + rel_y_1)*(j + rel_y_1);
//                 float radian = atan((j + rel_y_1)/(i + rel_x_1));
//                 r_theta_map[1][i][j] = radian * conv;
//         }
//     }
//     rep(i, 2){
//         rep(j, 15){
//             rep(k, 15){
//                 tableFile.print(r_theta_map[i][j][k]);  //0-14行がr,15-29行がtheta             
//             }
//             tableFile.println("");
//         }
//     }
//     Serial.println("table loaded");    
//     tableFile.close();
// }
// delay(2000);
// }

// void SD_read_map(char map_memory[12][5][5], short int X[5], short int Y[5]){ //X,Yは12 map_memoryは12*5*5
//     File dataFile = SD.open("log.txt", FILE_READ);
//     char Data[200][100] = {};
//     if(dataFile){
//         while(dataFile.available()){
//             rep(i,200){
//                 rep(j,100){
//                     Serial.write(dataFile.read());
//                     char value = dataFile.read();
//                     Data[i][j] = value;
//             }
//           }
//         }
//     rep(a, 12)
//         rep(i, 5){
//             rep(j, 5){
//                 map_memory[a][i][j] = Data[X[a] + i][Y[a] + j];
//         }
//     }
//     dataFile.close();
//     }
//     delay(2000);
// }