//
//  knapsack.h
//  knapsack
//
//  Created by Noura Alhajry on 10/04/1444 AH.
//

#ifndef knapsack_h
#define knapsack_h

#include <stdio.h>
#include <stdlib.h> // For exit() and struct
#include <time.h> // For the random example and timing

typedef struct{
  float total_value;
  int total_weight;
  int *objects;
  float **Fmat;
  float time;
} Knap;

Knap Knapsack_greedy(int C, int N, int *values, int *weights, int print_res);

Knap Knapsack_dynamic(int C, int N, int *values, int *weights, int print_F, int print_res);

Knap Knapsack_greedy(int C, int N, int *values, int *weights, int print_res){

  fprintf(stdout, "\n=====================================\n");
  fprintf(stdout, "Knapsack: Greedy Algorithm\n");
  fprintf(stdout, "=====================================\n");

  float P[N], Pi;
  int O[N], I[N], j1, j2, j, i, k;
  Knap K;
  clock_t START_TIME, END_TIME;

  // Check whether the inputs are correct.
  // Check whether C is positive.
  if(C <= 0){
    fprintf(stdout, "C is not positive!");
    exit(0);
  }
  // Check whether N is positive.
  if(N <= 0){
    fprintf(stdout, "N is not positive!");
    exit(1);
  }

  // Description of the problem
  if(print_res){
    fprintf(stdout, "Description of the problem:\n");
    fprintf(stdout, "We have %d objects and the weight limit is %d.\n", N, C);
    fprintf(stdout, "The values of the objects are: ");
    for(int i=0; i<N-1; i++) fprintf(stdout, "%d, ", values[i]);
    fprintf(stdout, "%d.\n", values[N-1]);
    fprintf(stdout, "The weights of the objects are: ");
    for(int i=0; i<N-1; i++) fprintf(stdout, "%d, ", weights[i]);
    fprintf(stdout, "%d.\n", weights[N-1]);
    fprintf(stdout, "=====================================\n");
  }

  // Greedy algorithm
  START_TIME = clock();
  O[0] = 0;
  for(i=0; i<N; i++){
    if(weights[i] == 0){
      fprintf(stdout, "The %d-th item has weight zero!", i);
      exit(-1);
    }
    Pi = values[i] / weights[i];
    P[i] = Pi;
    if(Pi >= P[O[0]]){
      j = 0;
    }else if(Pi <= P[O[i-1]]){
      j = i;
    }else{
      j1 = 0; j2 = i-1;
      while(1){
        if(j1 == j2 - 1){
          if(Pi > P[O[j1]]){
            j = j1 - 1; break;
          }else if(Pi >= P[O[j2]]){
            j = j2; break;
          }else{
            j = j2 + 1; break;
          }
        }else if(Pi <= P[O[(j1+j2)/2]]){
          j1 = (j1 + j2) / 2;
        }else if(Pi >= P[O[(j1+j2)/2]]){
          j2 = (j1 + j2) / 2;
        }
      }
    }
    for(k=i; k>j; k--){
      O[k] = O[k-1];
    }
    O[j] = i;
    //printf("P[O] = ");
    //for(int h=0;h<=i;h++) printf("%.1f ", P[O[h]]);
    //printf("\n");
  }

  //printf("\n\n\nP[O] = ");
  //for(int h=0;h<N;h++) printf("%.1f ", P[O[h]]);
  //printf("\nO = ");
  //for(int h=0;h<N;h++) printf("%d ", O[h]);

  int ind = 0;
  int accumulated_weight = 0;
  float accumulated_value = 0;
  while(ind < N && accumulated_weight <= C - weights[O[ind]]){
    //I[O[ind]] = 1;
    accumulated_weight += weights[O[ind]];
    accumulated_value += values[O[ind]];
    ind++;
  }
  END_TIME = clock();

  // print results
  if(print_res) fprintf(stdout, "Solution:\nThe optimal value is: %.1f. The total weight is: %d. \nOne possible combination is to include object ", accumulated_value, accumulated_weight);
  k = 0;
  int *obj = (int *)malloc(ind * sizeof(int));
  for(i=0; i<ind; i++){
    if(k == 0){
      obj[i] = O[i]+1;
      if(print_res) fprintf(stdout, "%d", O[i]+1);
      k++;
    }else{
      obj[i] = O[i]+1;
      if(print_res) fprintf(stdout, ", %d", O[i]+1);
    }
  }
  if(print_res) fprintf(stdout, ".\n");

  // Calculate time
  float REAL_TIME = (float) (END_TIME - START_TIME) / (CLOCKS_PER_SEC/1000);
  if(print_res){
    fprintf(stdout, "=====================================\n");
    printf("Performance:\nElapsed time = %f milliseconds\n", REAL_TIME);
    fprintf(stdout, "=====================================\n\n");
  }

  // return results
  K.total_value = accumulated_value;
  K.total_weight = accumulated_weight;
  K.objects = obj;
  K.Fmat = NULL;
  K.time = REAL_TIME;
  return K;
}

