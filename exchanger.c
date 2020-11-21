#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#define N 2056
#define FILE_NAME "text.txt"
int exchange(char* i_str,char *o_str){

  int index = 0;
  while(index < strlen(i_str)){
    if(!isalpha(i_str[index]) &&i_str[index]!= 0x0a){
        o_str[index] = 0x0020;
    }else{
        o_str[index] = i_str[index];
    }
    index++;
  } 
  return 0;
}
int export(char *str,char*filename){
    FILE *fp;
    fp = fopen(filename, "w");
    fprintf(fp, str);
    fclose(fp);
}
int import(char* o_str,char *file_name){
    char str_buffer[N];
    int len  = 0;
    memset(str_buffer, '\0', sizeof(str_buffer));
    FILE *fp;
    fp = fopen(file_name, "r"); // ファイルを開く。失敗するとNULLを返す。
	if(fp == NULL) {
		printf("%s file not open!\n", file_name);
		return -1;
	}
    while(fgets(str_buffer, N, fp) != NULL) {
      len += strlen(str_buffer);
      if(len>N){
          break;
      }
      strcat(o_str,str_buffer);
	}
}
//文字の種類を検出
int alfabet_set(char* i_str,char* result,int *result_cnt){
    int def_cnt = 0;
    int index = 1;
    //0文字目
    
    result[0] = i_str[0];
    result_cnt[0] +=1;
    
    //1文字目以降
    while (index < strlen(i_str))
    {
        int j;
        for(j = 0;j<strlen(result);j++){
           //過去の文字に同じものがないかを探す
            if(tolower(i_str[index]) == result[j]){
                result_cnt[j] +=1;
                break;
            }
        }
        //見つからなかったら
        if(j==strlen(result)){
            //新しい文字の場合は過去の末尾に新しい文字を付け加える
            result[j] = i_str[index];
            result_cnt[j] +=1;
        }
        index++;
    }
    return 0;    
}
//ランキング変更
int alfabet_rank(char* i_result,int *i_result_cnt){
    //出力配列の初期化

    int i,j ;
    
    for(i = 0;i_result[i]!='\0';i++){
        for(j = i+1;i_result[j]!='\0';j++){
            if(i_result_cnt[i]<i_result_cnt[j]){
                int buff_i = i_result_cnt[i];
                char buff_c = i_result[i];
                i_result_cnt[i] = i_result_cnt[j];
                i_result[i] = i_result[j];
                i_result_cnt[j] = buff_i;
                i_result[j] = buff_c;
            }
        }    
    }
    return 0;
}
//課題4
int make_str(char *i_str,char *o_str){
    srand((unsigned int)time(NULL));
    for(int j = 0; j < strlen(i_str); j++) {
        int d = rand() % strlen(i_str) ;
        printf("%d, \n", d);
        o_str[j] = i_str[d];
    }
    return 0;
}
int main(void) {
	char str[N];
    char ex_str[N];
    
    //アルファベットの文字の種類を格納
    char ex_alfabet[N];
    //アルファベットの文字の種類の数
    int ex_alfabet_cnt[N];

    //アルファベットの文字の種類を格納
    char sort_alfabet[N];
    //アルファベットの文字の種類の数
    int sort_alfabet_cnt[N];

    //第一近似の文字列の生成
    char random_alfabet[N];
    
    //配列内の初期化
    memset(str, '\0', sizeof(str));
    memset(ex_str, '\0', sizeof(ex_str));
    memset(ex_alfabet, '\0', sizeof(ex_alfabet));
    memset(ex_alfabet_cnt, 0, sizeof(ex_alfabet_cnt));
    memset(random_alfabet, 0, sizeof(random_alfabet));
    
    //課題1
	import(str,"text.txt");
    exchange(str,ex_str);
    printf("%s\n",ex_str);
    export(ex_str,"file_no_symbol.txt");
    //課題2
    alfabet_set(ex_str,ex_alfabet,ex_alfabet_cnt);
    alfabet_rank(ex_alfabet,ex_alfabet_cnt);
    //課題4
    int index = 0;
    make_str(ex_str,random_alfabet);
    export(random_alfabet,"primary_approximation.txt");
    while (index <strlen(ex_alfabet))
    {
        printf("sort_alfabet:%c  sort_alfabet_cnt:%d\n",ex_alfabet[index],ex_alfabet_cnt[index]);
        index++;
    }
	return 0;
}