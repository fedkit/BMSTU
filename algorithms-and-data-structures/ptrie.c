#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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

typedef unsigned int uint;

typedef struct {
    bool here;
    uint count;
    uint children[26];
} trieVert;

trieVert trieVert_create(){
    trieVert ret;
    ret.here = false;
    ret.count = 0;
    for (int i = 0; i < 26; i++){
        ret.children[i] = 0;
    }
    return ret;
}

typedef struct {
    size_t len;
    size_t ready;
    size_t width;
    void* data;
} dynStorage;

typedef dynStorage vect;

vect vector_create(size_t width){
    vect ret;
    ret.len = ret.ready = 0;
    ret.width = width;
    ret.data = NULL;
    return ret;
}

void vector_delete(vect* x){
    free(x->data);
}

void vector_change_size(vect* V, size_t sz){
    if (sz <= V->ready) {
        V->len = sz;
    } else if (V->ready == 0) {
        V->len = V->ready = sz;
        V->data = calloc(sz, V->width);
    } else {
        size_t better = V->ready;
        while (better < sz){
            better *= 2;
        }
        void* new_storage = calloc(better, V->width);
        memcpy(new_storage, V->data, V->len * V->width);
        free(V->data);
        V->data = new_storage;
        V->len = sz;
        V->ready = better;
    }
}

void vector_append(vect* V, void* el){
    size_t m = V->len;
    vector_change_size(V, m + 1);
    memcpy((uint8_t*)V->data + m * V->width, el, V->width);
}

typedef vect trieVertVec;

size_t trieVertVec_construct_back(trieVertVec *V){
    assert(V->width == sizeof(trieVert));
    size_t b = V->len;
    trieVert new_one = trieVert_create();
    vector_append(V, &new_one);
    return b;
}

typedef vect uintVec;

void uintVec_push(uintVec* V, uint val){
    assert(V->width == sizeof(uint));
    vector_append(V, &val);
}

uint uintVec_pop(uintVec* V){
    assert(V->width == sizeof(uint));
    assert(V->len > 0);
    uint value = ((uint*)V->data)[V->len - 1];
    vector_change_size(V, V->len - 1);
    return value;
}

uint uintVec_peep(uintVec *V){
    assert(V->width == sizeof(uint));
    assert(V->len > 0);
    return ((uint*)V->data)[V->len - 1];
}

trieVert *ptrie_acc(trieVertVec *ptrie, uintVec *trie_path){
    uint lt = uintVec_peep(trie_path);
    return &(((trieVert*)ptrie->data)[lt]);
}

#define chStor (ptrie_acc(&ptrie, &trie_path)->children[code])

int main(){
    trieVertVec ptrie = vector_create(sizeof(trieVert));
    uintVec trie_path = vector_create(sizeof(uint)); 
    assert(trieVertVec_construct_back(&ptrie) == 0);

    char arg_buff[100000];
    while (true){
        int cmdL = getwC(arg_buff, 60);
        assert(cmdL > 0);
        assert(trie_path.len == 0);
        if (arg_buff[0] == 'I'){
            uint N = getwC(arg_buff, 100000);
            assert(N > 0);

            uint L = 0;
            uintVec_push(&trie_path, 0);  
            while (L < N){
                int code = arg_buff[L] - 'a';
                assert(code < 26);
                if (!chStor){
                    uint new_one = trieVertVec_construct_back(&ptrie);
                    assert(new_one);
                    chStor = new_one;
                }
                uintVec_push(&trie_path, chStor);
                L++;
            }
            if (!(ptrie_acc(&ptrie, &trie_path)->here)){
                ptrie_acc(&ptrie, &trie_path)->here = 1;
                while (trie_path.len > 0){
                    ptrie_acc(&ptrie, &trie_path)->count++;
                    uintVec_pop(&trie_path);
                }
            } else {
                vector_change_size(&trie_path, 0);
            }
        } else if (arg_buff[0] == 'D'){
            uint N = getwC(arg_buff, 100000);
            assert(N > 0);

            uint L = 0;
            uintVec_push(&trie_path, 0); 
            while (L < N){
                int code = arg_buff[L] - 'a';
                assert(code < 26);
                assert(chStor != 0);
                uintVec_push(&trie_path, chStor);
                L++;
            }
            assert(ptrie_acc(&ptrie, &trie_path)->here == 1);
            ptrie_acc(&ptrie, &trie_path)->here = 0;
            while (trie_path.len > 0){
                assert(ptrie_acc(&ptrie, &trie_path)->count > 0);
                ptrie_acc(&ptrie, &trie_path)->count--;
                uintVec_pop(&trie_path);
            }
        } else if (arg_buff[0] == 'P'){
            uint N = getwC(arg_buff, 100000);
            assert(N > 0);
            bool no_path = false;
            uint L = 0;
            uintVec_push(&trie_path, 0); 
            while (L < N){
                int code = arg_buff[L] - 'a';
                assert(code < 26);
                if (!chStor){
                    no_path = true;
                    break;
                }
                uintVec_push(&trie_path, chStor);
                L++;
            }
            uint answer = no_path ? 0 : (ptrie_acc(&ptrie, &trie_path)->count);
            printf("%u\n", answer);
            vector_change_size(&trie_path, 0);
        } else if (arg_buff[0] == 'Q'){
        } else {
            break;
        }
    }
    vector_delete(&ptrie);
    vector_delete(&trie_path);
}


