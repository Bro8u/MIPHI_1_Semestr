#pragma once

namespace ranges {

// Определяет тип данных, на которые ссылается итератор
// template <typename Iterator>
// using IteratorValueType = typename std::iterator_traits<Iterator>::value_type;

// Определяет тип возвращаемого функцией значения F(Args...) -> Result
// template <typename F, typename... Args>
// using FunctionResultType = std::invoke_result_t<F, Args...>;

template <typename View, typename Adaptor>
auto operator|(const View& view, const Adaptor& adaptor) {
    return adaptor(view);
}

// Empty View
template <typename T>
class Empty {
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // bool operator==(const Iterator&) const { return true; }
        // bool operator!=(const Iterator&) const { return false; }
        // reference operator*() const { throw std::runtime_error("Empty view has no elements"); }
        // Iterator& operator++() { return *this; }
        // Iterator operator++(int) { return *this; }
    };

    Iterator begin() const { return Iterator(); }
    Iterator end() const { return Iterator(); }
};

// View
template <typename Container>
class View {
private:
    Container& container;

public:
    View(Container& cont) : container(cont) {}

    auto begin() -> decltype(container.begin()) { return container.begin(); }
    auto end() -> decltype(container.end()) { return container.end(); }

    // Определение оператора | для Adaptor
    // template <typename Adaptor>
    // auto operator|(Adaptor adaptor) const {
    //     return adaptor(*this);
    // }
};

} // namespace ranges

