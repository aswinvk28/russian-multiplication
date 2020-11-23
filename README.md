## The C project

The code is written in C language. It represents a piece of code which uses fork to separate out into reduction and expansion of two numbers. 

## Reduction processs

The reduction process reduces one input to 1, and the expansion process reduces another input to a final number.

## Expansion process

The expansion process expands the number into a final number, which is then resolved by elimination into a final value that represents our Russian Multiplication.

## What is Parametric in Nature

The code contains a band of string of text which is then appended by a series of vowels and consonants. These are determined by a matrix mapping, that replaces vowel with consonants and vice versa. 

## An example table of results

|  **RM1**  |  **RM2**  |  **RM3**  |  **RM4**  |  **RM5**  |  **RM6**  |  **BLK**  |  **SUM**  |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|  **RS1**  |  **RS2**  |  **RS3**  |  **RS4**  |  **RS4**  |  **RS6**  |  **BLK**  |  **TOT**  |
|     45    |     90    |    180    |     360   |     720   |    1440   |           |    1440   |
|     32    |     16    |     8     |      4    |      2    |      1    |           |           |
|  **RS1**  |  **RS2**  |  **RS3**  |  **RS4**  |  **RS4**  |  **RS6**  |  **BLK**  |  **TOT**  |
|     32    |     64    |    128    |     256   |     512   |    1024   |           |    1440   |
|     45    |     22    |     11    |      5    |      2    |      1    |           |           |
|  **RS1**  |  **RS2**  |  **RS3**  |  **RS4**  |  **RS4**  |  **RS6**  |  **BLK**  |  **TOT**  |
|     89    |     44    |    22     |     11    |      5    |     2     |     1     |           |
|     47    |     94    |    188    |     376   |     752   |    1504   |    3008   |    4183   |

## An extract of metadata of variables, functions, pointers, arguments, data structures

|  **Variables**  |      **Functions**        |  **Pointers**   |  **Arguments**  |    **Macros**   |   **Data Structures**  |   **Properties**  |
|-----------------|---------------------------|-----------------|-----------------|-----------------|------------------------|------------------------|
|     model       |   createModel             |       msg       |     number1     |     RND_SIZE    |        red_array       |         key  |
|  reduce_array   | aggregateVowelOrConsonant |  vowel_count    |     number2     |       SIZE      |        red_count       |        data  |
|  expand_array   |        collect            | consonant_count |                 |      LENGTH     |      reduce_array      |        index |
|    number1      |         reduce            |   reduce_count  |                 |       PROB      |      expand_array      |        from  |
|    number2      |         expand            |    red_array    |                 |                 |          vowels        |         to   |
|  reduce_count   |        calc_sum           |                 |                 |                 |        consonants      |              |
|     model       |         verify            |                 |                 |                 |            rc          |              |
|    random       |      Child_Process        |                 |                 |                 |        HashTable       |              |
|     text        |     Parent_Process        |                 |                 |                 |        StickModel      |              |
|      pid        |                           |                 |                 |                 |        hashArray       |              |
|      sum        |            90             |                 |                 |                 |        stickModel      |              |
