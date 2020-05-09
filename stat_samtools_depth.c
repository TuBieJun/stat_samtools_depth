#include <stdio.h>
#include <string.h>
#include "khash.h"
KHASH_MAP_INIT_STR(str, unsigned int);
#define  BUFFSIZE  10240

int main(int argc, char *argv[])
{
    if(argc != 2) {
        fprintf(stderr, "usage %s <samtools_depth_result.txt>\n", argv[0]);
        return 1;
    }
    FILE *fp;
    if((fp=fopen(argv[1], "r")) == NULL ) {
        fprintf(stderr, "can'n open file: %s\n", argv[1]);
        return 2;
    }
    
    char buff[BUFFSIZE];
    int l;
    char* depth;
    khash_t(str) *h;
    khint_t k;
    h = kh_init(str);
    int absent;


    while(fgets(buff, BUFFSIZE-1, fp) != NULL) {
        l = strlen(buff);
        buff[l-1] = '\0';
        strtok(buff, "\t");
        strtok(NULL, "\t");
        depth = strtok(NULL, "\t");
        k = kh_get(str, h, depth);
        if (k==kh_end(h)) {
            k = kh_put(str, h, strdup(depth), &absent);
            kh_value(h, k) = 1;
        } else {
            kh_value(h, k) ++;
        }
    }
    for(k = kh_begin(h); k != kh_end(h); ++k) {
        if(kh_exist(h, k))
           printf("%s\t%u\n", (char*)kh_key(h, k), kh_value(h, k));
    }
    fclose(fp);
    return 0;
}