#include <cstddef>
#include <tuple>

template <typename T>
class UniquePtr {
private:
    T* ptr_ = nullptr;

public:
    explicit UniquePtr(T* pptr = nullptr) {
        ptr_ = pptr;
    }
    UniquePtr(UniquePtr&& other) noexcept {
        delete ptr_;
        ptr_ = nullptr;
        std::swap(ptr_, other.ptr_);
    }
    template <typename C>
    UniquePtr(UniquePtr<C>&& other) noexcept {
        Reset();
        ptr_ = (other.Release());
        other.Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s
    template <typename C>
    UniquePtr& operator=(UniquePtr<C>&& other) noexcept {
        Reset();
        ptr_ = (other.Release());
        other.Reset();
        return *this;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (ptr_ == other.Get()) {
            return *this;
        }
        delete ptr_;
        ptr_ = nullptr;
        std::swap(ptr_, other.ptr_);
        return *this;
    }
    UniquePtr& operator=(std::nullptr_t) noexcept {
        delete ptr_;
        ptr_ = nullptr;
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~UniquePtr() noexcept {
        delete ptr_;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release() {
        T* ans = ptr_;
        ptr_ = nullptr;
        return ans;
    }
    void Reset(T* pptr = nullptr) {
        std::swap(ptr_, pptr);
        delete pptr;
        pptr = nullptr;
    }
    void Swap(UniquePtr& other) {
        std::swap(ptr_, other.ptr_);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const {
        return ptr_;
    }
    explicit operator bool() const {
        return ptr_ != nullptr;
    }

    T& operator*() const {
        return (*ptr_);
    }
    T* operator->() const {
        return ptr_;
    }
};
