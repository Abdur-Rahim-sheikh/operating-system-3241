// 5.8.2021

// Run the following program and check what happens. Try to think why it happens.

// How to compile: $ gcc InfiniteLoop.c -o InfiniteLoop
// How to run: $ ./InfiniteLoop

int main(){
	int i;

	for (i = 0; i < 1; i--)
		;

	return 0;
}
