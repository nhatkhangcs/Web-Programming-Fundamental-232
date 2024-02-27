#include "study_in_pink1.cpp"
#include "answer_get.hpp"
#include <random>

TestCase gentask123() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Random HP1, HP2
    std::uniform_int_distribution<int> distributionHP(-250, 750);
    int HP1 = distributionHP(gen);
    int HP2 = distributionHP(gen);
    // Random EXP1, EXP2
    std::uniform_int_distribution<int> distributionEXP(-250, 750);
    int EXP1 = distributionEXP(gen);
    int EXP2 = distributionEXP(gen);
    // Random M1, M2
    std::uniform_int_distribution<int> distributionM(-500, 3500);
    int M1 = distributionM(gen);
    int M2 = distributionM(gen);
    // Random E1, E2, E3
    std::uniform_int_distribution<int> distributionE(-50, 150);
    int E1 = distributionE(gen);
    int E2 = distributionE(gen);
    int E3 = distributionE(gen);
    return {
      HP1, HP2,
      EXP1, EXP2,
      M1, M2,
      E1, E2, E3
    };
}


template<typename Task_t>
Task1Ret runTask1(TestCase test, Task_t Task) {
  int ret = Task(test.EXP1, test.EXP2, test.E1);
  return { ret, test.EXP1, test.EXP2 };
}


template<typename Task_t>
Task2Ret runTask2(TestCase test, Task_t Task) {
  int ret = Task(test.HP1, test.EXP1, test.M1, test.E2);
  return { ret, test.HP1, test.EXP1, test.M1 };
}


template<typename Task_t>
Task3Ret runTask3(TestCase test, Task_t Task) {
  int ret = Task(test.HP1, test.EXP1, test.HP2, test.EXP2, test.E3);
  return { ret, test.HP1, test.EXP1, test.HP2, test.EXP2};
}


#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

class Password {
public:
    static bool isSpecial(char ch) {
        std::string special_chars = "@!$%#";
        return special_chars.find(ch) != std::string::npos;
    }

    static int specialCount(const std::string& input) {
        int count = 0;
        for (char ch : input) {
            if (isSpecial(ch))
                count++;
        }
        return count;
    }
};

int checkPassword(const std::string& s, const std::string& email) {
    // cout << s << " " << email << "\n";
    std::string se = email.substr(0, email.find('@'));
    if (s.length() < 8 || s.length() > 20) {
        return s.length() < 8 ? -1 : -2;
    }

    size_t idx = s.find(se);
    if (idx != std::string::npos) {
        return -(300 + static_cast<int>(idx));
    }

    for (size_t i = 0; i < s.length() - 2; ++i) {
        if (s[i] == s[i + 1] && s[i + 1] == s[i + 2]) {
            return -(400 + static_cast<int>(i));
        }
    }

    //cout << "[+] Generating special count..." << Password::specialCount(s) << "\n";

    if (Password::specialCount(s) == 0) {
        return -5;
    }

    for (size_t idx = 0; idx < s.length(); ++idx) {
        if (!isalnum(s[idx]) && !Password::isSpecial(s[idx])) {
            return static_cast<int>(idx);
        }
    }

    return -10;
}

int findCorrectPassword(const std::vector<std::string>& arr_pwds) {
    std::unordered_map<std::string, int> dct;
    for (const auto& pwd : arr_pwds) {
        dct[pwd]++;
    }

    auto compare = [](const auto& a, const auto& b) {
        if (a.second == b.second) {
            return a.first.length() > b.first.length();
        }
        return a.second > b.second;
    };

    auto result = std::max_element(dct.begin(), dct.end(), compare);
    return std::distance(arr_pwds.begin(), std::find(arr_pwds.begin(), arr_pwds.end(), result->first));
}



