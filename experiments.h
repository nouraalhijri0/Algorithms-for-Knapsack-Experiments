//
//  experiments.h
//  knapsack
//
//  Created by Noura Alhajry on 13/04/1444 AH.
//

#ifndef experiments_h
#define experiments_h
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

int experiments = 1000;
std::string path = ".../exp"; //define your experiments path

void initialize_data(int N, int C, int *uncorr_w, int *uncorr_v, int *corr_w, int *corr_v, int *scorr_w, int *scorr_v){
    
    for (int i=0; i<N; i++){
        uncorr_w[i] = rand() % C + 1;
        uncorr_v[i] = rand() % C + 1;

        corr_w[i] = rand() % C + 1;
        corr_v[i] = std::max(1, rand() % (C/5) + 1 + int(corr_w[i] - C/10));
        
        scorr_w[i] = (rand() % C + 1);
        scorr_v[i] = scorr_w[i] + C/10;
        
    }
    
}


void test_variables(){
    int N = 40, C=N*5;
    int uncorrelated_values[N], uncorrelated_weights[N], correlated_values[N], correlated_weights[N], strongly_correlated_values[N], strongly_correlated_weights[N];
    
    initialize_data(N, C, uncorrelated_weights, uncorrelated_values, correlated_weights, correlated_values, strongly_correlated_weights, strongly_correlated_values);

    
    std::ofstream uncorr_var (path + "/uncorr_var.txt"); uncorr_var << "weight\tvalues" << std::endl;
    for (int i=0; i<N; i++) uncorr_var << uncorrelated_weights[i] << "\t" << uncorrelated_values[i]  <<std::endl;
    uncorr_var.close();
    
    std::ofstream corr_var (path + "/corr_var.txt"); corr_var << "weight\tvalues" << std::endl;
    for (int i=0; i<N; i++) corr_var << correlated_weights[i] << "\t" << correlated_values[i]  <<std::endl;
    corr_var.close();
    
    std::ofstream scorr_var (path + "/scorr_var.txt"); scorr_var << "weight\tvalues" << std::endl;
    for (int i=0; i<N; i++) scorr_var << strongly_correlated_weights[i] << "\t" << strongly_correlated_values[i]  <<std::endl;
    scorr_var.close();
}

void simple_example(){ //this example has created by Bradley
    int N = 40, print_F = 0, print_res = 1, C = N*50;
    
    int uncorrelated_values[N], uncorrelated_weights[N], correlated_values[N], correlated_weights[N], strongly_correlated_values[N], strongly_correlated_weights[N];

    // initialize all data instances
    initialize_data(N, C, uncorrelated_weights, uncorrelated_values, correlated_weights, correlated_values, strongly_correlated_weights, strongly_correlated_values);
    
    
    Knap K_dynamic_uncorr, K_greedy_uncorr, K_dynamic_corr, K_greedy_corr, K_dynamic_scorr, K_greedy_scorr;

    // There are 6 arguments for the Knapsack_dynamic and 5 for Knapsack_greedy
    // C (float) is the weight limit
    // N (int) is the number of objects
    // values (float*) is an array with all the values for the objects
    // weights (float*) is an array with all the weights for the objects
    // print_F (int) indicates whether or not to print the intermediate matrix
    // print_res (int) indicates whether or not to print within the function
    
    
    //--------Uncorrelated data instances--------
    fprintf(stdout, "****************** Uncorrelated data instances ******************\n");

    K_dynamic_uncorr = Knapsack_dynamic(C, N, uncorrelated_values, uncorrelated_weights, print_F, print_res);

    K_greedy_uncorr = Knapsack_greedy(C, N, uncorrelated_values, uncorrelated_weights, print_res);
    
    //--------Correlated data instances--------
    fprintf(stdout, "\n****************** Correlated data instances ******************\n");
    
    K_dynamic_corr = Knapsack_dynamic(C, N, correlated_values, correlated_weights, print_F, print_res);

    K_greedy_corr = Knapsack_greedy(C, N, correlated_values, correlated_weights, print_res);
    
    //--------Strongly correlated data instances--------
    fprintf(stdout, "\n****************** Strongly correlated data instances ******************\n");
    
    K_dynamic_scorr = Knapsack_dynamic(C, N, strongly_correlated_values, strongly_correlated_weights, print_F, print_res);

    K_greedy_scorr = Knapsack_greedy(C, N, strongly_correlated_values, strongly_correlated_weights, print_res);
    
}


