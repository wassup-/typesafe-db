#ifndef NON_COPYABLE_HPP
#define NON_COPYABLE_HPP

namespace fp {

    struct non_copyable {
    private:
        non_copyable(non_copyable const &) = delete;
        non_copyable & operator=(non_copyable const &) = delete;
    protected:
        non_copyable() = default;
    };
}

#endif