TestCase45 gentask45() {
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string special_chars = "!@#$%";
    auto generator = [](const std::string& x, int y) {
        std::string result;

        for (int i = 0; i < y; ++i) {
            result += x[rand() % x.length()];
        }
        return result;
    };

    std::vector<std::string> domain_mail_list = {"@hcmut.edu.vn", "@gmail.com", "@yahoo.com", "@hotmail.com", "@outlook.com"};
    std::string domain_mail = domain_mail_list[rand() % domain_mail_list.size()];
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> dist(1, 100 - domain_mail.length());

    int rest_len = dist(gen);
    
    // int rest_len = rand() % (100 - domain_mail.length());
    std::string email_name = generator(chars, rest_len);
    std::string email = email_name + domain_mail;
    std::vector<int> error_list = {-10, -1, -2, -300, -400, -5, 8};
    int idx = error_list[rand() % error_list.size()];
    std::string s;

    // cout << "[+] Generating task 45...\n";

    switch (idx) {
        case -10: {
            while (true) {
                //cout << "[+] Generating -10...\n";
                int s_len = rand() % 13 + 7;
                s = generator(chars + special_chars, s_len);
                if (Password::specialCount(s) == 0) {
                    s.insert(rand() % s_len, 1, special_chars[rand() % special_chars.length()]);
                } else {
                    s.insert(rand() % s_len, 1, chars[rand() % chars.length()]);
                }
                if (checkPassword(s, email) == -10) {
                    break;
                }
            }
            break;
        }
        case -1: {
            int s_len = rand() % 7 + 1;
            s = generator(chars + special_chars, s_len);
            break;
        }
        case -2: {
            int s_len = rand() % 30 + 21;
            s = generator(chars + special_chars, s_len);
            break;
        }
        case -300: {
            if (email_name.length() > 20) {
                int new_rest_len = rand() % 20 + 1;
                email_name = generator(chars, new_rest_len);
                domain_mail = "@" + generator(chars + ".", rand() % (new_rest_len + 1));
                email = email_name + domain_mail;
            }
            int s_len = rand() % (rest_len < 8 ? 21 : rest_len) + 8;
            s = generator("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%", s_len - rest_len);
            s.insert(rand() % (1 + s.length()), email_name);
            break;
        }
        case -400: {
            int repeat_len = rand() % 19 + 2;
            int s_len = rand() % (repeat_len < 8 ? 21 : repeat_len) + 8;
            s = generator(chars + special_chars, s_len - repeat_len);
            std::string ch = generator(chars + special_chars, 1);
            s.insert(rand() % (1 + s.length()), repeat_len, ch[0]);
            break;
        }
        case -5: {
            while (true) {
                //cout << "[+] Generating -5...\n";
                int s_len = rand() % 13 + 8;
                s = generator(chars, s_len);
                //cout << "[+] CHECKING " << checkPassword(s, email) << "\n";
                if (checkPassword(s, email) == -5) {
                    break;
                }
            }
            break;
        }
        default: {
            while (true) {
                //cout << "[+] Generating default...\n";
                int s_len = rand() % 13 + 8;
                std::string other_char = "^&*()_+-={[]}|;:'<,>.?/";
                s = generator(chars + special_chars + other_char, s_len);
                if (checkPassword(s, email) >= 0 && checkPassword(s, email) <= 20) {
                    break;
                }
            }
            break;
        }
    }

    auto generateCorrectPassword = [&]() -> std::string {
        while (true) {
            int s_len = rand() % 13 + 7;
            std::string s = generator(chars + special_chars, s_len);
            if (Password::specialCount(s) == 0) {
                s.insert(rand() % (1 + s_len), 1, special_chars[rand() % special_chars.length()]);
            } else {
                s.insert(rand() % (1 + s_len), 1, chars[rand() % chars.length()]);
            }
            if (checkPassword(s, email) == -10) {
                return s;
            }
        }
    };

    std::vector<std::string> distinct_pwds;
    for (int i = 0; i < 30; ++i) {
        distinct_pwds.push_back(generateCorrectPassword());
    }
    int num_pwds = rand() % 26 + 5;
    std::vector<std::string> arr_pwds;
    for (int i = 0; i < num_pwds; ++i) {
        arr_pwds.push_back(distinct_pwds[rand() % distinct_pwds.size()]);
    }

    return {TestCase4{s, email}, TestCase5{num_pwds, std::move(arr_pwds)}};
}