void measure_time(){
    int n_items[experiments];
    float g_time_uncorr[experiments], g_time_corr[experiments], g_time_scorr[experiments],
        d_time_uncorr[experiments], d_time_corr[experiments], d_time_scorr[experiments];
    
    Knap K_dynamic_uncorr, K_greedy_uncorr, K_dynamic_corr, K_greedy_corr, K_dynamic_scorr, K_greedy_scorr;
    
    for(int i=0; i<experiments; i++) n_items[i] = i+1; //generates n items
    for(int i=0; i<experiments; i++){//experiments with different number of items and c
        int N = n_items[i], print_F = 0, print_res = 1, C = (i+1)*5;
        int uncorrelated_values[N], uncorrelated_weights[N], correlated_values[N], correlated_weights[N], strongly_correlated_values[N], strongly_correlated_weights[N];

        // initialize all data instances
        initialize_data(N, C, uncorrelated_weights, uncorrelated_values, correlated_weights, correlated_values, strongly_correlated_weights, strongly_correlated_values);
        
        fprintf(stdout, "****************** Uncorrelated data instances ******************\n");
        K_dynamic_uncorr = Knapsack_dynamic(C, N, uncorrelated_values, uncorrelated_weights, print_F, print_res);
        K_greedy_uncorr = Knapsack_greedy(C, N, uncorrelated_values, uncorrelated_weights, print_res);
        d_time_uncorr[i] = K_dynamic_uncorr.time;
        g_time_uncorr[i] = K_greedy_uncorr.time;
        fprintf(stdout, "****************** Correlated data instances ******************\n");
        K_dynamic_corr = Knapsack_dynamic(C, N, correlated_values, correlated_weights, print_F, print_res);
        K_greedy_corr = Knapsack_greedy(C, N, correlated_values, correlated_weights, print_res);
        d_time_corr[i] = K_dynamic_corr.time;
        g_time_corr[i] = K_greedy_corr.time;
        fprintf(stdout, "****************** Strongly correlated data instances ******************\n");
        K_dynamic_scorr = Knapsack_dynamic(C, N, strongly_correlated_values, strongly_correlated_weights, print_F, print_res);
        K_greedy_scorr = Knapsack_greedy(C, N, strongly_correlated_values, strongly_correlated_weights, print_res);
        d_time_scorr[i] = K_dynamic_scorr.time;
        g_time_scorr[i] = K_greedy_scorr.time;
    }
    // print n_items and time
    // save the experiment result to a txt file
    
    std::ofstream D_uncorr_time (path + "/D_uncorr_time.txt");
    D_uncorr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) D_uncorr_time << n_items[i] << "\t" << d_time_uncorr[i] << "\t" << ((i+1)*5) <<std::endl;
    D_uncorr_time.close();
    
    std::ofstream G_uncorr_time (path + "/G_uncorr_time.txt");
    G_uncorr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) G_uncorr_time << n_items[i] << "\t" << g_time_uncorr[i] << "\t" << ((i+1)*5) <<std::endl;
    G_uncorr_time.close();
    
    std::ofstream D_corr_time (path + "/D_corr_time.txt");
    D_corr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) D_corr_time << n_items[i] << "\t" << d_time_corr[i] << "\t" << ((i+1)*5) <<std::endl;
    D_corr_time.close();
    
    std::ofstream G_corr_time (path + "/G_corr_time.txt");
    G_corr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) G_corr_time << n_items[i] << "\t" << g_time_corr[i] << "\t" << ((i+1)*5) <<std::endl;
    G_corr_time.close();
    
    std::ofstream D_scorr_time (path + "/D_scorr_time.txt");
    D_scorr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) D_scorr_time << n_items[i] << "\t" << d_time_scorr[i] << "\t" << ((i+1)*5) <<std::endl;
    D_scorr_time.close();
    
    std::ofstream G_scorr_time (path + "/G_scorr_time.txt");
    G_scorr_time << "n_items\ttime\tcapacity" << std::endl;
    for(int i=0; i<experiments; i++) G_scorr_time << n_items[i] << "\t" << g_time_scorr[i] << "\t" << ((i+1)*5) <<std::endl;
    G_scorr_time.close();
    
    fprintf(stdout, "The results of time measurement has been saved to the files!\n");
}

