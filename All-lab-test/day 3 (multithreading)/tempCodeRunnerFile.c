
void signal_handler(int c){
    // pthread_mutex_lock(&key);
    // printf("main Thread:I am forced to terminate by my thread after getting 100.\n");
    exit(-1);