int main() {
    int const numtestcase = 100000;
    std::cout << "Running task 1..." << std::endl;
    for (int i = 0; i < numtestcase; ++i) {
        const auto test = gentask123();
        // print testcase
        {
          std::ofstream out("testcase");
            out << test.HP1 << ' ' << test.HP2 << '\n'
                << test.EXP1 << ' ' << test.EXP2 << '\n' 
                << test.M1 << ' ' << test.M2 << '\n'
                << test.E1 << ' ' << test.E2 << ' ' << test.E3 << std::endl;
        }

        auto expected = runTask1(test, true_code::firstMeet);
        expected.dump("expected");
        auto got = runTask1(test, firstMeet);
        got.dump("got");

        if (memcmp(&expected, &got, sizeof(Task1Ret)) != 0) {
          std::cout << "Wrong answer\n";
          return -1;
        }
    }
    std::cout << "Task 1 done" << std::endl;
    std::cout << "Running task 2..." << std::endl;
    for (int i = 0; i < numtestcase; ++i) {
        const auto test = gentask123();
        // print testcase
        {
          std::ofstream out("testcase");
            out << test.HP1 << ' ' << test.HP2 << '\n'
                << test.EXP1 << ' ' << test.EXP2 << '\n' 
                << test.M1 << ' ' << test.M2 << '\n'
                << test.E1 << ' ' << test.E2 << ' ' << test.E3 << std::endl;
        }

        auto expected = runTask2(test, true_code::traceLuggage);
        expected.dump("expected");
        auto got = runTask2(test, traceLuggage);
        got.dump("got");

        if (memcmp(&expected, &got, sizeof(Task2Ret)) != 0) {
          std::cout << "Wrong answer\n";
          return -1;
        }
    }
    std::cout << "Task 2 done" << std::endl;
    std::cout << "Running task 3..." << std::endl;
    for (int i = 0; i < numtestcase; ++i) {
        const auto test = gentask123();
        // print testcase
        {
          std::ofstream out("testcase");
            out << test.HP1 << ' ' << test.HP2 << '\n'
                << test.EXP1 << ' ' << test.EXP2 << '\n' 
                << test.M1 << ' ' << test.M2 << '\n'
                << test.E1 << ' ' << test.E2 << ' ' << test.E3 << std::endl;
        }

        auto expected = runTask3(test, true_code::chaseTaxi);
        expected.dump("expected");
        auto got = runTask3(test, chaseTaxi);
        got.dump("got");

        if (memcmp(&expected, &got, sizeof(Task3Ret)) != 0) {
          std::cout << "Wrong answer\n";
          return -1;
        }
    }
    std::cout << "Task 3 done" << std::endl;
    std::cout << "Running task 4..." << std::endl;
    for (int i = 0; i < numtestcase; ++i) {
        const auto test = gentask45();
        // print testcase
        {
          std::ofstream out("testcase");
          out << test.test4.s << '\n' << test.test4.email << std::endl;
        }

        auto expected = true_code::checkPassword(test.test4.s.c_str(), test.test4.email.c_str());

        std::ofstream efile("expected");
        efile << expected << std::endl;
        efile.close();
        auto got = checkPassword(test.test4.s.c_str(), test.test4.email.c_str());
        std::ofstream gfile("got");
        gfile << got << std::endl;
        gfile.close();

        if (got != expected) {
          std::cout << "Wrong answer\n";
          return -1;
        }
    }
    std::cout << "Task 4 done" << std::endl;
    std::cout << "Running task 5..." << std::endl;
    for (int i = 0; i < numtestcase; ++i) {

        // std::cout << i << std::endl;
        const auto test = gentask45();
        //cout << i << " th time shiettttt\n";

        // print testcase
        {
          std::ofstream out("testcase");
          out << test.test5.nstrs << std::endl;
          for (auto& line : test.test5.strs)
            out << line << std::endl;
        }

        
        std::vector<const char*> pwds;
        for (auto& v : test.test5.strs)
            pwds.push_back(v.c_str());

        auto expected = true_code::findCorrectPassword(pwds.data(), test.test5.nstrs);
        //cout << "Expected " << expected << endl;

        std::ofstream efile("expected");
        efile << expected << std::endl;
        efile.close();
        auto got = findCorrectPassword(pwds.data(), test.test5.nstrs);
        //cout << "Got " << got << endl;
        std::ofstream gfile("got");
        gfile << got << std::endl;
        gfile.close();

        if (got != expected) {
          std::cout << "Wrong answer\n";
          return -1;
        }
    }
    std::cout << "Task 5 done" << std::endl;
    std::cout << "All done" << std::endl;
    return 0;
}