#include <cstdlib>
#include <cstdint>
#include <iterator>
#include <iostream>


/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    
    while (firstIn < lastIn) {
        *firstOut = op(*firstIn);
        ++firstIn;
        ++firstOut;
    }
}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    if (first == last) {
        return;
    }
    --last;
    // cout << first << ' ' << last << '\n';
    while (first < last) {
        if (!p(*first)) {
            while (first != last && !p(*last)) {
                --last;
            }
            if (p(*last)) {
                int help = *last;
                *last = *first;
                *first = help;
            }
        }
        ++first;
    }
}

/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {

    while (first1 < last1 || first2 < last2) {
        if (first1 < last1 && first2 < last2){
            if (*first1 <= *first2) {
                *firstOut = *first1;
                ++first1;
            }
            else {
                *firstOut = *first2;
                ++first2;
            }
        }
        else {
            if (first1 < last1) {
                *firstOut = *first1;
                ++first1;
            }
            else{
                *firstOut = *first2;
                ++first2;
            }
        }
        ++firstOut;
    }
}
/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
public:

    class Iterator {
        friend class FibonacciRange;
    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;

        Iterator(uint64_t pr, uint64_t ptr) : pr_(pr), ptr_(ptr){}

        value_type operator *() const {
            // разыменование итератора -- доступ к значению
            return pr_;
        }

        Iterator& operator ++() {
            // prefix increment
            uint64_t help = ptr_;
            ptr_ += pr_;
            pr_ = help;
            // std::cout << *ptr_ << ' ' << *pr_ << '\n';
            return *this;
        }
        Iterator operator ++(int) {
            // postfix increment
            Iterator result = *this;
            uint64_t help = ptr_;
            ptr_ += pr_;
            pr_ = help;
            return result;
        }

        bool operator ==(const Iterator& rhs) const {
            if (ptr_ == rhs.ptr_) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator <(const Iterator& rhs) const {
            if (ptr_ < rhs.ptr_) {
                return true;
            }
            else {
                return false;
            }
        }
        friend std::ostream& operator<<(std::ostream& ostream, const Iterator& array);
    private:
        uint64_t pr_;
        uint64_t ptr_;
    };

    FibonacciRange(size_t amount) {
        amount_= amount;
        int64_t prev1 = 1, prev2 = 2;
        for (int i = 3; i <= amount + 2; ++i) {
            int64_t help = prev2;
            prev2 = prev1 + prev2;
            prev1 = help;
        }
        prevlast_ = prev1;
        last_ = prev2;
    }

    Iterator begin() const {
        return Iterator(1, 2);
    }

    Iterator end() const {
        return Iterator(prevlast_, last_);
    }
    // bool operator=()
    size_t size() const {
        return amount_;
    }
private:
    size_t amount_;
    uint64_t prevlast_;
    uint64_t last_;
};
std::ostream& operator << (std::ostream& ostream, const FibonacciRange::Iterator& array) {
    ostream.clear();
    ostream << array.ptr_  << " and prev is " << array.pr_;
    return ostream;
}
