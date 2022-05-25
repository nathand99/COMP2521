#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "textbuffer.h"

#define TRUE 1
#define FALSE 0


int main(int argc, char *argv[]) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n\0";
                 
    char line[] = "Hi\nhow\nare\nthings\n\0";
    
    char line2[] = "This\nis\na\nsentence\n\0";
                 
    TB tb1 = newTB(str);
    TB tb2 = newTB(line);
    TB tb3 = newTB(line2);
    
    // testing dumpTB
    char *dumptb1 = dumpTB(tb1, FALSE);
    char *dumptb2 = dumpTB(tb2, FALSE);
    char *dumptb3 = dumpTB(tb3, FALSE);
    assert(strcmp(dumptb1, "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n\0") == 0);
    assert(strcmp(dumptb2, "Hi\nhow\nare\nthings\n\0") == 0);
    assert(strcmp(dumptb3, "This\nis\na\nsentence\n\0") == 0);
    
    // with showLineNumbers
    char *dump1 = dumpTB (tb1, TRUE);
    assert(strcmp(dump1, "1. line 01\n"
                 "2. line 02\n"
                 "3. line 03\n"
                 "4. line 04\n"
                 "5. line 05\n"
                 "6. line 06\n"
                 "7. line 07\n"
                 "8. line 08\n"
                 "9. line 09\n"
                 "10. line 10\n\0") == 0);
    
    char *dump2 = dumpTB (tb2, TRUE);
    assert(strcmp(dump2, "1. Hi\n2. how\n3. are\n4. things\n\0") == 0);

    char *dump3 = dumpTB(tb3, TRUE);
    assert(strcmp(dump3, "1. This\n2. is\n3. a\n4. sentence\n\0") == 0);
    
    // testing linesTB
    assert(linesTB(tb1) == 10);
    assert(linesTB(tb2) == 4);
    assert(linesTB(tb3) == 4);
    
    // testing addPrefixTB
    // this should add a prefix to the first 5 lines
    addPrefixTB (tb1, 0, 4, "prefix ");
    char *tb1_addp = dumpTB(tb1, FALSE);
    assert(strcmp(tb1_addp, "prefix line 01\n"
                 "prefix line 02\n"
                 "prefix line 03\n"
                 "prefix line 04\n"
                 "prefix line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n\0") == 0);
     
    addPrefixTB (tb2, 0, 1, "hello ");
    char *tb2_addp = dumpTB(tb2, FALSE);   
    assert(strcmp(tb2_addp, "hello Hi\nhello how\nare\nthings\n\0") == 0);
    
    addPrefixTB (tb3, 3, 3, "funny ");
    char *tb3_addp = dumpTB(tb3, FALSE);   
    assert(strcmp(tb3_addp, "This\nis\na\nfunny sentence\n\0") == 0);
    
    //testing mergeTB 
    mergeTB (tb2, 0, tb3);
    char *merge1 = dumpTB(tb2, FALSE);
    assert(strcmp(merge1, "This\nis\na\nfunny sentence\nhello Hi\nhello how\nare\nthings\n\0") == 0);
     
    char line3[] = "Im\ngood\nthanks\n\0";
    char line4[] = "Random\nwords\n\0";
    TB tb4 = newTB(line3);
    TB tb5 = newTB(line4);
    mergeTB (tb5, 1, tb4);
    char *merge2 = dumpTB(tb5, FALSE);
    assert(strcmp(merge2, "Random\nIm\ngood\nthanks\nwords\n\0") == 0);
    
    mergeTB (tb5, 3, tb2);
    char *merge3 = dumpTB(tb5, FALSE);
    assert(strcmp(merge3, "Random\nIm\ngood\nThis\nis\na\nfunny sentence\nhello Hi\nhello how\nare\nthings\nthanks\nwords\n\0") == 0);
    
    //testing cutTB
    
    // cut from start
    TB tb6 = cutTB(tb5, 0, 1);
    char *cut1 = dumpTB(tb6, FALSE);
    assert(strcmp(cut1, "Random\nIm\n\0") == 0);
    char *cut2 = dumpTB(tb5, FALSE);
    assert(strcmp(cut2, "good\nThis\nis\na\nfunny sentence\nhello Hi\nhello how\nare\nthings\nthanks\nwords\n\0") == 0);
    
    // cut from end
    TB tb7 = cutTB(tb5, 8, 10);
    cut1 = dumpTB(tb7, FALSE);
    assert(strcmp(cut1, "things\nthanks\nwords\n\0") == 0);
    cut2 = dumpTB(tb5, FALSE);
    assert(strcmp(cut2, "good\nThis\nis\na\nfunny sentence\nhello Hi\nhello how\nare\n\0") == 0);
    
    //testing deleteTB
    
    // delete from start
    deleteTB(tb5, 0, 2);
    char *delete1 = dumpTB(tb5, FALSE);
    assert(strcmp(delete1, "a\nfunny sentence\nhello Hi\nhello how\nare\n\0") == 0);
    
    //delete from end
    deleteTB(tb5, 3, 4);
    char *delete2 = dumpTB(tb5, FALSE);
    assert(strcmp(delete2, "a\nfunny sentence\nhello Hi\n\0") == 0);
    
    //testing pasteTB
    
    char line5[] = "last\nline\n\0";
    TB tb8 = newTB(line5);
    pasteTB(tb5, 1, tb8);
    char *pastedump = dumpTB(tb5, FALSE);
    assert(strcmp(pastedump, "a\nlast\nline\nfunny sentence\nhello Hi\n\0") == 0);

    
    searchTB(tb5, "a");
    
    //valgrind --leak-check=full -v ./textbuffer

    return EXIT_SUCCESS;
}
