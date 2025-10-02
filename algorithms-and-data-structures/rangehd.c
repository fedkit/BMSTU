#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char lett_par_f; 

lett_par_f fw_add(lett_par_f X, lett_par_f Y){
    return (X & 1) ^ (Y & 1);
}

unsigned int fw_gen(unsigned int i){
    return (i + 1) & i; 
}

lett_par_f binIntTr_rangeadd(int n, lett_par_f* binIntTr, int len){
    lett_par_f summa = 0;  
    while (len) {
        len--;
        summa = fw_add(summa, binIntTr[len]);
        len = fw_gen(len);
    }
    return summa;
}

lett_par_f binIntTr_rangeadd_unstick(int n, lett_par_f* binIntTr, int L, int R){
    return binIntTr_rangeadd(n, binIntTr, R) - binIntTr_rangeadd(n, binIntTr, L);
}

void sum_buffers_update(int n, lett_par_f* binIntTr, int I, lett_par_f value){
    int tmp = I;
    while (tmp < n){
        binIntTr[tmp] = fw_add(binIntTr[tmp], value);
        tmp = (tmp + 1) | tmp; 
    }
}

int getwC(char* buffer, int buff_sz){
    bool recording = false;
    int written = 0;
    while (true){
        int ch = getc(stdin);
        if (ch == EOF){
            return written;
        }
        if (ch < 33){
            if (recording){
                return written;
            }
        } else {
            assert(written < buff_sz);
            recording = true;
            buffer[written] = ch;
            written++;
        }
    }
}


int main(){
    char input_line[1000001];
    int n = getwC(input_line, 1000000);
    if (!n){
        fprintf(stderr, "Oshibka\n");
        exit(1);
    }
    int bukvi = 26; 
    lett_par_f* fenwiki[bukvi];  
    for (int j = 0; j < bukvi; j++){
        fenwiki[j] = (lett_par_f*)calloc(n, sizeof(lett_par_f));
    }
    for (int i = 0; i < n; i++){
        int ltr = input_line[i] - 'a';
        assert(0 <= ltr && ltr < bukvi);
        sum_buffers_update(n, fenwiki[ltr], i, 1);  
    }
    char cmd_buf[1000001];
    while (true){
        int cmd_sz = getwC(cmd_buf, 40);
        assert(cmd_sz);
        if (cmd_buf[0] == 'H'){
            int L, R;
            scanf("%d", &L);
            scanf("%d", &R);
            assert(L <= R && ++R <= n);
            int misspaired = 0;
            for (int ltr = 0; ltr < bukvi; ltr++){
                if (binIntTr_rangeadd_unstick(n, fenwiki[ltr], L, R)){
                    misspaired++;
                }
            }
            if ((R - L) % 2 == misspaired){
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        } else if (cmd_buf[0] == 'U'){
            int Left;
            scanf("%d", &Left);
            int Arg_sz = getwC(cmd_buf, 1000000);
            assert(Arg_sz);
            assert(Left + Arg_sz - 1 < n);
            for (int i = 0; i < Arg_sz; i++){
                if (input_line[Left + i] != cmd_buf[i]){
                    sum_buffers_update(n, fenwiki[input_line[Left + i] - 'a'], Left + i, 1);
                    sum_buffers_update(n, fenwiki[cmd_buf[i] - 'a'], Left + i, 1);
                    input_line[Left + i] = cmd_buf[i]; 
                }
            }
        } else {
            break;
        }
    }
    for (int i = 0; i < bukvi; i++){
        free(fenwiki[i]);
    }
    return 0;
}