void measure_accuracy(){
    int n_items[experiments];
    float g_acc_uncorr[experiments], g_acc_corr[experiments], g_acc_scorr[experiments];
    
    Knap K_dynamic_uncorr, K_greedy_uncorr, K_dynamic_corr, K_greedy_corr, K_dynamic_scorr, K_greedy_scorr;
    
    for(int i=0; i<experiments; i++) n_items[i] = i+1; //generates n items
    for(int i=0; i<experiments; i++){//experiments with different number of items and c
        int N = n_items[i], print_F = 0, print_res = 1, C = (i+1)*5;
        int uncorrelated_values[N], uncorrelated_weights[N], correlated_values[N], correlated_weights[N], strongly_correlated_values[N], strongly_correlated_weights[N];

        // initialize all data instances
        initialize_data(N, C, uncorrelated_weights, uncorrelated_values, correlated_weights, correlated_values, strongly_correlated_weights, strongly_correlated_values);
        
        fprintf(stdout, "****************** Uncorrelated data instances ******************\n");
        K_dynamic_uncorr = Knapsack_dynamic(C, N, uncorrelated_values, uncorrelated_weights, print_F, print_res);
        K_greedy_uncorr = Knapsack_greedy(C, N, uncorrelated_values, uncorrelated_weights, print_res);
        g_acc_uncorr[i] = K_greedy_uncorr.total_value / K_dynamic_uncorr.total_value;

        fprintf(stdout, "****************** Correlated data instances ******************\n");
        K_dynamic_corr = Knapsack_dynamic(C, N, correlated_values, correlated_weights, print_F, print_res);
        K_greedy_corr = Knapsack_greedy(C, N, correlated_values, correlated_weights, print_res);
        g_acc_corr[i] = K_greedy_corr.total_value / K_dynamic_corr.total_value;
        
        fprintf(stdout, "****************** Strongly correlated data instances ******************\n");
        K_dynamic_scorr = Knapsack_dynamic(C, N, strongly_correlated_values, strongly_correlated_weights, print_F, print_res);
        K_greedy_scorr = Knapsack_greedy(C, N, strongly_correlated_values, strongly_correlated_weights, print_res);
        g_acc_scorr[i] = K_greedy_scorr.total_value / K_dynamic_scorr.total_value;
        
    }
    //print n_items and time
    // I used this printing format to make copy-paste to R easier [R for plotting]
    
    // save the experiment result to a txt file
    
    std::ofstream G_uncorr_acc (path + "/G_uncorr_acc.txt");
    G_uncorr_acc << "n_items\tacc" << std::endl;
    for(int i=0; i<experiments; i++) G_uncorr_acc << n_items[i] << "\t" << (g_acc_uncorr[i]*100) << std::endl;
    G_uncorr_acc.close();
    
    std::ofstream G_corr_acc (path + "/G_corr_acc.txt");
    G_corr_acc << "n_items\tacc" << std::endl;
    for(int i=0; i<experiments; i++) G_corr_acc << n_items[i] << "\t" << (g_acc_corr[i]*100) << std::endl;
    G_corr_acc.close();
    
    std::ofstream G_scorr_acc (path + "/G_scorr_acc.txt");
    G_scorr_acc << "n_items\tacc" << std::endl;
    for(int i=0; i<experiments; i++) G_scorr_acc << n_items[i] << "\t" << (g_acc_scorr[i]*100) << std::endl;
    G_scorr_acc.close();
    
    fprintf(stdout, "The results of accuracy measurement has been saved to the files!\n");
    
}

void measure_misc(){
    
}

#endif /* experiments_h */