Knap Knapsack_dynamic(int C, int N, int *values, int *weights, int print_F, int print_res){

  fprintf(stdout, "\n=====================================\n");
  fprintf(stdout, "Knapsack: Dynamic Algorithm\n");
  fprintf(stdout, "=====================================\n");

  float previous_best, current_best, **F = (float**)malloc((C+1) * sizeof(float*));
  int c, n, I[N];
  Knap K;
  clock_t START_TIME, END_TIME;

  // Check whether the inputs are correct.
  // Check whether C is positive.
  if(C <= 0){
    fprintf(stdout, "C is not positive!");
    exit(0);
  }
  // Check whether N is positive.
  if(N <= 0){
    fprintf(stdout, "N is not positive!");
    exit(1);
  }

  // Description of the problem
  if(print_res){
    fprintf(stdout, "Description pf the problem:\n");
  fprintf(stdout, "We have %d objects and the weight limit is %d.\n", N, C);
  fprintf(stdout, "The values of the objects are: ");
  for(int i=0; i<N-1; i++) fprintf(stdout, "%d, ", values[i]);
  fprintf(stdout, "%d.\n", values[N-1]);
  fprintf(stdout, "The weights of the objects are: ");
  for(int i=0; i<N-1; i++) fprintf(stdout, "%d, ", weights[i]);
  fprintf(stdout, "%d.\n", weights[N-1]);
  fprintf(stdout, "=====================================\n");
  }

  START_TIME = clock();
  // Create the F matrix and let the 1st row & column be zero.
  for(c = 0; c <= C; c++){
    F[c] = (float*)malloc((N+1) * sizeof(float));
    F[c][0] = 0;
  }
  for(n = 0; n <= N; n++) F[0][n] = 0;
  
  // int num_of_comp_for_the_mat = 0;
  // Dynamically fill the matrix
  for(c = 1; c <= C; c++){
    for(n = 1; n <= N; n++){
      if(weights[n-1] == 0){
        fprintf(stdout, "The %d-th object has weight zero!", n-1);
        exit(0);
      }
      // num_of_comp_for_the_mat++;
      if(n == 0 || c == 0){
        F[c][n] = 0;
      }else if(weights[n-1] <= c){
        // num_of_comp_for_the_mat++;
        previous_best = F[c][n-1];
        current_best = values[n-1] + F[c-weights[n-1]][n-1];
        // num_of_comp_for_the_mat++;
        if(previous_best >= current_best){
          // num_of_comp_for_the_mat++;
          F[c][n] = previous_best;
        }else{
          F[c][n] = current_best;
        }
      }else{
        // num_of_comp_for_the_mat++;
        F[c][n] = F[c][n-1];
      }
    }
  }

  // fprintf(stdout, "The number of comparisons is: %d", num_of_comp_for_the_mat);
  // Print the F matrix after creation
  if(print_F){
    fprintf(stdout, "\nThe dynamic matrix is:\n");
    for(c=0; c<=C; c++){
      for(n=0; n<=N; n++){
        if(n == 0){
          fprintf(stdout, "%d\t||\t%.1f\t", c, F[c][n]);
        }else{
          fprintf(stdout, "%.1f\t", F[c][n]);
        }
      }
      fprintf(stdout, "\n");
    }
  }

  // Find a path back to the starting point (find one possible solution)
  c = C; n = N;
  while(c != 0 && n != 0 && F[c][n] != 0){
    // fprintf(stdout, "c = %d, n = %d, F[c][n] = %d\n", c, n, F[c][n]);
    if(weights[n-1] <= c){
      previous_best = F[c][n-1];
      current_best = values[n-1] + F[c-weights[n-1]][n-1];
      if(previous_best > current_best){
        n--;
        I[n] = 0;
      }else{
        c -= weights[n-1];
        n--;
        I[n] = 1;
      }
    }else{
      n--;
      I[n] = 0;
    }
  }
  // fprintf(stdout, "(OUT OF WHILE) c = %d, n = %d, F[c][n] = %d\n", c, n, F[c][n]);
  if(n > 0){
    for(int i=0; i<n; i++) I[i] = 0;
  }
  // for(int i=0; i<N; i++) fprintf(stdout, "%d ", I[i]);

  END_TIME = clock();

  // objects to include
  int accumulated_weight = 0;
  int max_num = 0;
  for(int i=0; i<N; i++)
    if(I[i] == 1){
      accumulated_weight += weights[i];
      max_num++;
    }
  int *obj = (int *)malloc(max_num * sizeof(int));
  int k = 0;
  for(int i=0; i<N; i++)
    if(I[i] == 1){
      obj[k] = i;
      k++;
    }

  // print results
  if(print_res){
    fprintf(stdout, "Solution:\nThe optimal value is: %.1f. The total weight is: %d.\nOne possible combination is to include object ", F[C][N], accumulated_weight);
    int k=0;
    for(int i=0; i<max_num; i++){
      if(k == 0){
        fprintf(stdout, "%d", obj[i]);
        k++;
      }else{
        fprintf(stdout, ", %d", obj[i]);
      }
    }
    fprintf(stdout, ".\n");
  }

  // Calculate time
  float REAL_TIME = (float) (END_TIME - START_TIME) / (CLOCKS_PER_SEC/1000);
  if(print_res){
    fprintf(stdout, "=====================================\n");
    printf("Performance:\nElapsed time = %f milliseconds\n", REAL_TIME);
    fprintf(stdout, "=====================================\n\n");
  }

  // return results
  K.total_value = F[C][N];
  K.total_weight = accumulated_weight;
  K.objects = obj;
  K.Fmat = F;
  K.time = REAL_TIME;
  return K;
}


#endif /* knapsack_h */
