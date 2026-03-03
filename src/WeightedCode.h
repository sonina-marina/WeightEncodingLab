#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

struct Answer {
    int m;
    int n;
    int l;
    std::vector<int> A;
    std::string R;
    std::string combination;
};

struct Answer2 {
    int newM;
    std::vector<int> a;
    std::string R;
    int r;
    std::string J;
    std::string result;
};

class WeightedCode {

    private:

        std::string s, newS, R;
        int m, n, l, R10;

        int newN, newM;
        std::string newR;

        int countWeight(std::string s) {
            int weight = 0;
            for (int i = 0; i < n; i++) {
                weight += (s[i] - '0');
                //std::cout << s[i] - '0' << " ";
            }
            return weight;
        }

        std::string toBinary(int n) {
            if (n == 0) return "0";
            std::string binary = "";
            while (n > 0) {
                binary += (n % 2 == 0 ? '0' : '1');
                n /= 2;
            }
            std::reverse(binary.begin(), binary.end());
            return binary;
        }

        int fromBinary(std::string s) {
            int digit = 0;
            for (int i = 0; i < s.size(); i++) {
                digit += (s[i] - '0') * std::pow(2, s.size() - 1 - i);
            }
            return digit;
        }

        int modFunc(int a, int b) {
            while (a < 0) {
                a += b;
            }

            return a % b;
        }

    public:
        
        Answer coding(std::string s) {

            Answer ans;

            n = s.size();
            m = 0;

            for (char c : s) {
                if (c == '1') {
                    m++;
                }
            }
            
            l = ceil(log2(n));
        
            ans.m = m;
            ans.n = n;
            ans.l = l;
            
            std::vector<int> a(m);
            int counter = 0;
            int sumIndexes = 0;
            for (int i = 0; i < n; i++) {
                if (s[i] == '1') {
                    a[counter] = i;
                    sumIndexes += i;
                    counter++;
                }
            }

            R10 = sumIndexes % n;
            R = toBinary(R10);
            while (R.size() < l) {
                R = "0" + R;
            }
            newS = s + R;

            ans.A = a;
            ans.R = R;
            ans.combination = newS;
            // << newS << " " << R << "\n";
            return ans;
        }


        Answer2 checking(const std::string& newS) {
            Answer2 ans;
            std::string str = newS, res = "";

            newN = str.size();
            newM = 0;
            int infLength = newN - l;
            int sumIndexes = 0;

            std::vector<int> newA;
            for (int i = 0; i < infLength; i++) {
                if (str[i] == '1') {
                    newA.push_back(i);
                    newM++;
                    sumIndexes += i;
                }   
                //std::cout << str[i] << " ";
            }

            newR = str.substr(newN - l);

            ans.newM = newM;
            ans.a = newA;
            ans.R = newR;

            std::string potentialR = toBinary(sumIndexes % n);
            while (potentialR.size() < l) {
                potentialR = "0" + potentialR;
            }

            //std::cout << newM << " " << m << "\n";

            if (newM == m) {
                if (R == newR ) {
                    if (potentialR == newR) {
                        ans.r = 0;
                        ans.J = "";
                        ans.result = str.substr(0, newN - l);
                        //std::cout << "Декодировали: " << ans.result << "\n";
                    }
                    else {
                        ans.r = 2;
                        ans.J = "";
                        ans.result = "Симметричная ошибка в информационной части";
                        //std::cout << ans.result << "\n";
                    }
                }
                else {
                    int counter = 0;
                    std::vector<int> markNumber;
                    for (int i = 0; i < l; i++) {
                        if (potentialR[i] != newR[i]) {
                            counter++;
                            markNumber.push_back(infLength + i);
                        }
                    }
                    std::string markN = "";
                    for (int i: markNumber) {
                        str[i] = (str[i] == '0') ? '1' : '0';
                        markN += std::to_string(i) + " ";
                    }

                    ans.r = counter;
                    ans.J = markN;
                    ans.result = str.substr(0, newN - l);
                    //std::cout << ans.result << "\n";
                }
            }
            else {
                //std::cout << "other" << "\n";
                int position;
                //std::cout << newM - m << "\n";
                if (newM - m == 1) { // newM > by 1
                    //std::cout << sumIndexes << " " << newN - l << " " << fromBinary(newR) << "\n";
                    position = modFunc((sumIndexes % (newN - l)- fromBinary(newR)), newN - l);
                    //std::cout << "Ошибка в бите: " << ans.J << "\n";
                    str[position] = (str[position] == '0') ? '1' : '0';
                    //std::cout << str << "\n";
                }
                else if (newM - m == -1) {
                    position = modFunc((fromBinary(newR) - sumIndexes % (newN - l)), newN - l);
                    str[position] = (str[position] == '0') ? '1' : '0';
                }
                else {
                    ans.r = 2;
                    ans.J = "";
                    ans.result = "";
                    return ans;
                }
                //std::cout << countWeight(str);
                if (countWeight(str) == m) {
                    ans.r = 1;
                    ans.J = std::to_string(position);
                    ans.result = str.substr(0, newN - l);
                }
                else {
                    ans.r = 2;
                    ans.J = "";
                    ans.result = "Один информационный и один проверочный символы";
                }
            }
            


            // ans.r = ;
            // ans.J = ;

            
            return ans;
        }
};