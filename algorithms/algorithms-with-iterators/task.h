#include <cstdlib>
#include <iterator>
#include <iostream>
#include <algorithm>

/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {
    while (firstIn != lastIn) {
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
    --last;
    while (first < last) {
        if (!p(*first)) {
            while (first < last && !p(*last)) {
                --last;
            }
            if (p(*last)) {
                iter_swap(first, last);  
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

    while (first1 < last1 && first2 < last2) {
        if (*first1 <= *first2) {
            *firstOut = *first1;
            ++first1;
        }
        else {
            *firstOut = *first2;
            ++first2;
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

        Iterator(const uint64_t* ptr) : ptr_(ptr) {}

        value_type operator *() const {
            // разыменование итератора -- доступ к значению
            return *ptr_;
        }

        Iterator& operator ++() {
            // prefix increment
            ++ptr_;
            return *this;
        }
        Iterator operator ++(int) {
            // postfix increment
            Iterator help = *this;
            ++(*this);
            return help;
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

    private:
        const uint64_t* ptr_;
    };

    FibonacciRange(size_t amount) : begin_(1), end_(amount) {}

    Iterator begin() const {
        return Iterator(&begin_);
    }

    Iterator end() const {
        return Iterator(&end_);
    }

    size_t size() const {
        return end_;
    }
private:
    uint64_t begin_, end_;
    
};
