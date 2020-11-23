#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SIZE 20
#define LENGTH 100
#define PROB 0.9
#define RND_SIZE 100

char model[LENGTH] = "I like the way you play it!";
int reduce_array[SIZE];
int expand_array[SIZE];
int number1 = 0, number2 = 0;
int reduce_count = 0;

struct HashTable {
   char* key;
   char* data;
   int index;
};

struct StickModel {
   int index;
   int from;
   int to;
};

struct HashTable hashArray[SIZE];
struct StickModel stickModel[SIZE];

char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
char consonants[21] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'w', 'x', 'y', 'z'};

void createModel() {
    // replace with one vowel if there are 2 consonants
    struct HashTable ht1;
    ht1.key = "vowel";
    ht1.data = "consonant";
    ht1.index = 0;
    hashArray[0] = ht1;
    // replace with one vowel if there is one vowel
    struct HashTable ht2;
    ht2.key = "vowel";
    ht2.data = "vowel";
    ht2.index = 1;
    hashArray[1] = ht2;
    // replace with one consonant if there is one vowel
    struct HashTable ht3;
    ht3.key = "consonant";
    ht3.data = "vowel";
    ht3.index = 2;
    hashArray[2] = ht3;
    // replace with one consonant if there is one consonant
    struct HashTable ht4;
    ht4.key = "consonant";
    ht4.data = "consonant";
    ht4.index = 3;
    hashArray[3] = ht4;
    struct StickModel sm1 = {0, 1, 1};
    stickModel[0] = sm1;
    struct StickModel sm2 = {1, 1, 2};
    stickModel[1] = sm2;
    struct StickModel sm3 = {2, 1, 3};
    stickModel[2] = sm3;
    struct StickModel sm4 = {3, 1, 4};
    stickModel[3] = sm4;
}

