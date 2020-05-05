#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <queue>


using namespace std;

 
    struct Widget{
        int id;
        double cost;
        double tax;
        double total;
    };

    

    // Task 1 MorkFork
    // Assumed mork is a type of animal or whatever (like a stork?)

    struct Mork{
        int id;
        string message = "Nanu nanu!";
    };

    // Create pipes to be used by parent and child
    int morkPipe[2];
    int MAX_MESSAGE_LENGTH = 30;

    int morkForkChild(){
        // Birth the mork
        Mork m;
        // Give the mork a name
        m.id = (int) getpid();

        // close read end
        close(morkPipe[0]);

        // Create string to say "I am pidNumber! Nanu nanu!"
        string contents = "I am " + to_string(m.id) + "! " + m.message;
        // Put that string in the pipe
        write(morkPipe[1], contents.c_str(), MAX_MESSAGE_LENGTH);

        // Close write end 
        close(morkPipe[1]);

        // Find a nice hole to die in #me
        exit(0);
        return 0;
    }

    
    void morkFork(int n){
        int child[n];
	    int childStatus[n];

        // open pipe
        if (pipe(morkPipe) < 0) {
		    cout << "Failed to pipe" << endl;
		    exit(1);
	    }

        // fork for each n child
        for(int i = 0; i < n; i++){
            child[i] = fork();
            if(child[i] == -1){
                cout << "An error has occured" << endl;
                return;
            }
            else if(child[i] == 0){
                childStatus[i] = morkForkChild();
                exit(0);
            }
        }

        // wait for all children to die
        for(int i = 0; i < n; i++){
            wait(NULL);
        }

        // close write pipe
        close(morkPipe[1]);

        // read from pipe
        char message[MAX_MESSAGE_LENGTH];
        while(read(morkPipe[0], message, MAX_MESSAGE_LENGTH) > 0){
            cout << "Mork mama sees her child mork: " << message << endl;
        }

    }

    





    // Task 2 MapReduce
    // Create q for threads to access
    // *** This is a little wonky, run it a couple times to get it to run properly
    queue<int> q;

    void* mapReduceThread(void* n){
        // Each thread has its own "square" to avoid race conditions
        int square = (int) n * (int) n;
        // Add square to queue
        q.push(square);
        pthread_exit(NULL);
    }

    void mapReduce(int n){
        pthread_t threads[n];
        int total = 0;

        // Create each thread and label 
        for(int i = 1; i < n+1; i++){
            cout << "Thread: " << to_string(i) << endl;
            pthread_create(&threads[i], NULL, mapReduceThread,  (void*) i);
            
        }

        // Wait for each thread to exit
        for(int i = 0; i < n; i++){
            wait(NULL);
        }

        // Add values to total until queue is empty
        while(!q.empty()){
            cout << "Square: " << q.front() << endl;
            total += q.front();
            q.pop();
        }

        // Display totals
        cout << "Total: " << to_string(total);
    }

    



    // Task 4 ProcessWidget
    // Global object of widget because I can't figure out how 
    //   to get the widget back up through the threads to parent
    Widget w;
    pthread_t costThread, taxThread, totalThread;

    void* processWidgetTotal(void*){
        w.total = w.cost + (w.cost * w.tax);

        pthread_exit(NULL);

    }

    void* processWidgetTax(void*){
        double tax = .0925;
        w.tax = tax;

        // create total thread
        pthread_create(&totalThread, NULL, processWidgetTotal, NULL);
        // link threads
        pthread_join(totalThread, NULL);
        // wait for total to die
        wait(NULL);
        // exit when complete
        pthread_exit(NULL);
    }

    void* processWidgetCost(void* cost){
        w.id = 38624;
        w.cost = *(double*) cost;

        // create tax thread
        pthread_create(&taxThread, NULL, processWidgetTax, NULL);
        // link threads
        pthread_join(taxThread, NULL);
        // wait for tax to die
        wait(NULL);
        // exit when complete
        pthread_exit(NULL);

    }

    Widget processWidget(double cost){
        // pthreads don't like casting double as void*
        double* newCost = new double(cost);
        // create cost thread
        pthread_create(&costThread, NULL, processWidgetCost, (void*) newCost);
        // link threads
        pthread_join(costThread, NULL);

        // Display all results to user
        cout << "ID: " << to_string(w.id) << endl;
        cout << "Cost: " << to_string(w.cost) << endl;
        cout << "Tax: " << to_string(w.tax) << endl;
        cout << "Total: " << to_string(w.total) << endl;

        // Return widget
        return w;
    }

    




int main(){
        int n = 5;
        double cost = 2.50;

        cout << "For testing:\n n = " << to_string(n) << "\n cost = " << to_string(cost) << endl;


        cout << "\n\n1. morkFork(n)" << endl;
        morkFork(n);

        cout << "\n\n2. mapReduce(n)" << endl;
        mapReduce(n);

        cout << "\n\n4. processWidget(cost)" << endl;
        processWidget(cost);

        return 0;
    }