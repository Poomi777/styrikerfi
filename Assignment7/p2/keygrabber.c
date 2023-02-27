#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dlfcn.h>
#include <stdarg.h>
#include <signal.h>


// You will have to "attack" (probe) three functions in the shared library:
// square, multiply, and reduce
// These are used in square-and-multiply modular exponentiation in RSA.
// The provided code will find the start of the functions in the shared library
// and add an offset, so you can probe a "central" part of the function that is
// used more frequently in an inner loop
// This makes it less likely to miss some access accidentely
// (you could find these offsets on your own by analysing the disassembly of the shared library)
#define LIBCRYPTO_SQUARE_FUNCTION "bi_square"
#define LIBCRYPTO_MULTIPLY_FUNCTION "bi_multiply"
#define LIBCRYPTO_REDUCE_FUNCTION "bi_subtract"

#define LIBCRYPTO_SQUARE_OFFSET 0xb2
#define LIBCRYPTO_MULTIPLY_OFFSET 0xa3
#define LIBCRYPTO_REDUCE_OFFSET 0x83

// This is the shared library
#define AXTLSLIB "/home/sty23/axtls-code/_stage/libaxtls.so.1"

// This is a placeholder for the correct key.
// The first 40 bits of the private exponent are included so you can more easily check if you are on the right path...
// The size of the key is 1024 bit
#define ORIGINALKEY "1000000011111101001110100000100000110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"


// This is a buffer to be used in the probing function
#define RESULTS_SIZE 1024*1024*16
unsigned char *results;

// Synchronization between main() and the probing thread (code provided in the template)
pthread_mutex_t stopMutex;
int stop_probing = 0;

// This function shall measure the duration of a (read) access to addr using rdtsc, and return that duration
// (FLUSH + RELOAD probe function)
unsigned long probe(void *addr) {
	// TODO - to be implemented
	(addr);
        return 0;
}


// This function shall be implemented to be used for calibartion.
// It shall call probe() 1000 times to measure the cache miss access time and calculate the minimum and average.
//
// Use some memory location that is not accessed, such as the results buffer
// 
// Just print the values using printf() and then manually adjust the threshold value.
#define THRESHOLD 500
void calibrate() {
	// TODO: to be implemented
}


// This function is executed in a separate thread while the main programming is accessing the web server.
// Here you need to place the side channel attack.
void *probe_thread(void *arg) {
	// This code in the template obtains the memory locations of square, multipl, and reduce code in the shared TLS library.
        char *dl_error;
        void *library = dlopen(AXTLSLIB, RTLD_NOW);
        if (!library) {
                fprintf(stderr,"dlopen failed: %s\n",dl_error); exit(1);
        }
        void * square_addr = dlsym(library, LIBCRYPTO_SQUARE_FUNCTION);
        if ((dl_error = dlerror()) != NULL)  {
                fprintf(stderr,"error in dlsym: %s\n",dl_error); exit(1);
        }
        void * multiply_addr = dlsym(library, LIBCRYPTO_MULTIPLY_FUNCTION);
        if ((dl_error = dlerror()) != NULL)  {
                fprintf(stderr,"error in dlsym: %s\n",dl_error); exit(1);
        }
        void * reduce_addr = dlsym(library, LIBCRYPTO_REDUCE_FUNCTION);
        if ((dl_error = dlerror()) != NULL)  {
                fprintf(stderr,"error in dlsym: %s\n",dl_error); exit(1);
        }

        square_addr   += LIBCRYPTO_SQUARE_OFFSET;
        multiply_addr += LIBCRYPTO_MULTIPLY_OFFSET;
        reduce_addr += LIBCRYPTO_REDUCE_OFFSET;

	printf("probe thread is running");
	printf("Using code addresses %p (square), %p (multiply), %p (reduce)\n", square_addr, multiply_addr, reduce_addr);

        int pos=0;  // position in results
        int iter=0; // counting iterations, not used, just for informational purposes
        while(1) {
		// This mutex-protected (for ensuring memory consistency) variable stop_probing is used to
		// indicate that the interaction with the web server has finished, so we can stop probing.
                pthread_mutex_lock(&stopMutex);
                if ( stop_probing ) {
                        break;
                }
                pthread_mutex_unlock(&stopMutex);

		/////////////////////////////////////////////////////
		// TODO
		// Here you need to add your probing code, adding 'S'/'M'/'\n' to results as required.
		/////////////////////////////////////////////////////
                iter++;
        }
	printf("Probe finishing. %d iterations, %d detected probes\n", iter, pos);
        pthread_exit(NULL);
}

int main(int argc, char **argv) {
        /* Prepare the result buffer */
        results = (unsigned char *)malloc(RESULTS_SIZE);
        if ( results == NULL ) {
                fprintf(stderr, "Error in malloc !"); exit(1);
        }
        memset(results,0,RESULTS_SIZE);

	if (argc == 2 && strcmp(argv[1],"calibrate")==0 ) {
		calibrate();
		exit(0);
	}
        if (argc != 3) {
                printf("usage:  client <IP address> <port>\n"
		       "   or:  client calibrate\n");
		exit(1);
        }


        /* Start the probing thread */
        pthread_t probe_t;
        if(pthread_create(&probe_t, NULL, probe_thread, NULL) == -1) {
                fprintf(stderr, "can't create probe thread"); exit(1);
        }

        /* Request HTTPS page from the vulnerable web server */
	/////////////////////////////////////////////////////
	// TODO: Add code to access the HTTPS server as a client
	// This code should block until the wget process terminates
	sleep(1);  // can be removed / replaced with your code
	/////////////////////////////////////////////////////

        /* Stop the probing thread */
        pthread_mutex_lock(&stopMutex);
        stop_probing = 1;
        pthread_mutex_unlock(&stopMutex);
        pthread_cancel(probe_t);

        /* Write results (maybe you want to plot that somehow or manually take a look) */
        int result_fd = open("./results.txt",O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        if (result_fd < 0 ) {
                fprintf(stderr, "Cannot open output file for writting"); exit(1);
        }
        write(result_fd,results,strlen(results));
        close(result_fd);

        /* resolve SQUARE & MULTIPLY from the results */
	printf("extracing key from results\n");
        char key [6000]={0};
	int pos = 0; // Use this to store the length of the extracted key
	///////////////////////////////////////////
	// TODO: Implement the transformation of results in a guess for the right key

	//////////////////////////////////////
	// Print your result (you should put the key as binary string in "key")
        printf("Retrieved KEY :\n %s",key);
        printf("\n Length of Retrieved Key = %d (should be 1024)",pos);
    	printf("\n Original KEY :\n %s \n", ORIGINALKEY);

	// As soon as you think you have got the right key, you can copy that into "ORIGINALKEY" above.
	// Then, on each re-run, this will print the XOR of the newly extracted key and the ORIGINALKEY.
	// If both match, this XOR will be all 0
        int ii;
        char xor_key [6000]={0};
        for(ii=0; ii < pos ; ii++)
        {
                if (key[ii] == ORIGINALKEY[ii])
                        xor_key[ii] = '0';
                else
                        xor_key[ii] = '1';
        }

        printf("\n XOR KEY :\n %s \n",xor_key);
        return 0;
}