// checks if the character is vowel or consonant
int aggregateVowelOrConsonant(char c) {
    // evaluates to 1 (true) if c is a lowercase vowel
    char isLowercaseVowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
    // evaluates to 1 (true) if c is an uppercase vowel
    char isUppercaseVowel = (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
    if (isLowercaseVowel || isUppercaseVowel)
        return 0;
    else
        return 1;
}

// aggregates the message passed in order to process the input text
void collect(char *msg, int *vowel_count, int *consonant_count, int8_t convert) {
    int vidx = convert ? 1 : 0;
    int cidx = convert ? 1 : 0;
    char c;
    strcat(model, " ");
    int random = 0;
    float probability = 0.0f;
    for(int i = 0; i < sizeof(msg)/sizeof(msg[0])+1; i++) {
        c = msg[i];
        probability = (float) (rand() % (RND_SIZE - 1 + 1) + 1) / RND_SIZE;
        if(!aggregateVowelOrConsonant(c) && (vidx >= stickModel[1].to || vidx >= stickModel[2].to) && probability <= PROB) {
            random = rand() % (5 - 1 + 1) + 1;
            msg[i] = vowels[random];
        } else if(aggregateVowelOrConsonant(c) && cidx >= stickModel[0].to && probability <= PROB) {
            random = rand() % (5 - 1 + 1) + 1;
            msg[i] = vowels[random];
        } else if(aggregateVowelOrConsonant(c) && cidx >= stickModel[3].to && probability <= PROB) {
            random = rand() % (21 - 1 + 1) + 1;
            msg[i] = consonants[random];
        }
    }
    strcat(model, msg);
    *vowel_count = vidx;
    *consonant_count = cidx;
}

// reduce must be driven by incrementing the parametric constraint
void reduce(int number, int *reduce_count, int *red_array) {
    number = (int) (number / 2);
    int is_odd = (int) (number % 2);
    if(number == 0) {
    } else if (number == 1) {
        red_array[*reduce_count] = 1;
        *reduce_count += 1;
        reduce(number, reduce_count, red_array);
    } else if (is_odd == 1) {
        red_array[*reduce_count] = 1;
        *reduce_count += 1;
        reduce(number, reduce_count, red_array);
    } else {
        red_array[*reduce_count] = 0;
        *reduce_count += 1;
        reduce(number, reduce_count, red_array);
    }
}

void output_results(int* red_array, int* exp_array, int *red_count) {
    printf("%s\n", "|  RM1  |  RM2  |  RM3  |  RM4  |  RM5  |  RM6  |  BLK  |  SUM  |");
    printf("%s\n", "|  RS1  |  RS2  |  RS3  |  RS4  |  RS4  |  RS6  |  BLK  |  TOT  |");
    int sum = 0;
    for(int i = 0; i < *red_count; i++) {
        printf("|    %d   ", exp_array[i]);
        sum += exp_array[i];
    }
    printf("|    %d    |\n", sum);
    for(int i = 0; i < *red_count; i++) {
        printf("|    %d    ", red_array[i]);
    }
    printf("|    %s    |\n", "");
}

// expand must be driven by the usage of the parametric constraint via shared memory
void expand(int *array1, int *red_array, int number, int *red_count) {
    int num = number;
    for(int i = 0; i < *red_count; i++) {
        int c = red_array[i];
        if (c == 1) {
            array1[i] = num;
        } else if(c == 0) {
            array1[i] = 0;
        }
        num *= 2;
    }
}

// calculates the sum of all elements in the array by eliminating deduplication
int calc_sum(int *array, int *red_count) {
    int sum_0 = 0;
    for(int i = 0; i < *red_count; i++) {
        sum_0 += array[i];
    }
    return sum_0;
}

// conducts tests and verifies if product and result are equal
int verify(int product, int result) {
    return product - result;
}

// accepts child processes and executes reduce
void Child_Process(int number2, int *reduce_count, int *red_array) {
  if((int) (number2 % 2) == 1) {
    red_array[0] = 0;
  }
  *reduce_count += 1;
  reduce(number2, reduce_count, red_array);
}

// accepts parent processes and executes expand
void Parent_Process(int number1, int *expand_array, int *red_array, int *red_count) {
  expand_array[0] = number1;
  expand(expand_array, red_array, number1, red_count);
}

int main(int argc, char *argv[]) {
    int stat;
    int sum = 0;
    srand(time(0));
    createModel();

    number1 = atoi(argv[1]);
    number2 = atoi(argv[2]);
    char text[10] = "hardcoded";
    int fd = open("/dev/xyz", O_CREAT | O_RDWR);
    int dt = open("/dev/dat", O_CREAT | O_RDWR);

    int vowel_count = 0;
    int consonant_count = 0;
    int8_t convert = 1;

    collect(text, &vowel_count, &consonant_count, convert);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed!\n");
        exit(-1);
    }

    if (pid == 0) {
        sleep(0.3);
        int red_array[SIZE];
        int red_count[1];
        fd = open("/dev/xyz", O_CREAT | O_RDWR);
        dt = open("/dev/dat", O_CREAT | O_RDWR);
        int ret = read(fd, (void*) red_array, sizeof(int)*SIZE);
        int retval = read(dt, (void*) red_count, sizeof(int));
        close(fd);
        close(dt);
        Parent_Process(number1, expand_array, (int*) red_array, (int*) red_count);
        sum = calc_sum(expand_array, (int*) red_count);
        printf("%s\n", model);
        output_results(reduce_array, expand_array, (int*) red_count);
    } else {
        sleep(0.1);
        Child_Process(number2, &reduce_count, reduce_array);
        int rc[1];
        rc[0] = reduce_count;
        write(fd, (void*) reduce_array, reduce_count*sizeof(int));
        write(dt, (void*) rc, sizeof(int));
        close(fd);
        close(dt);
        exit(0);
    }

    // verify the product of 2 numbers
    if(verify(number1 * number2, sum) && pid == 0) {
        fprintf(stderr, "Product failed!\n");
        exit(0);
    }

    exit(0);
}

