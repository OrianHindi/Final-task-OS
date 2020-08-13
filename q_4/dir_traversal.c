//
// Created by orian on 04/08/2020.
//

#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * fpath -> the path for the file.
 * sb-> stat struct with metadata on the file.
 * tflag -> the type of the file.
 * ftbwbuff -> for base and level of the file.
 */

static int display_info(const char* fpath , const struct stat* sb,int tflag, struct FTW* ftbwbuff){
        if(tflag== FTW_SL) return 0;
        printf("%s\t %ld \t %s \n",(tflag == FTW_D) ?   "D"   : (tflag == FTW_DNR) ? "DNR" :
        (tflag == FTW_DP) ?  "DP"  : (tflag == FTW_F) ?   "F" : "NS"
       ,sb->st_ino,fpath+ftbwbuff->base);
        return 0;
    }


int main(int argc, char* argv[]){
    if(nftw((argc<2) ? "." : argv[1],display_info,20,FTW_PHYS)== -1 ){
        perror("Failed nftw.");
        exit(EXIT_FAILURE);
    }
    return 0;
}
