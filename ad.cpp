#include <iostream>

class LongNumber {
    private:
        int length = 0;
        int sign = 1;
        int *numbers = nullptr; 

    public:

    LongNumber() { // корректный ввод по условию
	    numbers = nullptr;
	    length = 0;
	    sign = 0;
    }
        LongNumber(const char* const str) {
            delete[] numbers;
            length = get_length(str);
            sign = get_sign(str);
            numbers = new int[length-sign];
            for(int i = sign; i < length; i++)
                numbers[i] = str[i] - '0';
        }
        LongNumber(const LongNumber& x) {
            length = x.length;
            sign = x.sign;
            numbers = new int[length];
            for(int i = x.sign; i < x.length; i++ ) 
            numbers[i] = x.numbers[i]; 
        }
        int get_length(const char* const str) const noexcept {
            int length = 0;
            while(str[length] != '\0') {
                length++;
            }
            return length;
        }

        int get_sign(const char* const str) const noexcept {
            if(str[0] == '-')
                return 1;
            else
                return 0;
        }
        friend std::ostream& operator << (std::ostream &os, const LongNumber& x) {
            if(x.sign == 1) os << "-";
            for(int i = 0; i < x.length; i++) {
                os << x.numbers[i];
            }
            return os;
        }
        bool operator == (const LongNumber& x) const {
	        if (&numbers == &x.numbers && sign == x.sign && length == x.length) return true;
	        else return false;
        }
        ~LongNumber() {
            delete[] numbers;
        }

    LongNumber operator + (const LongNumber& x) const { //6718 + 381
	    LongNumber bigger;
	    LongNumber less;
	    LongNumber result;
        if(length >= x.length) {
            bigger = *this;
            less = x;
        }
        else if(length <= x.length) {
            bigger = x;
            less = *this;
        }

        int temp_size = bigger.length + 2;
        int *res_nums = new int[temp_size]{};

        for(int i = bigger.length-1; i >= 0; i--) {
            if(bigger.numbers[i] + less.numbers[i] < 10) 
                res_nums[i] += bigger.numbers[i] + less.numbers[i];
            else if(bigger.numbers[i] + less.numbers[i] >= 10) {
                res_nums[i] += (bigger.numbers[i] + less.numbers[i]) % 10;
                bigger.numbers[i-1] += 1;
            } 
        }

        int head_zeros = 0;
        for(int i = 0; i < temp_size; i++) {
            if(res_nums[i] == 0 && res_nums[i+1] == 0)
                head_zeros++;
            else if(res_nums[i] == 0 && res_nums[i+1] != 0)
                head_zeros++;
                break;
        }

        result.numbers = res_nums + head_zeros;
        res_nums = nullptr; // mem leakage

        return result;
    }
};

int main() {
    LongNumber init("25");
    LongNumber copy("52");
    LongNumber copy2(copy);
    std::cout << init.get_length("25") << " ";
    std::cout << init.get_sign("25") << " ";
    std::cout << init;


    int *res_nums = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    int *test;

    test = res_nums + 2;

    if(copy2 == copy) std::cout << "ok" << std::endl;
        else std::cout << "nigger ";
    for(int i = 0; i < 8; i++) std::cout << test[i];
    
    LongNumber res = LongNumber("22") + LongNumber("11");
    std::cout << res;
}