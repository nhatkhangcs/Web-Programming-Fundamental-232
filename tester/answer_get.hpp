#pragma once

#include <vector>
#include <string>
#include <cstdio>

struct TestCase {
  int HP1, HP2;
  int EXP1, EXP2;
  int M1, M2;
  int E1, E2, E3;
};



struct Task1Ret {
  int ret;
  int EXP1;
  int EXP2;

  void dump(const char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "ret=%d\n"
                  "EXP1=%d\n"
                  "EXP2=%d\n", ret, EXP1, EXP2);
    fclose(file);
  }

};


struct Task2Ret {
  int ret;
  int HP1;
  int EXP1;
  int M1;

  void dump(const char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "ret=%d\n"
                  "HP1=%d\n"
                  "EXP1=%d\n"
                  "M1=%d\n", ret, HP1, EXP1, M1);
    fclose(file);
  }

};


struct Task3Ret {
  int ret;
  int HP1;
  int EXP1;
  int HP2;
  int EXP2;

  void dump(const char* filename) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "ret=%d\n"
                  "HP1=%d\n"
                  "EXP1=%d\n"
                  "HP2=%d\n"
                  "EXP2%d\n", ret, HP1, EXP1, HP2, EXP2);
    fclose(file);
  }

};


struct TestCase5 {
  int nstrs;
  std::vector<std::string> strs;
};

struct TestCase4 {
  std::string s, email;
};

struct TestCase45 {
  TestCase4 test4;
  TestCase5 test5;
};


namespace true_code {

// Support functions
// Task 1
int firstMeet(int & EXP1, int & EXP2, int E1);

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2);

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3);

// Task 4
int checkPassword(const char *s, const char *email);

// Task 5
int findCorrectPassword(const char *arr_pwds[], int num_pwds);

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
}